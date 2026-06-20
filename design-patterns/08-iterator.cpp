#include <iostream>
#include <memory>
#include <vector>

template <typename T>
class Iterator
{
public:
    virtual ~Iterator() = default;

    virtual bool hasNext() const = 0;
    virtual T next() = 0;
};

template <typename T>
class MyCollection
{
private:
    std::vector<T> items_;

public:
    void add(const T &item)
    {
        items_.push_back(item);
    }

    const std::vector<T> &items() const
    {
        return items_;
    }
};

template <typename T>
class VectorIterator : public Iterator<T>
{
private:
    const std::vector<T> &items_;
    size_t index_ = 0;

public:
    explicit VectorIterator(
        const std::vector<T> &items)
        : items_(items)
    {
    }

    bool hasNext() const override
    {
        return index_ < items_.size();
    }

    T next() override
    {
        return items_[index_++];
    }
};

int main()
{
    MyCollection<int> collection;

    collection.add(10);
    collection.add(20);
    collection.add(30);

    VectorIterator<int> it(collection.items());

    while (it.hasNext())
    {
        std::cout << it.next() << '\n';
    }
}