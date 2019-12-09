#include <cassert>

class Singleton {
public:
    static Singleton& getInstance();
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
private:
    Singleton() = default;
    ~Singleton() = default;
};

Singleton& Singleton::getInstance()
{
    static Singleton instance;
    return instance;
}

int main()
{
    auto& a = Singleton::getInstance();
    auto& b = Singleton::getInstance();
    assert(&a == &b);
}