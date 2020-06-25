#include <memory>

class Door {
 public:
  virtual ~Door() = default;
};

class Window {
 public:
  virtual ~Window() = default;
};

class House {
 public:
  virtual void setDoor(const Door&) {}
  virtual void setWindow(const Window&) {}
  virtual ~House() = default;
};

class Life {
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

  std::unique_ptr<House> createHouse()
  {
    std::unique_ptr<Door> door = makeDoor();
    std::unique_ptr<Window> window = makeWindow();
    std::unique_ptr<House> house = makeHouse();
    house->setDoor(*door);
    house->setWindow(*window);
    return house;
  }

  virtual ~Life() = default;
};

class WoodHouse : public House {};
class WoodDoor : public Door {};
class WoodWindow : public Window {};

class MyLife : public Life {
 public:
  std::unique_ptr<House> makeHouse() override
  {
    return std::make_unique<WoodHouse>();
  }

  std::unique_ptr<Door> makeDoor() override
  {
    return std::make_unique<WoodDoor>();
  }

  std::unique_ptr<Window> makeWindow() override
  {
    return std::make_unique<WoodWindow>();
  }
};

int main()
{
  MyLife life;
  std::unique_ptr<House> house = life.createHouse();
}