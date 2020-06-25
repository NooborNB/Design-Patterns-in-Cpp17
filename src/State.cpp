#include <iostream>
#include <memory>

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