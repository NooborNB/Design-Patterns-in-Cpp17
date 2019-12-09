* 抽象工厂能生成一系列相关的局部产品
```cpp
class HouseFactory {
public:
    virtual std::unique_ptr<Door> makeDoor()
    {
        return std::make_unique<Door>();
    }
    virtual std::unique_ptr<Window> makeWindow()
    {
        return std::make_unique<Window>();
    }
    virtual std::unique_ptr<House> makeHouse()
    {
        return std::make_unique<House>();
    }
    virtual ~HouseFactory() = default;
};
```
* 用这个抽象工厂生成的局部产品即可组合成一个完整的产品
```cpp
class Life {
public:
    std::unique_ptr<House> createHouse(HouseFactory& factory)
    {
        std::unique_ptr<Door> door = factory.makeDoor();
        std::unique_ptr<Window> window = factory.makeWindow();
        std::unique_ptr<House> house = factory.makeHouse();
        house->setDoor(*door);
        house->setWindow(*window);
        return house;
    }
};

int main()
{
    Life life;
    HouseFactory factory;
    std::unique_ptr<House> house = life.createHouse(factory); 
}
```
* 继承这个抽象工厂，即可对局部产品进行修改
```cpp
class WoodDoor : public Door {};
class WoodWindow : public Window {};
class WoodHouse : public House {};

class WoodHouseFactory : public HouseFactory {
public:
    std::unique_ptr<Door> makeDoor() override
    {
        return std::make_unique<WoodDoor>();
    }
    std::unique_ptr<Window> makeWindow() override
    {
        return std::make_unique<WoodWindow>();
    }
    std::unique_ptr<House> makeHouse() override
    {
        return std::make_unique<WoodHouse>();
    }
};

int main()
{
    Life life;
    WoodHouseFactory factory;
    std::unique_ptr<House> house = life.createHouse(factory);
}
```