#include <iostream>
#include <memory>
#include <cstdint>
#include <utility>

class Handler {
 public:
  virtual void process(std::int32_t i)
  {
    if (p)
    {
      p->process(i);
    }
    else
    {
      std::cout << i << "can't be processed\n";
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
      Handler::process(i);
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