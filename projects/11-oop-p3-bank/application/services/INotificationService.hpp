#pragma once

#include <string>

// SMS and email delivery port.
// Called by task handlers on background threads - never from use cases directly.
// Implementations: TwilioNotificationService, LoggingNotificationService(dev).

// TODO: add NotificationResult send(const NotificationMessage& message) and NotificationChannel {
// SMS, EMAIL, PUSH, WHATSAPP } abstaction
class INotificationService {

    public:

        virtual void sendSms(const std::string& phone, const std::string& message) = 0;

        virtual void sendEmail(const std::string& toAddress,
                               const std::string& subject,
                               const std::string& body) = 0;

        virtual ~INotificationService() = default;
};