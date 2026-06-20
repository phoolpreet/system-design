#include <iostream>
#include <memory>
#include <string>

class Printer
{
public:
    virtual ~Printer() = default;
    virtual void print(const std::string &msg) = 0;
};

class LegacyPrinter
{
public:
    void printText(const std::string &text)
    {
        std::cout << "[Legacy] " << text << '\n';
    }
};

class PrinterAdapter : public Printer
{
private:
    LegacyPrinter &legacy_;

public:
    explicit PrinterAdapter(LegacyPrinter &printer)
        : legacy_(printer)
    {
    }

    void print(const std::string &msg) override
    {
        legacy_.printText(msg);
    }
};

int main()
{
    LegacyPrinter oldPrinter;

    PrinterAdapter adapter(oldPrinter);

    adapter.print("Hello World");
}