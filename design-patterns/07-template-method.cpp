#include <iostream>

class Beverage
{
public:
    virtual ~Beverage() = default;

    void prepareRecipe()
    {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }

protected:
    void boilWater()
    {
        std::cout << "Boiling water\n";
    }

    void pourInCup()
    {
        std::cout << "Pouring into cup\n";
    }

    virtual void brew() = 0;
    virtual void addCondiments() = 0;
};

class Coffee : public Beverage
{
protected:
    void brew() override
    {
        std::cout << "Brewing coffee\n";
    }

    void addCondiments() override
    {
        std::cout << "Adding milk\n";
    }
};

class Tea : public Beverage
{
protected:
    void brew() override
    {
        std::cout << "Steeping tea\n";
    }

    void addCondiments() override
    {
        std::cout << "Adding lemon\n";
    }
};

int main()
{
    Coffee coffee;
    Tea tea;

    std::cout << "Coffee:\n";
    coffee.prepareRecipe();

    std::cout << "\nTea:\n";
    tea.prepareRecipe();
}