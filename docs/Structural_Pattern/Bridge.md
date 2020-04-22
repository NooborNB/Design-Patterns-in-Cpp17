* 桥接模式分离了接口部分和实现部分，使其可以独立变化。这样就可以在不影响接口部分的情况下修改实现部分，接口部分的代码无需重新编译，从而降低了编译依赖，这种手法在C++中称为[pImpl（Pointer to implementation）](https://en.cppreference.com/w/cpp/language/pimpl)

```cpp
class AImpl { // 提供基础操作的实现部分
public:
    void fImpl() {}
};

class A { // 提供给用户的接口部分
public:
    A() : p(std::make_unique<AImpl>()) {}
    void f() { p->fImpl(); } // 将请求转发给实现类
private:
    std::unique_ptr<AImpl> p;
};

int main()
{
    A a;
    a.f();
}
```

* 当有多个实现时

```cpp
class AbstractionImpl { // 定义实现部分的抽象类
public:
    virtual void fImpl() = 0;
    virtual ~AbstractionImpl() = default;
};

class AImpl1 : public AbstractionImpl { // 具体的实现类1
public:
    void fImpl() override { std::cout << 1; }
};

class AImpl2 : public AbstractionImpl { // 具体的实现类2
public:
    void fImpl() override { std::cout << 2; }
};

class Abstraction { // 定义接口部分的抽象类
public:
    virtual void f() = 0;
    virtual ~Abstraction() = default;
};

class A1 : public Abstraction { // 接口类的扩充类1
public:
    explicit A1(std::unique_ptr<AbstractionImpl> _p) : p(std::move(_p)) {}
    void f() override { p->fImpl(); } // 将请求转发给实现类
private:
    std::unique_ptr<AbstractionImpl> p;
};

class A2 : public Abstraction { // 接口类的扩充类2
public:
    explicit A2(std::unique_ptr<AbstractionImpl> _p) : p(std::move(_p)) {}
    void f() override { p->fImpl(); }
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
```
