#include <iostream>
#include <memory>
#include <string>

class Image
{
public:
    virtual ~Image() = default;
    virtual void display() = 0;
};

class RealImage : public Image
{
private:
    std::string filename;

    void loadFromDisk()
    {
        std::cout << "Loading image: "
                  << filename << '\n';
    }

public:
    RealImage(const std::string &file)
        : filename(file)
    {
        loadFromDisk();
    }

    void display() override
    {
        std::cout << "Displaying image: "
                  << filename << '\n';
    }
};

class ProxyImage : public Image
{
private:
    std::string filename;
    std::unique_ptr<RealImage> realImage;

public:
    ProxyImage(const std::string &file)
        : filename(file)
    {
    }

    void display() override
    {
        if (!realImage)
        {
            realImage =
                std::make_unique<RealImage>(
                    filename);
        }

        realImage->display();
    }
};

int main()
{
    ProxyImage image("car.jpg");

    std::cout << "Image created\n\n";

    image.display();

    std::cout << '\n';

    image.display();
}