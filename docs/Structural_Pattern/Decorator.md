* 装饰器可以不改变定义地扩展功能

```cpp
// 定义接口的Component
class Shape {
public:
    virtual void show() = 0;
    virtual ~Shape() = default;
};

// 定义实现的ConcreteComponent
class Line : public Shape {
public:
    void show() override
    {
        std::cout << "line\n";
    }
};

// 持有一个Component指针的Decorator，它提供与Component一致的接口
class Decorator : public Shape {
public:
    Decorator(std::unique_ptr<Shape> p) : shape(std::move(p)) {}

    void show() override
    {
        shape->show();
    }
private:
    std::unique_ptr<Shape> shape;
};

// 扩展接口功能的ConcreteDecorator
class ColorDecorator : public Decorator {
public:
    using Decorator::Decorator;

    void show() override
    {
        std::cout << "red ";
        Decorator::show();
    }
};

int main()
{
    std::unique_ptr<Shape> colorDecorator = std::make_unique<ColorDecorator>(std::make_unique<Line>());
    colorDecorator->show(); // red line
}
```

* 用模板实现装饰器

```cpp
class Shape {
public:
    virtual void show() = 0;
    virtual ~Shape() = default;
};

template<typename... T>
class Line : public Shape, public T... {
public:
    void show() override
    {
        std::apply([](auto&&... x) { (x.show(), ...); }, std::make_tuple(T()...));
        std::cout << "line\n";
    }
};

class ColorDecorator {
public:
    void show()
    {
        std::cout << "red ";
    }
};

class WeightDecorator {
public:
    void show()
    {
        std::cout << "bold ";
    }
};

int main()
{
    Line line1;
    Line<ColorDecorator> line2;
    Line<WeightDecorator> line3;
    Line<ColorDecorator, WeightDecorator> line4;

    line1.show(); // line
    line2.show(); // red line
    line3.show(); // bold line
    line4.show(); // red bold line
}
```

* 结合CRTP

```cpp
class Shape {
public:
    virtual void show() = 0;
    virtual ~Shape() = default;
};

template<template<typename>class... T>
class Line : public Shape, public T<Line<>>... {
public:
    void show() override
    {
        std::apply([](auto&&... x) { (x.show(), ...); }, std::make_tuple(T<Line<>>()...));
        std::cout << "line\n";
    }
};

template<template<typename>class... T>
class Text : public Shape, public T<Text<>>... {
public:
    void show() override
    {
        std::apply([](auto&&... x) { (x.show(), ...); }, std::make_tuple(T<Text<>>()...));
        std::cout << "text\n";
    }
};

template<typename T>
class ColorDecorator {
public:
    void show()
    {
        if constexpr (std::is_constructible_v<Line<>*, T*>)
        {
            std::cout << "red ";
        }
        else
        {
            std::cout << "black ";
        }
    }
};

template<typename T>
class WeightDecorator {
public:
    void show()
    {
        if constexpr (std::is_constructible_v<Line<>*, T*>)
        {
            std::cout << "bold ";
        }
        else
        {
            std::cout << "normal ";
        }
    }
};

int main()
{
    Line line1;
    Line<ColorDecorator> line2;
    Line<WeightDecorator> line3;
    Line<ColorDecorator, WeightDecorator> line4;

    Text text1;
    Text<ColorDecorator> text2;
    Text<WeightDecorator> text3;
    Text<ColorDecorator, WeightDecorator> text4;

    line1.show(); // line
    line2.show(); // red line
    line3.show(); // bold line
    line4.show(); // red bold line

    text1.show(); // text
    text2.show(); // black text
    text3.show(); // normal text
    text4.show(); // black normal text
}
```
