#include <iostream>
#include <memory>

class Graphic {
public:
    virtual void show() = 0;
    virtual ~Graphic() = default;
};

class Image : public Graphic {
public:
    void show() override
    {
        std::cout << 1;
    }
};

class Proxy : public Graphic {
public:
    void show() override
    {
        getImage().show();
    }
protected:
    Image& getImage()
    {
        if (!p) p = std::make_unique<Image>();
        return *p;
    }
private:
    std::unique_ptr<Image> p;
};

int main()
{
    std::unique_ptr<Graphic> proxy = std::make_unique<Proxy>();
    proxy->show(); // 1
}