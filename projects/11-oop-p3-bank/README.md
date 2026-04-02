# Banking System — C++ Clean Architecture
 
> A production-grade banking system built in C++ as a **learning project** exploring Clean Architecture, Domain-Driven Design, and enterprise patterns applied to a genuinely complex domain.
 
---
 
## Why This Project Exists
 
Most tutorials teach patterns in isolation — a Repository here, a Factory there, a Strategy pattern somewhere else. What they rarely show is how these patterns *interact* under real constraints: when the domain is genuinely complex, when boundaries between concerns actually matter, and when getting the architecture wrong costs more than starting over.
 
This project was built to answer a different set of questions.
 
**Why Clean Architecture?**
Not because it is the only valid approach — it is not. But because it imposes a structured framework that forces you to reason about every dependency. When a domain entity cannot import a database library *by design*, you stop asking "should it?" and start asking "what should own this instead?" That discipline surfaces better decisions faster than any amount of theory. It is a guard against spaghetti — not just in the code, but in the thinking.
 
**Why a banking system?**
Banking is one of the few domains where the rules are non-negotiable, the data is permanent, and mistakes have real consequences. It forces you to think about immutability (transactions cannot be edited), audit trails (everything is recorded), consistency (a transfer must debit and credit atomically), and bounded contexts (a client's identity has nothing to do with their account balance). These problems do not appear in todo-list tutorials. The complexity is the point.
 
**Why implement Redis and Kafka in-memory?**
Because understanding *why* Redis solves the rate-limiting problem requires experiencing the problem first without Redis. When you build `InMemoryRateLimiter` and realise it breaks the moment you run two server instances, you understand exactly what Redis brings and why it is designed the way it is. The in-memory implementations are not shortcuts — they are the foundation for understanding what the real thing replaces and why it exists.
 
The goal was never to ship this to production. The goal was to understand what production-grade actually means, by building toward it with discipline.
 
---
 
## Architecture Overview
 
The system applies **Clean Architecture** (Robert C. Martin) layered over **Domain-Driven Design** (Eric Evans) concepts, with patterns borrowed from NestJS and ASP.NET Core adapted to C++.
 
```
┌──────────────────────────────────────────────────────┐
│                   PRESENTATION                        │
│              HTTP / WebSocket / CLI                   │
└──────────────────────┬───────────────────────────────┘
                       │
┌──────────────────────▼───────────────────────────────┐
│                 APPLICATION LAYER                     │
│  Pipeline · Interceptors · UseCases · Events          │
│  Outbox · TaskQueue · RealTime · Audit · Session      │
└──────────┬──────────────────────────┬────────────────┘
           │ depends on               │ depends on
    (interfaces)               (interfaces)
           │                          │
┌──────────▼──────────┐   ┌──────────▼────────────────┐
│    DOMAIN LAYER      │   │   INFRASTRUCTURE LAYER     │
│  Entities            │   │  SQLite Repositories       │
│  Value Objects       │   │  Mappers                   │
│  Domain Services     │   │  In-Memory Services        │
│  Repository (I)      │   │  Background Workers        │
│  Ports (I)           │   │  Schema Initializer        │
└──────────────────────┘   └───────────────────────────┘
```
 
**The Dependency Rule:** source code dependencies point inward only. The domain knows nothing about the application layer. The application layer knows nothing about infrastructure. Infrastructure implements everything the inner layers declare they need.
 
---
 
## Folder Structure
 
```
banking-system/
├── domain/
│   ├── entities/        Client, Account, Transaction, User
│   ├── value_objects/   Money, PinCode, Role, AccountId, ClientId…
│   ├── repositories/    IClientRepository, IAccountRepository… (interfaces)
│   ├── services/        BalanceCalculator (pure domain logic)
│   ├── ports/           IIdGenerator, IPinCodeGenerator, IPasswordHasher, IUnitOfWork
│   └── security/        Permissions (bitmask flags)
│
├── application/
│   ├── abstractions/    IUseCase, IInterceptor, UseCasePipeline, PipelineBuilder
│   │                    ExecutionContext, CallerIdentity, UseCaseMetadata
│   │                    AppError, UseCaseResult<T>
│   ├── interceptors/    CallerPolicy, Validation, RateLimit,
│   │                    Authorization, Audit, Transaction
│   ├── usecases/        client/ account/ transaction/ user/ currency/
│   ├── events/          IDomainEvent, IEventDispatcher, EventDispatcher
│   │   ├── domain/      ClientRegisteredEvent…
│   │   └── handlers/    SendWelcomeSmsHandler…
│   ├── outbox/          OutboxEntry, IOutboxRepository, IOutboxPoller
│   ├── tasks/           ITask, ITaskQueue, SendSmsTask…
│   ├── services/        IRateLimiter, ISessionService, IRealtimePublisher…
│   ├── audit/           IAuditLog
│   └── CompositionRoot.hpp
│
└── infrastructure/
    ├── persistence/     SqliteConnection, SqliteUnitOfWork, Row
    ├── mappers/         ClientMapper, AccountMapper, TransactionMapper, UserMapper
    ├── repositories/    SqliteClientRepository, SqliteAccountRepository…
    ├── services/        UuidGenerator, RandomPinCodeGenerator,
    │                    InMemoryRateLimiter, InMemoryTaskQueue,
    │                    InMemoryRealtimePublisher, InMemorySessionService…
    └── outbox/          OutboxPoller
```
 
---
 
## Bounded Contexts
 
The domain is divided into four bounded contexts with strict ownership:
 
| Context | Owns | Does NOT Own |
|---|---|---|
| **Client BC** | identity, contact info, PinCode | balance, account number, transactions |
| **Account BC** | accountId, clientId, status (ACTIVE/FROZEN/CLOSED) | balance (derived), transaction history |
| **Transaction BC** | every financial movement, balance (derived) | client info, account status |
| **User BC** | operator identity, role + permissions, password hash | client data, financial data |
 
The most important design decision: **balance is derived, never stored.** Balance = sum of all credits minus debits from the transaction history. There is no `_balance` field anywhere. This prevents balance drift, makes auditing trivial, and correctly places financial truth in the Transaction BC.
 
---
 
## Design Patterns
 
### Repository Pattern
Use cases depend on `IClientRepository`, not `SqliteClientRepository`. The database is an implementation detail. Tests require no database.
 
### Factory Method
Private constructors + named static factories:
```cpp
Account::openFor(accountId, clientId)
Transaction::credit(id, accountId, amount, description)
Transaction::debit(id, accountId, amount, description)
```
Invalid objects cannot be constructed — the compiler prevents it.
 
### Reconstitution Pattern
`create()` validates and generates. `reconstitute()` restores from persistence without revalidating — rerunning validators against historical data risks rejecting records created under old rules.
 
### Chain of Responsibility — Pipeline
Every use case passes through a composable interceptor chain. Each interceptor calls `next()` or short-circuits:
```
CallerPolicy → Validation → RateLimit? → Auth? → Audit? → Transaction? → UseCase
```
 
### Metadata-Driven Decorator (NestJS equivalent)
Each use case declares its own requirements. `PipelineBuilder` reads them and assembles only the interceptors needed — no manual wiring per use case:
 
```cpp
// NestJS:
@UseGuards(AuthGuard)
@Roles(Permission.AddClient)
@UseInterceptors(AuditInterceptor)
 
// C++ equivalent — use case self-describes:
UseCaseMetadata metadata() const override {
    return UseCaseMetadata::create("RegisterClient")
        .withPermission(Permission::AddClient);
    // transactional = true (default)
    // audited       = true (default)
}
```
 
### Transactional Outbox
The race condition without outbox:
```
DB commits → process crashes → event never dispatched → SMS never sent → no retry
```
With outbox: domain entities AND outbox entries are written in the same atomic commit. A background `OutboxPoller` reads pending entries and delivers them. At-least-once delivery is guaranteed. The in-memory task queue simulates exactly what RabbitMQ/Kafka would do — making the swap a one-line change in `CompositionRoot`.
 
### Unit of Work
All repository saves within one request share the same DB connection and transaction. `TransactionInterceptor` calls `begin()`/`commit()`/`rollback()`. If any save fails, everything rolls back atomically.
 
### Port / Adapter (Strategy)
Every infrastructure concern is behind an interface. The composition root decides which implementation to wire:
 
| Concern | Dev (current) | Production (swap) |
|---|---|---|
| Task Queue | `InMemoryTaskQueue` | `RabbitMqTaskQueue` / `KafkaTaskQueue` |
| Real-time | `InMemoryRealtimePublisher` | `RedisRealtimePublisher` |
| Rate Limiting | `InMemoryRateLimiter` | `RedisRateLimiter` |
| Session | `InMemorySessionService` | `JwtSessionService` |
| Database | SQLite | PostgreSQL |
| Notifications | `LoggingNotificationService` | `TwilioNotificationService` |
 
Every swap is one line in `CompositionRoot`. The application layer never changes.
 
### Anti-Corruption Layer (Mappers)
`ClientMapper`, `AccountMapper`, `TransactionMapper`, `UserMapper` translate between domain model and database rows. Column names are string literals in exactly one file. Migration-safe field reading via `row.getOr<T>(column, default)` means old records never break when fields are added.
 
---
 
## NestJS Mapping Reference
 
| NestJS | C++ Equivalent |
|---|---|
| `@Module` | `CompositionRoot::build()` |
| `@Injectable()` Service | Use case class |
| `@UseGuards(AuthGuard)` | `AuthorizationInterceptor` |
| `@Roles(Permission.X)` | `UseCaseMetadata.withPermission(X)` |
| `ValidationPipe` | `ValidationInterceptor` + `request.validate()` |
| `@Throttle()` | `RateLimitInterceptor` |
| `EventEmitter` | `IEventDispatcher` + `EventDispatcher` |
| `@InjectRepository()` | Constructor injection via `shared_ptr` |
| Bull Queue | `ITaskQueue` → `InMemoryTaskQueue` |
| WebSocket Gateway | `IRealtimePublisher` → `InMemoryPublisher` |
 
---
 
## Current State
 
### Domain Layer — Complete
All entities, value objects, repository interfaces, domain services, and ports fully implemented with invariants, factory methods, and reconstitution patterns.
 
### Application Layer — Complete
All 38 files: abstractions, 6 interceptors, `PipelineBuilder`, `CompositionRoot`, event system, outbox types, task definitions, and service ports. Three showcase use cases fully implemented: `LoginUseCase`, `RegisterClientUseCase`, `GetCurrencyRateUseCase`.
 
### Infrastructure Layer — Complete
SQLite repositories for all entities, mappers, `Row` abstraction, `SqliteConnection`, `SqliteUnitOfWork`, `SqliteSchemaInitializer`, `OutboxPoller`, and all in-memory service implementations.
 
### Use Cases — 3 of 21 Implemented
The patterns are fully established. Every remaining use case follows the same structure as `RegisterClientUseCase`.
 
---
 
## How To Add a New Use Case
 
**Step 1** — Design the contract first. Request DTO, Response DTO, errors, domain events raised.
 
**Step 2** — Declare metadata:
```cpp
UseCaseMetadata metadata() const override {
    return UseCaseMetadata::create("DepositUseCase")
        .withPermission(Permission::Deposit);
}
```
 
**Step 3** — Implement `execute()`. Pure business logic. No auth checks, no transaction management, no audit writes — the pipeline handles all of that.
 
**Step 4** — Register in `CompositionRoot`:
```cpp
root.pipelines.deposit = PipelineBuilder::build(
    std::make_shared<DepositUseCase>(accountRepo, transactionRepo, idGenerator),
    services);
```
 
That is the entire change surface.
 
---
 
## What To Build Next
 
Ordered by importance:
 
1. **Idempotency keys on write use cases** — the most critical production safety fix. At-least-once delivery from the outbox without idempotency is a double-spend vulnerability. Every financial use case needs an `idempotencyKey` field and a pre-execution duplicate check.
 
2. **Running balance on Transaction** — replace load-all `BalanceCalculator` with a stored `running_balance` column. Balance is always the latest transaction's running balance. One query instead of N.
 
3. **Remaining 17 use cases** — `Deposit`, `Withdraw`, `Transfer`, `GetBalance`, `GetStatement`, `DeleteClient`, `DeactivateUser`, and others. All follow the established pattern.
 
4. **Transaction policy engine** — `PolicyEvaluator` domain service checking daily limits, velocity rules, cooling-off periods. Plugs in as a new interceptor on financial use cases.
 
5. **Client notifications on every transaction** — `TransactionCreatedEvent` → `ClientNotificationHandler` → outbox → SMS. The `SendWelcomeSmsHandler` is the exact template to copy.
 
6. **Four-eyes approval for large transfers** — `PendingTransfer` entity with `AWAITING_APPROVAL → APPROVED → EXECUTED | REJECTED` state machine.
 
7. **Double-entry ledger** — `LedgerEntry` entity, chart of accounts, `LedgerBalanceVerifier` domain service. This is the correct production-grade ledger model. The architecture supports it cleanly through the event system.
 
8. **Suspicious activity detection** — `SuspiciousActivityDetector` domain service, called by `TransactionCreatedEvent` handler.
 
---
 
## Trade-offs
 
| Decision | Benefit | Cost |
|---|---|---|
| Balance derived from transactions | Perfect audit trail, no drift | Load-all is expensive at scale — mitigated by running balance |
| Templated pipeline | Compile-time type safety | Template instantiation per use case, longer build times |
| Outbox polling (1s interval) | Guaranteed delivery | Up to 1s delay between commit and SMS delivery |
| SQLite | Zero setup, single file | Limited concurrent writes, no replication |
| In-memory services | Zero external dependencies | Data lost on restart, cannot simulate broker failures |
| Single-entry bookkeeping (current) | Simple to reason about | Not production-grade for a real bank — double-entry is the correct model |
 
---
 
## Running the Project
 
```bash
git clone https://github.com/yousdevs/Engineering-Logic-Roadmap.git
cd projects/11-oop-p3-bank
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j$(nproc)
./banking_system
```
 
**Requirements:** C++17, CMake 3.16+, SQLite3 (`libsqlite3-dev` on Debian/Ubuntu).
 
---
 
## Key Learning Outcomes
 
**Design by contract before implementation** is the single most valuable practice in this codebase. Defining Request/Response DTOs before writing a line of implementation forces every dependency and boundary violation to surface at design time — not at debugging time.
 
**Discomfort is an architectural alarm.** When a field feels wrong to put somewhere, that feeling is a boundary violation trying to surface. The moment `balance` felt wrong in `AddClientRequest` was the moment the Transaction BC was correctly separated.
 
**Build the in-memory version first.** `InMemoryRateLimiter` working on one instance but failing on two instances is a more durable understanding of Redis than any documentation produces.
 
**Testability is a design metric, not a test concern.** Every decision that moved ID generation to the application layer was made to improve testability. `Transaction::credit(id, accountId, amount, desc)` requires zero mocks. A test is three lines.
 
**Patterns are vocabulary, not templates.** Repository, Factory, Outbox, Pipeline — these names communicate intent instantly to any developer who knows them. Architecture is written for the next person, not the compiler.
 
---
 
