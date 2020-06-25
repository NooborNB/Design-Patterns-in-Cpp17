* 外观模式为一组子系统提供了一个高层接口，用户无需了解各个子系统的内部联系，只需要使用此高层接口

```cpp
class Scanner {
 public:
  void scan() { std::cout << "generate token\n"; }
};

class Parser {
 public:
  void parse() { std::cout << "build syntax tree\n"; }
};

class CodeGenerator {
 public:
  void generateCode() { std::cout << "generate machine code\n"; }
};

// 提供高层接口的Facade类
class Compiler {
 public:
  void run()
  {
    Scanner s;
    s.scan();

    Parser p;
    p.parse();

    CodeGenerator c;
    c.generateCode();
  }
};

int main()
{
  Compiler compiler;
  compiler.run();
}
```