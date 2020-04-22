#include <iostream>
#include <memory>

class Abstract {
public:
    void templateMethod()
    {
        f();
        g();
        h();
    }

    virtual ~Abstract() = default;

private:
    virtual void f() = 0;
    virtual void g() = 0;
    virtual void h() = 0;
};

class A : public Abstract {
private:
    void f() override
    {
        std::cout << 1;
    }

    void g() override
    {
        std::cout << 2;
    }

    void h() override
    {
        std::cout << 3;
    }
};

class B : public Abstract {
private:
    void f() override
    {
        std::cout << 4;
    }

    void g() override
    {
        std::cout << 5;
    }

    void h() override
    {
        std::cout << 6;
    }
};

int main()
{
    std::unique_ptr<Abstract> a = std::make_unique<A>();
    std::unique_ptr<Abstract> b = std::make_unique<B>();

    a->templateMethod(); // 123
    b->templateMethod(); // 456
}