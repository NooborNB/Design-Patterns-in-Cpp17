#include <iostream>
#include <memory>
#include <list>

class Element;

class Visitor {
 public:
  virtual void visitA(const Element&) = 0;
  virtual void visitB(const Element&) = 0;
  virtual ~Visitor() = default;
};

class ConcreteVisitor : public Visitor {
 public:
  void visitA(const Element&) override
  {
    std::cout << "visit A\n";
  }

  void visitB(const Element&) override
  {
    std::cout << "visit B\n";
  }
};

class Element {
 public:
  virtual void accept(const std::shared_ptr<Visitor>& v) = 0;
  virtual ~Element() = default;
};

class ElementA : public Element {
 public:
  void accept(const std::shared_ptr<Visitor>& v) override
  {
    v->visitA(*this);
  }
};

class ElementB : public Element {
 public:
  void accept(const std::shared_ptr<Visitor>& v) override
  {
    v->visitB(*this);
  }
};

class ObjectStructure {
 public:
  void add(const std::shared_ptr<Element>& e)
  {
    elements.emplace_back(e);
  }

  void remove(const std::shared_ptr<Element>& e)
  {
    elements.remove(e);
  }

  void accept(const std::shared_ptr<Visitor>& visitor)
  {
    for (auto&& x : elements) x->accept(visitor);
  }

 private:
  std::list<std::shared_ptr<Element>> elements;
};

int main()
{
  const std::shared_ptr<Element> a = std::make_shared<ElementA>();
  const std::shared_ptr<Element> b = std::make_shared<ElementB>();

  ObjectStructure o;
  o.add(a);
  o.add(b);

  const std::shared_ptr<Visitor> visitor = std::make_shared<ConcreteVisitor>();
  o.accept(visitor); // visit A\nvisit B\n
}