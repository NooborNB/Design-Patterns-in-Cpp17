* 适配器提供了源接口到目标接口的转换

```cpp
class Target {  // 提供给用户的类
 public:
  virtual void f() = 0;
  virtual ~Target() = default;
};

class Adaptee {  // 提供实际功能的类
 public:
  virtual void g() { std::cout << 1; }
  virtual ~Adaptee() = default;
};

class Adapter : public Target, public Adaptee {  // 适配器
 public:
  void f() override { Adaptee::g(); }
};

int main() {
  std::unique_ptr<Target> target = std::make_unique<Adapter>();
  target->f();  // 1
}
```

* 上述采用多继承的形式称为类适配器，另一种采用组合的形式称为对象适配器

```cpp
class Adapter : public Target {
 public:
  Adapter() : p(std::make_unique<Adaptee>()) {}
  void f() override { p->g(); }

 private:
  std::unique_ptr<Adaptee> p;
};
```
