* 成员将请求发送给中介者，中介者再将该请求转发给其他成员，从而解耦了成员之间的交互关系

```cpp
class Colleague;

// 中介者接口
class Mediator {
 public:
  virtual void notify(const std::shared_ptr<Colleague>&, std::string_view) = 0;
  virtual ~Mediator() = default;
};

// 成员接口
class Colleague {
 public:
  explicit Colleague(const std::shared_ptr<Mediator>& p) : mediator(p) {}
  virtual void send(std::string_view) = 0;
  virtual void get(std::string_view) const = 0;
  virtual ~Colleague() = default;

 protected:
  std::weak_ptr<Mediator> mediator;
};

class ColleagueA : public Colleague,
                   public std::enable_shared_from_this<ColleagueA> {
 public:
  using Colleague::Colleague;

  void send(std::string_view s) override {
    mediator.lock()->notify(shared_from_this(), s);
  }

  void get(std::string_view s) const override {
    std::cout << "A receive: " << s << '\n';
  }
};

class ColleagueB : public Colleague,
                   public std::enable_shared_from_this<ColleagueB> {
 public:
  using Colleague::Colleague;

  void send(std::string_view s) override {
    mediator.lock()->notify(shared_from_this(), s);
  }

  void get(std::string_view s) const override {
    std::cout << "B receive: " << s << '\n';
  }
};

// 中介者实现
class ConcreteMediator : public Mediator {
 public:
  void add(const std::shared_ptr<Colleague>& c) { colleagues.emplace_back(c); }

  void notify(const std::shared_ptr<Colleague>& c,
              std::string_view s) override {
    for (auto&& x : colleagues) {
      if (const auto p = x.lock()) {
        if (p != c) p->get(s);  // 转发给其他成员
      }
    }
  }

 private:
  std::list<std::weak_ptr<Colleague>> colleagues;
};

int main() {
  auto m = std::make_shared<ConcreteMediator>();
  auto colleagueA = std::make_shared<ColleagueA>(m);
  auto colleagueB = std::make_shared<ColleagueB>(m);

  m->add(colleagueA);
  m->add(colleagueB);

  colleagueA->send("hello");  // B receive: hello
  colleagueB->send("world");  // A receive: world
}
```
