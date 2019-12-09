* 目标对象执行相同操作时，如果状态不同，则执行结果也不同。让目标对象持有一个状态对象的指针，目标的操作都转发给状态对象，改变目标的状态即可相应地改变目标操作，看起来就像整个类都被修改了
```cpp
class Connection;

class State {
public:
    virtual void open(const Connection&) const = 0;
    virtual void close(const Connection&) const = 0;
    virtual ~State() = default;
};

class Connection {
public:
    Connection(std::unique_ptr<State> _p) : p(std::move(_p)) {}
    void changeState(std::unique_ptr<State> _p)
    {
        p = std::move(_p);
    }
    void open() const
    {
        p->open(*this);
    }
    void close() const
    {
        p->close(*this);
    }
private:
    std::unique_ptr<State> p;
};

class StateA : public State {
public:
    void open(const Connection&) const override
    {
        std::cout << 1;
    }
    void close(const Connection&) const override
    {
        std::cout << 2;
    }
};

class StateB : public State {
public:
    void open(const Connection&) const override
    {
        std::cout << 3;
    }
    void close(const Connection&) const override
    {
        std::cout << 4;
    }
};

int main()
{
    Connection connection{std::make_unique<StateA>()};
    connection.open(); // 1
    connection.close(); // 2

    connection.changeState(std::make_unique<StateB>());
    connection.open(); // 3
    connection.close(); // 4
}
```