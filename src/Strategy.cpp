#include <iostream>
#include <memory>

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

  void f() const { p->f(); }

 private:
  std::unique_ptr<Strategy> p;
};

int main() {
  const Context a{std::make_unique<StrategyA>()};
  const Context b{std::make_unique<StrategyB>()};

  a.f();  // 1
  b.f();  // 2
}