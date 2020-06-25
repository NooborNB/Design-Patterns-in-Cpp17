* 建造者本身只定义接口，由不同实现定义实现类

```cpp
// 提供接口的 Builder
class GameDevice {
 public:
  virtual void buildMouse() = 0;
  virtual void buildKeyboard() = 0;
  virtual void buildHeadphone() = 0;
  virtual DeviceSuite& getDevice() const = 0;
  virtual ~GameDevice() = default;
};

// 定义一个实现类
class LOLGameDevice : public GameDevice {
 public:
  LOLGameDevice() : device(std::make_unique<DeviceSuite>()) {}

  void buildMouse() override
  {
    device->setMouse("Logitech");
  }

  void buildKeyboard() override
  {
    device->setKeyboard("Filco");
  }

  void buildHeadphone() override
  {
    device->setHeadphone("Sennheiser");
  }

  DeviceSuite& getDevice() const override
  {
    return *device;
  }

 private:
  std::unique_ptr<DeviceSuite> device;
};

// 还可以继续定义其他实现类，根据需要可以有无数种实现
class DNFGameDevice : public GameDevice {
 public:
  DNFGameDevice() : device(std::make_unique<DeviceSuite>()) {}

  void buildMouse() override
  {
    device->setMouse("Razer");
  }

  void buildKeyboard() override
  {
    device->setKeyboard("Cherry");
  }

  void buildHeadphone() override
  {
    device->setHeadphone("Beyerdynamic");
  }

  DeviceSuite& getDevice() const override
  {
    return *device;
  }

 private:
  std::unique_ptr<DeviceSuite> device;
};
```

* 用实现类构建一个完整产品

```cpp
class Life {
 public:
  DeviceSuite& createDevice(GameDevice& builder)
  {
    builder.buildMouse();
    builder.buildKeyboard();
    builder.buildHeadphone();
    return builder.getDevice();
  }
};

int main()
{
  Life life;
  LOLGameDevice LOLBuilder;
  DNFGameDevice DNFBuilder;

  DeviceSuite LOLDevice = life.createDevice(LOLBuilder);
  DeviceSuite DNFDevice = life.createDevice(DNFBuilder);
}
```
