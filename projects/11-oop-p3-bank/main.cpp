#include <atomic>
#include <chrono>
#include <csignal>
#include <iostream>
#include <memory>
#include <thread>

// infrastructure - persistence
#include "infrastructure/persistence/SqliteConnection.hpp"
#include "infrastructure/persistence/SqliteSchemaInitializer.hpp"
#include "infrastructure/persistence/SqliteUnitOfWork.hpp"
#include "infrastructure/repositories/SqliteAccountRepository.hpp"
#include "infrastructure/repositories/SqliteAuditLogRepository.hpp"
#include "infrastructure/repositories/SqliteClientRepository.hpp"
#include "infrastructure/repositories/SqliteOutboxRepository.hpp"
#include "infrastructure/repositories/SqliteTransactionRepository.hpp"
#include "infrastructure/repositories/SqliteUserRepository.hpp"

// infrastructure - services
#include "infrastructure/outbox/OutboxPoller.hpp"
#include "infrastructure/services/InMemoryCurrencyRateService.hpp"
#include "infrastructure/services/InMemoryRateLimiter.hpp"
#include "infrastructure/services/InMemoryRealtimePublisher.hpp"
#include "infrastructure/services/InMemorySessionService.hpp"
#include "infrastructure/services/InMemoryTaskQueue.hpp"
#include "infrastructure/services/LoggingNotificationService.hpp"
#include "infrastructure/services/PlainTextHasher.hpp"
#include "infrastructure/services/RandomPinCodeGenerator.hpp"
#include "infrastructure/services/UuidGenerator.hpp"

// Application
#include "application/CompositionRoot.hpp"

// Graceful shutdown - SIGINT / SIGTERM set this flag.
// The main loop checks it and calls root.shutdown() before exit.
static std::atomic<bool> gRunning{true};

static void handleSignal(int) {
    gRunning = false;
}

int main(int argc, char* argv[]) {

    const std::string dbPath = argc > 1 ? argv[1] : "bank.db";

    std::signal(SIGINT, handleSignal);
    std::signal(SIGTERM, handleSignal);

    try {
        // Schema -------
        // Shared connection for schema init - closed after setup.
        {
            SqliteConnection initConn(dbPath);
            SqliteSchemaInitializer::initialize(initConn);
        }

        // Per-request connection factory ------
        // Each request gets its own SqliteConnection + UnitOfWork.
        // The lambda is called by the request dispatcher / HTTP layer.
        // For simplicity here we create one shared connection.
        // TODO: use a connection pool for prod.
        auto sharedConn = std::make_shared<SqliteConnection>(dbPath);
        auto uow        = std::make_shared<SqliteUnitOfWork>(sharedConn);

        // Repositories ------------
        auto clientRepo      = std::make_shared<SqliteClientRepository>(uow);
        auto accountRepo     = std::make_shared<SqliteAccountRepository>(uow);
        auto transactionRepo = std::make_shared<SqliteTransactionRepository>(uow);
        auto userRepo        = std::make_shared<SqliteUserRepository>(uow);

        // Outbox - two instances:
        //      uowOutbox   : used by event handlers (shares the UoW connection)
        //      pollerOutbox: used by OutboxPoller (own connection, own thread)
        auto uowOutbox    = std::make_shared<SqliteOutboxRepository>(uow);
        auto pollerOutbox = std::make_shared<SqliteOutboxRepository>(dbPath, nullptr);

        // Audit log - own connection so writes survive a UoW rollback.
        auto auditLog = std::make_shared<SqliteAuditLogRepository>(dbPath);

        // Domain ports ---------------------------------------------------
        auto idGenerator  = std::make_shared<UuidGenerator>();
        auto pinGenerator = std::make_shared<RandomPinCodeGenerator>();
        auto hasher       = std::make_shared<PlainTextHasher>();
        // TODO: swap PlainTextHasher -> BcryptPasswordHasher before prod

        // Application services ----------------------------------------
        auto sessionService = std::make_shared<InMemorySessionService>();
        auto rateLimiter =
            std::make_shared<InMemoryRateLimiter>(/*maxRequests=*/10, /*windowSeconds=*/60);
        auto realtimePublisher = std::make_shared<InMemoryRealtimePublisher>();
        auto taskQueue         = std::make_shared<InMemoryTaskQueue>();
        auto currencyService   = std::make_shared<InMemoryCurrencyRateService>();
        auto notifService      = std::make_shared<LoggingNotificationService>();

        // Seed a sample rate for development.
        currencyService->updateRate({"USD", "TRY", 44.5, std::time(nullptr)});

        // Outbox Poller ---------------------------------------------------------
        auto outboxPoller = std::make_shared<OutboxPoller>(

            pollerOutbox,
            taskQueue,
            /*pollingIntervalMs=*/1000,
            /*batchSize=*/50,
            /*maxAttempts=*/5);

        // Task handler - SendSmsTask ---------------------------------
        taskQueue->registerHandler("SendSmsTask",

                                   [notifService](const std::string& payload) {
                                       // TODO: deserialize JSON payload with nlohmann/json.
                                       // For now, log the raw payload.
                                       notifService->sendSms("(parsed from payload)", payload);
                                   }

        );

        // Composition root ---------------------------------------------------
        auto root = CompositionRoot::build(userRepo,
                                           clientRepo,
                                           accountRepo,
                                           uowOutbox,  // outbox repo for event handlers
                                           uow,
                                           auditLog,
                                           idGenerator,
                                           pinGenerator,
                                           hasher,
                                           sessionService,
                                           currencyService,
                                           rateLimiter,
                                           taskQueue,
                                           outboxPoller,
                                           notifService);

        std::cout << "[main] Banking system started. DB: " << dbPath << '\n';
        std::cout << "[main] Press Ctrl+C to stop.\n";

        // Main loop -----------------------------------------------------------
        // In a real system this would block on an HTTP server accept loop.
        // Here we demonstrate a single RegisterClient call then idle.
        {
            auto ctx = ExecutionContext::anonymous(idGenerator->generate(), "127.0.0.1");

            RegisterClientRequest req;
            req.firstName = "Ali";
            req.lastName  = "Omer";
            req.phone     = "+905345678901";

            auto result = root.pipelines.registerClient.execute(ctx, req);

            if (result.success)
                std::cout << "[demo] Client registered: " << result.data->clientId << '\n';
            else
                std::cout << "[demo] Registration failed: " << result.error->message << '\n';
        }

        {
            CallerIdentity admin{
                "admin-id",
                "admin",
                "ADMIN",
                /*permissions=*/0xFFFFFFFF  // all permissions
            };

            auto ctx = ExecutionContext::authenticated(admin, idGenerator->generate(), "127.0.0.1");

            RegisterClientRequest req;
            req.firstName = "Nor";
            req.lastName  = "Ola";
            req.phone     = "+905345678900";

            auto result = root.pipelines.registerClient.execute(ctx, req);

            if (result.success)
                std::cout << "[demo] Client registered: " << result.data->clientId << '\n';
            else
                std::cout << "[demo] Registration failed: " << result.error->message << '\n';
        }

        while (gRunning) {

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        // Graceful shutdown ------------------------------------------------------
        std::cout << "\n[main] Shutting down...\n";
        root.shutdown();
        std::cout << "[main] Done.\n";

    } catch (const std::exception& ex) {

        std::cerr << "[main] Fatal error: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}