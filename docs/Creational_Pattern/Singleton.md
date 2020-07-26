* 单例模式保证一个类只有一个实例

```cpp
template <typename T>
class Singleton {
 public:
  static T& getInstance();
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;

 private:
  Singleton() = default;
  ~Singleton() = default;
};

template <typename T>
T& Singleton<T>::getInstance() {
  static T inst;
  return inst;
}

class A {};

int main() {
  auto& a = Singleton<A>::getInstance();
  auto& b = Singleton<A>::getInstance();
  assert(&a == &b);
}
```