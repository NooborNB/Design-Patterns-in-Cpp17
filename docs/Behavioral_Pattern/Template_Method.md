* 在基类定义一个包含多个操作的方法，每个操作在派生类中实现，基类的这个方法就是模板方法。在C++中这种手法称为NVI（non-virtual interface），模板方法是一个非虚函数，其中的操作为虚函数，并且作为私有成员不暴露给外部

```cpp
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
    void f() override { std::cout << 1; }
    void g() override { std::cout << 2; }
    void h() override { std::cout << 3; }
};

class B : public Abstract {
private:
    void f() override { std::cout << 4; }
    void g() override { std::cout << 5; }
    void h() override { std::cout << 6; }
};

int main()
{
    std::unique_ptr<Abstract> a = std::make_unique<A>();
    std::unique_ptr<Abstract> b = std::make_unique<B>();

    a->templateMethod(); // 123
    b->templateMethod(); // 456
}
```
