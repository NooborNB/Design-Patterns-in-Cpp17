#include <iostream>
#include <memory>
#include <unordered_map>

class Flyweight {
public:
    virtual void print() = 0;
    virtual ~Flyweight() = default;
};

class ConcreteFlyweight : public Flyweight {
public:
    explicit ConcreteFlyweight(char _c) : c(_c) {}

    void print() override
    {
        std::cout << c;
    }
private:
    char c;
};

class FlyweightFactory {
public:
    std::shared_ptr<Flyweight> getFlyweight(char c)
    {
        if (const auto it = m.find(c); it != std::end(m))
        {
            std::cout << "existing char\n";
            return it->second;
        }
        std::shared_ptr<Flyweight> p = std::make_shared<ConcreteFlyweight>(c);
        m.try_emplace(c, p);
        return p;
    }

private:
    std::unordered_map<char, std::shared_ptr<Flyweight>> m;
};

int main()
{
    FlyweightFactory factory;
    std::shared_ptr<Flyweight> a = factory.getFlyweight('a');
    std::shared_ptr<Flyweight> b = factory.getFlyweight('a'); // existing char
    std::shared_ptr<Flyweight> c = factory.getFlyweight('b');

    a->print(); // a
    b->print(); // a
    c->print(); // b
}