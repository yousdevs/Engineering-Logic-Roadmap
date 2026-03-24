#pragma once

#include <string>

#include "application/tasks/ITask.hpp"

// Enqueued when an SMS must be sent.
// Produced by SendWelcomeSmsHandler (ClientRegisteredEvent).
// Consumed by the task worker witch calls INotificationService.sendSms().
// Idempotent - sending the same SMS twice is acceptable.

// TODO: Add taskId, proper JSON serialization/deserialization, and deduplication support

struct SendSmsTask : public ITask {

        std::string phone;
        std::string message;
        std::string clientId;  // tracing only

        std::string taskType() const override {
            return "SendSmsTask";
        }

        std::string serialize() const override {

            // Replace with a proper JSON library (nlohmann/json) in production.
            return "{\"phone\":\"" + phone + "\","
            "\"message\":\"" + message + "\","
            "\"clientId\":\"" + clientId + "\"}";
        }
};