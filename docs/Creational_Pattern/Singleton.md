* 单例模式保证一个类只有一个实例
```cpp
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
    static Singleton instance; // 线程安全的初始化
    return instance;
}

int main()
{
    auto& a = Singleton::getInstance();
    auto& b = Singleton::getInstance();
    assert(&a == &b);
}
```