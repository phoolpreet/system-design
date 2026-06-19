#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <string>

// Observer interface
template <typename Message>
class Observer
{
public:
    virtual ~Observer() = default;
    virtual void onNotify(const Message &msg) = 0;
};

// Subject
template <typename Message>
class Subject
{
public:
    void subscribe(std::shared_ptr<Observer<Message>> observer)
    {
        observers_.push_back(observer);
    }

    void notify(const Message &msg)
    {
        for (auto &obs : observers_)
        {
            obs->onNotify(msg);
        }
    }

private:
    std::vector<std::shared_ptr<Observer<Message>>> observers_;
};

// Example message type
struct SensorData
{
    int temperature = 27;
    int humidity = 50;
};

// Concrete observers
class Display : public Observer<SensorData>
{
public:
    void onNotify(const SensorData &data) override
    {
        std::cout << "Display: Temp=" << data.temperature
                  << ", Humidity=" << data.humidity << '\n';
    }
};

class Logger : public Observer<SensorData>
{
public:
    void onNotify(const SensorData &data) override
    {
        std::cout << "Logger: Received sensor update\n";
    }
};

// Main function
int main()
{
    std::cout << "Observer Pattern!" << std::endl;
    Subject<SensorData> sensorSubject;

    auto display = std::make_shared<Display>();
    auto logger = std::make_shared<Logger>();

    sensorSubject.subscribe(display);
    sensorSubject.subscribe(logger);

    SensorData data{25, 60};

    sensorSubject.notify(data);
}