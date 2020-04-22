* 原型模式提供一个clone接口来创建新的对象，避免了创建相同对象时要编写的重复代码

```cpp
class Prototype {
public:
    virtual std::unique_ptr<Prototype> clone() = 0;
    virtual ~Prototype() = default;
};

class A : public Prototype {
public:
    std::unique_ptr<Prototype> clone() override
    {
        return std::make_unique<A>(*this);
    }
};

int main()
{
    std::unique_ptr<Prototype> p = std::make_unique<A>();
    std::unique_ptr<Prototype> q = p->clone();
    assert(p != q);
}
```