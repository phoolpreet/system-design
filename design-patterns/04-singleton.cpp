#include <iostream>

class Logger
{
public:
    static Logger &instance()
    {
        static Logger logger; // Created once
        return logger;
    }

    void log(const std::string &msg)
    {
        std::cout << "[LOG] " << msg << '\n';
    }

private:
    Logger() = default;

    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;
};

int main()
{
    Logger::instance().log("Application started");

    Logger &l1 = Logger::instance();
    Logger &l2 = Logger::instance();

    std::cout << (&l1 == &l2) << '\n';
}