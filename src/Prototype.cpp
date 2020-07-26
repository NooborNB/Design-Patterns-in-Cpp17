#include <cassert>
#include <memory>

class Prototype {
 public:
  virtual std::unique_ptr<Prototype> clone() = 0;
  virtual ~Prototype() = default;
};

class A : public Prototype {
 public:
  std::unique_ptr<Prototype> clone() override {
    return std::make_unique<A>(*this);
  }
};

int main() {
  std::unique_ptr<Prototype> p = std::make_unique<A>();
  std::unique_ptr<Prototype> q = p->clone();
  assert(p != q);
}