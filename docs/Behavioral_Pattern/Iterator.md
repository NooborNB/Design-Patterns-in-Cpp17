* 提供迭代器用于顺序访问聚合对象中的各个元素，而不暴露对象内部表示

```cpp
template <typename T>
class List;

template <typename T>
class Iterator {
 public:
  Iterator(List<T>& _list) : list(_list) {}

  void operator++() { ++cur; }

  bool isDone() { return cur >= list.size(); }

  T& operator*() { return list[cur]; }

 private:
  List<T>& list;
  std::size_t cur = 0;
};

template <typename T>
class List {
 public:
  Iterator<T> begin() { return Iterator<T>{*this}; }

  void append(T&& x) { data.emplace_back(std::forward<T>(x)); }

  std::size_t size() { return std::size(data); }

  T& operator[](std::size_t n) { return data.at(n); }

 private:
  std::vector<T> data;
};

int main() {
  List<std::int32_t> list;
  list.append(2);
  list.append(3);
  list.append(1);

  for (auto it = list.begin(); !it.isDone(); ++it) {
    std::cout << *it;
  }
}
```
