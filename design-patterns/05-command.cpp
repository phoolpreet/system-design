#include <iostream>
#include <memory>

class Light
{
public:
    void turnOn()
    {
        std::cout << "Light ON\n";
    }

    void turnOff()
    {
        std::cout << "Light OFF\n";
    }
};

class Command
{
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

class TurnOnCommand : public Command
{
private:
    Light &light_;

public:
    explicit TurnOnCommand(Light &light)
        : light_(light)
    {
    }

    void execute() override
    {
        light_.turnOn();
    }
};

class TurnOffCommand : public Command
{
private:
    Light &light_;

public:
    explicit TurnOffCommand(Light &light)
        : light_(light)
    {
    }

    void execute() override
    {
        light_.turnOff();
    }
};

class RemoteButton
{
private:
    std::unique_ptr<Command> command_;

public:
    explicit RemoteButton(std::unique_ptr<Command> cmd)
        : command_(std::move(cmd))
    {
    }

    void press()
    {
        command_->execute();
    }
};

int main()
{
    Light light;

    RemoteButton onButton(
        std::make_unique<TurnOnCommand>(light));

    RemoteButton offButton(
        std::make_unique<TurnOffCommand>(light));

    onButton.press();
    offButton.press();
}