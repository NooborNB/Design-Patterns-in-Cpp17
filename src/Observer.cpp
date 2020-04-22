#include <iostream>
#include <memory>
#include <list>
#include <cstdint>

class Subject;

class Observer {
public:
    explicit Observer(const std::shared_ptr<Subject>& p) : subject(p) {}
    virtual void update() = 0;
    virtual ~Observer() = default;

protected:
    std::weak_ptr<Subject> subject;
};

class Subject {
public:
    void add(const std::shared_ptr<Observer>& o)
    {
        observers.emplace_back(o);
    }

    void remove(const std::shared_ptr<Observer>& o)
    {
        observers.remove(o);
    }

    void notify()
    {
        for (auto&& x : observers)
        {
            x->update();
        }
    }

    void setValue(std::int32_t n)
    {
        value = n;
    }

    std::int32_t getValue() const
    {
        return value;
    }

private:
    std::list<std::shared_ptr<Observer>> observers;
    std::int32_t value = 0;
};

class ObserverA : public Observer {
public:
    using Observer::Observer;

    void update() override
    {
        if (const auto p = subject.lock())
        {
            std::cout << "Subject value in A: " << p->getValue() << '\n';
        }
    }
};

class ObserverB : public Observer {
public:
    using Observer::Observer;

    void update() override
    {
        if (const auto p = subject.lock())
        {
            std::cout << "Subject value in B: " << p->getValue() << '\n';
        }
    }
};

int main()
{
    auto subject = std::make_shared<Subject>();
    auto a = std::make_shared<ObserverA>(subject);
    auto b = std::make_shared<ObserverB>(subject);

    subject->add(a);
    subject->add(b);

    subject->setValue(3);
    subject->notify(); // subject value in A: 3\nsubject value in B: 3\n
}