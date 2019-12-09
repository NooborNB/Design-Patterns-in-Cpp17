* 策略模式和状态模式的实现几乎一样：目标对象持有一个策略对象的指针，并把操作转发给策略对象。区别在于，策略由用户提供，针对单个操作，目标不可切换策略，而状态由内部提供，可以切换，并且会改变目标的所有操作
```cpp
class Strategy {
public:
    virtual void f() = 0;
    virtual ~Strategy() = default;
};

class StrategyA : public Strategy {
public:
    void f() override { std::cout << 1; }
};

class StrategyB : public Strategy {
public:
    void f() override { std::cout << 2; }
};

class Context {
public:
    Context(std::unique_ptr<Strategy> _p) : p(std::move(_p)) {}
    void f() const
    {
        p->f();
    }
private:
    std::unique_ptr<Strategy> p;
};

int main()
{
    const Context a{ std::make_unique<StrategyA>() };
    const Context b{ std::make_unique<StrategyB>() };
    a.f(); // 1
    b.f(); // 2
}
```