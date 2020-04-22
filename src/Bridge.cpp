#include <iostream>
#include <memory>
#include <utility>

class AbstractionImpl {
public:
    virtual void fImpl() = 0;
    virtual ~AbstractionImpl() = default;
};

class AImpl1 : public AbstractionImpl {
public:
    void fImpl() override
    {
        std::cout << 1;
    }
};

class AImpl2 : public AbstractionImpl {
public:
    void fImpl() override
    {
        std::cout << 2;
    }
};

class Abstraction {
public:
    virtual void f() = 0;
    virtual ~Abstraction() = default;
};

class A1 : public Abstraction {
public:
    explicit A1(std::unique_ptr<AbstractionImpl> _p) : p(std::move(_p)) {}

    void f() override
    {
        p->fImpl();
    }

private:
    std::unique_ptr<AbstractionImpl> p;
};

class A2 : public Abstraction {
public:
    explicit A2(std::unique_ptr<AbstractionImpl> _p) : p(std::move(_p)) {}

    void f() override
    {
        p->fImpl();
    }

private:
    std::unique_ptr<AbstractionImpl> p;
};

int main()
{
    std::unique_ptr<Abstraction> a1 = std::make_unique<A1>(std::make_unique<AImpl1>());
    std::unique_ptr<Abstraction> a2 = std::make_unique<A1>(std::make_unique<AImpl2>());
    std::unique_ptr<Abstraction> a3 = std::make_unique<A2>(std::make_unique<AImpl1>());
    std::unique_ptr<Abstraction> a4 = std::make_unique<A2>(std::make_unique<AImpl2>());

    a1->f(); // 1
    a2->f(); // 2
    a3->f(); // 1
    a4->f(); // 2
}