#pragma once

#include <iostream>

#include "application/services/INotificationService.hpp"

// Prints notifications to stdout - for development.
// swap with TwilioNotificationService / SmtpNotificationService

class LoggingNotificationService : public INotificationService {

    public:

        void sendSms(const std::string& phone, const std::string& message) override {

            std::cout << "[SMS] to=" << phone << " | " << message << '\n';
        }

        void sendEmail(const std::string& toAddress,
                       const std::string& subject,
                       const std::string& body) override {

            std::cout << "[EMAIL] to=" << toAddress << " | subject=" << subject
                      << " | body=" << body << '\n';
        }
};