* 责任链模式将对象连成一条链，让每个对象都有机会处理请求，从而解耦了发送者和处理者。发送者不需要关心具体的处理者，只要把请求发送到链上即可。如果当前对象不能处理请求，则沿着链转发给下一个对象，直到请求被一个对象处理为止。对象应按照从特殊到普遍的顺序链接，即处理范围最小的应最先链接
```cpp
class Handler {
public:
    virtual void process(std::int32_t i)
    {
        if (p)
        {
            p->process(i); // 分派给链中的下一对象
        }
        else
        {
            std::cout << i << "can't be processed\n"; // 未指定下一对象则处理失败
        }
    }
    void setNext(std::shared_ptr<Handler> _p)
    {
        p = std::move(_p);
    }
    virtual ~Handler() = default;
private:
    std::shared_ptr<Handler> p;
};

class A : public Handler {
public:
    void process(std::int32_t i) override
    {
        if (i < 10)
        {
            std::cout << i << " processed by A\n";
        }
        else
        {
            Handler::process(i); // 若不能处理则转发给链中下一对象
        }
    }
};

class B : public Handler {
public:
    void process(std::int32_t i) override
    {
        if (i < 100)
        {
            std::cout << i << " processed by B\n";
        }
        else
        {
            Handler::process(i);
        }
    }
};

class C : public Handler {
public:
    void process(std::int32_t i) override
    {
        if (i < 1000)
        {
            std::cout << i << " processed by C\n";
        }
        else
        {
            Handler::process(i);
        }
    }
};

int main()
{
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();
    auto c = std::make_shared<C>();
    a->setNext(b);
    b->setNext(c);
    a->process(9); // 9 processed by A
    a->process(999); // 999 processed by C
    a->process(99); // 99 processed by B
    a->process(9999); // 9999 can't be processed
}
```