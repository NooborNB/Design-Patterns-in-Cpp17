#include <iostream>
#include <tuple>
#include <type_traits>

class Shape {
 public:
  virtual void show() = 0;
  virtual ~Shape() = default;
};

template <template <typename> class... T>
class Line : public Shape, public T<Line<>>... {
 public:
  void show() override {
    std::apply([](auto&&... x) { (x.show(), ...); },
               std::forward_as_tuple(T<Line<>>()...));
    std::cout << "line\n";
  }
};

template <template <typename> class... T>
class Text : public Shape, public T<Text<>>... {
 public:
  void show() override {
    std::apply([](auto&&... x) { (x.show(), ...); },
               std::forward_as_tuple(T<Text<>>()...));
    std::cout << "text\n";
  }
};

template <typename T>
class ColorDecorator {
 public:
  void show() {
    if constexpr (std::is_constructible_v<Line<>*, T*>) {
      std::cout << "red ";
    } else {
      std::cout << "black ";
    }
  }
};

template <typename T>
class WeightDecorator {
 public:
  void show() {
    if constexpr (std::is_constructible_v<Line<>*, T*>) {
      std::cout << "bold ";
    } else {
      std::cout << "normal ";
    }
  }
};

int main() {
  Line line1;
  Line<ColorDecorator> line2;
  Line<WeightDecorator> line3;
  Line<ColorDecorator, WeightDecorator> line4;

  Text text1;
  Text<ColorDecorator> text2;
  Text<WeightDecorator> text3;
  Text<ColorDecorator, WeightDecorator> text4;

  line1.show();  // line
  line2.show();  // red line
  line3.show();  // bold line
  line4.show();  // red bold line

  text1.show();  // text
  text2.show();  // black text
  text3.show();  // normal text
  text4.show();  // black normal text
}