#include <iostream>

class Scanner {
 public:
  void scan()
  {
    std::cout << "generate token\n";
  }
};

class Parser {
 public:
  void parse()
  {
    std::cout << "build syntax tree\n";
  }
};

class CodeGenerator {
 public:
  void generateCode()
  {
    std::cout << "generate machine code\n";
  }
};

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