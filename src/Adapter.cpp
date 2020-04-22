#include <iostream>
#include <memory>

class Target {
public:
    virtual void f() = 0;
    virtual ~Target() = default;
};

class Adaptee {
public:
    virtual void g()
    {
        std::cout << 1;
    }

    virtual ~Adaptee() = default;
};

class Adapter : public Target, public Adaptee {
public:
    void f() override
    {
        Adaptee::g();
    }
};

int main()
{
    std::unique_ptr<Target> target = std::make_unique<Adapter>();
    target->f(); // 1
}