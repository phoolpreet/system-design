#include <iostream>
#include <memory>
#include <string>

class Coffee
{
public:
    virtual ~Coffee() = default;

    virtual double cost() const = 0;
    virtual std::string description() const = 0;
};

class SimpleCoffee : public Coffee
{
public:
    double cost() const override
    {
        return 5.0;
    }

    std::string description() const override
    {
        return "Coffee";
    }
};

class CoffeeDecorator : public Coffee
{
protected:
    std::shared_ptr<Coffee> coffee_;

public:
    CoffeeDecorator(std::shared_ptr<Coffee> c)
        : coffee_(std::move(c)) {}
};

class MilkDecorator : public CoffeeDecorator
{
public:
    MilkDecorator(std::shared_ptr<Coffee> c)
        : CoffeeDecorator(std::move(c)) {}

    double cost() const override
    {
        return coffee_->cost() + 1.0;
    }

    std::string description() const override
    {
        return coffee_->description() + ", Milk";
    }
};

class SugarDecorator : public CoffeeDecorator
{
public:
    SugarDecorator(std::shared_ptr<Coffee> c)
        : CoffeeDecorator(std::move(c)) {}

    double cost() const override
    {
        return coffee_->cost() + 0.5;
    }

    std::string description() const override
    {
        return coffee_->description() + ", Sugar";
    }
};

int main()
{
    std::shared_ptr<Coffee> coffee =
        std::make_shared<SimpleCoffee>();

    coffee = std::make_shared<MilkDecorator>(coffee);
    coffee = std::make_shared<SugarDecorator>(coffee);

    std::cout << coffee->description() << '\n';
    std::cout << "Cost: INR " << coffee->cost() << '\n';
}