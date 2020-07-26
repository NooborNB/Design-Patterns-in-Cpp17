* 组合模式为组合对象提供了与单体对象一致的处理方式，从而使得用户可以忽略两者的差异并以统一方式使用

```cpp
class Shape {
 public:
  virtual void show() = 0;
  virtual void add(const std::shared_ptr<Shape>&) {}
  virtual void remove(const std::shared_ptr<Shape>&) {}

  virtual std::shared_ptr<Shape> getChild(std::size_t) { return nullptr; }

  virtual ~Shape() = default;
};

class Line : public Shape {  // 单体的线对象，除了show()其他均使用默认实现
 public:
  void show() override { std::cout << 1; }
};

class Rect : public Shape {  // 单体的矩形对象，除了show()其他均使用默认实现
 public:
  void show() override { std::cout << 2; }
};

class Picture : public Shape {  // 包含多个单体对象的组合对象
 public:
  void show() override  // 提供与单体对象一致的接口
  {
    for (auto&& x : shapes) x->show();
  }

  void add(const std::shared_ptr<Shape>& s) override { shapes.emplace_back(s); }

  void remove(const std::shared_ptr<Shape>& s) override {
    if (const auto it = std::find(std::begin(shapes), std::end(shapes), s);
        it != std::end(shapes)) {
      shapes.erase(it);
    }
  }

  std::shared_ptr<Shape> getChild(std::size_t n) override {
    return shapes.at(n);
  }

 private:
  std::vector<std::shared_ptr<Shape>> shapes;
};

int main() {
  std::unique_ptr<Shape> picture = std::make_unique<Picture>();
  const auto line = std::make_shared<Line>();
  const auto rect = std::make_shared<Rect>();

  picture->add(line);
  picture->add(rect);
  picture->show();  // 12

  picture->remove(line);
  picture->show();  // 2
}
```
