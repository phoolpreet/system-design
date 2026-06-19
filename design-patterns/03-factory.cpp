#include <iostream>
#include <memory>
#include <string>

class Notification
{
public:
    virtual ~Notification() = default;

    virtual void send(const std::string &message) = 0;
};

class EmailNotification : public Notification
{
public:
    void send(const std::string &message) override
    {
        std::cout << "Email: " << message << '\n';
    }
};

class SMSNotification : public Notification
{
public:
    void send(const std::string &message) override
    {
        std::cout << "SMS: " << message << '\n';
    }
};

class PushNotification : public Notification
{
public:
    void send(const std::string &message) override
    {
        std::cout << "Push: " << message << '\n';
    }
};

class NotificationFactory
{
public:
    static std::unique_ptr<Notification>
    create(const std::string &type)
    {
        if (type == "email")
            return std::make_unique<EmailNotification>();

        if (type == "sms")
            return std::make_unique<SMSNotification>();

        if (type == "push")
            return std::make_unique<PushNotification>();

        return nullptr;
    }
};

int main()
{
    auto notification =
        NotificationFactory::create("email");

    notification->send("Hello World");
}