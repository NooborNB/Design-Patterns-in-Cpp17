* 用一个备忘录保存源对象状态

```cpp
class Memento {
 public:
  Memento(std::int32_t n = 0) : storeValue(n) {}

  std::int32_t getValue() const { return storeValue; }

 private:
  std::int32_t storeValue;
};
```

* 源对象状态的保存和恢复都通过备忘录来执行

```cpp
class Originator {
 public:
  Originator(std::int32_t n = 0) : value(n) {}

  Memento save() const { return Memento{value}; }

  void load(const Memento& m) { value = m.getValue(); }

  void show() const { std::cout << value << '\n'; }

  void setValue(std::int32_t n) { value = n; }

 private:
  std::int32_t value;
};
```

* 负责人保存一系列备忘录，供源对象使用

```cpp
class Caretaker {
 public:
  Memento& getState(const std::string& s) { return mementos[s]; }

  void setState(const std::string& s, const Memento& m) {
    mementos.try_emplace(s, m);
  }

 private:
  std::unordered_map<std::string, Memento> mementos;
};

int main() {
  Caretaker c;
  Originator o(2200);
  c.setState("state1", o.save());
  o.setValue(7);
  c.setState("state2", o.save());
  o.setValue(4396);
  c.setState("state3", o.save());

  o.load(c.getState("state2"));
  o.show();  // 7
  o.load(c.getState("state1"));
  o.show();  // 2200
  o.load(c.getState("state3"));
  o.show();  // 4396
}
```
