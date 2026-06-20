#include <iostream>
#include <memory>

class TrafficLight;

class State
{
public:
    virtual ~State() = default;

    virtual void next(TrafficLight &light) = 0;
    virtual const char *name() const = 0;
};

class TrafficLight
{
private:
    std::unique_ptr<State> state_;

public:
    explicit TrafficLight(std::unique_ptr<State> state)
        : state_(std::move(state))
    {
    }

    void setState(std::unique_ptr<State> state)
    {
        state_ = std::move(state);
    }

    void next()
    {
        state_->next(*this);
    }

    void print() const
    {
        std::cout << state_->name() << '\n';
    }
};

class GreenState;
class YellowState;
class RedState;

class RedState : public State
{
public:
    void next(TrafficLight &light) override;

    const char *name() const override
    {
        return "RED";
    }
};

class GreenState : public State
{
public:
    void next(TrafficLight &light) override;

    const char *name() const override
    {
        return "GREEN";
    }
};

class YellowState : public State
{
public:
    void next(TrafficLight &light) override;

    const char *name() const override
    {
        return "YELLOW";
    }
};

void RedState::next(TrafficLight &light)
{
    light.setState(
        std::make_unique<GreenState>());
}

void GreenState::next(TrafficLight &light)
{
    light.setState(
        std::make_unique<YellowState>());
}

void YellowState::next(TrafficLight &light)
{
    light.setState(
        std::make_unique<RedState>());
}

int main()
{
    TrafficLight light(
        std::make_unique<RedState>());

    for (int i = 0; i < 5; ++i)
    {
        light.print();
        light.next();
    }
}