* 命令模式将请求封装成对象，解耦了调用者与处理者

```cpp
// 处理者
class Receiver {
 public:
  void f() { std::cout << 1; }
};

class Command {
 public:
  virtual void execute() = 0;
  virtual ~Command() = default;
};

template <typename T>
class CommandA : public Command {
 public:
  using Action = std::function<void(T&)>;

  CommandA(const std::shared_ptr<T>& p, Action a)
      : receiver(p), action(std::move(a)) {}

  void execute() override {
    std::cout << "A";
    if (const auto p = receiver.lock()) {
      action(*p);
    }
  }

 private:
  std::weak_ptr<T> receiver;
  Action action;
};

template <typename T>
class CommandB : public Command {
 public:
  using Action = std::function<void(T&)>;

  CommandB(const std::shared_ptr<T>& p, Action a)
      : receiver(p), action(std::move(a)) {}

  void execute() override {
    std::cout << "B";
    if (const auto p = receiver.lock()) {
      action(*p);
    }
  }

 private:
  std::weak_ptr<T> receiver;
  Action action;
};

// 调用者
class Invoker : public Command {
 public:
  void add(const std::shared_ptr<Command>& c) { commands.emplace_back(c); }

  void remove(const std::shared_ptr<Command>& c) {
    commands.remove_if(
        [&](std::weak_ptr<Command>& x) { return x.lock() == c; });
  }

  void execute() override {
    for (auto&& x : commands) {
      if (const auto p = x.lock()) {
        p->execute();
      }
    }
  }

 private:
  std::list<std::weak_ptr<Command>> commands;
};

int main() {
  auto receiver = std::make_shared<Receiver>();
  const std::shared_ptr<Command> commandA =
      std::make_shared<CommandA<Receiver>>(receiver, &Receiver::f);
  const std::shared_ptr<Command> commandB =
      std::make_shared<CommandB<Receiver>>(receiver, &Receiver::f);

  Invoker invoker;
  invoker.add(commandA);
  invoker.add(commandB);
  invoker.execute();  // A1B1
}
```
