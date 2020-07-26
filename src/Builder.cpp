#include <memory>
#include <string_view>

class DeviceSuite {
 public:
  void setMouse(std::string_view) {}
  void setKeyboard(std::string_view) {}
  void setHeadphone(std::string_view) {}
};

class GameDevice {
 public:
  virtual void buildMouse() = 0;
  virtual void buildKeyboard() = 0;
  virtual void buildHeadphone() = 0;
  virtual DeviceSuite& getDevice() const = 0;
  virtual ~GameDevice() = default;
};

class LOLGameDevice : public GameDevice {
 public:
  LOLGameDevice() : device(std::make_unique<DeviceSuite>()) {}

  void buildMouse() override { device->setMouse("Logitech"); }

  void buildKeyboard() override { device->setKeyboard("Filco"); }

  void buildHeadphone() override { device->setHeadphone("Sennheiser"); }

  DeviceSuite& getDevice() const override { return *device; }

 private:
  std::unique_ptr<DeviceSuite> device;
};

class DNFGameDevice : public GameDevice {
 public:
  DNFGameDevice() : device(std::make_unique<DeviceSuite>()) {}

  void buildMouse() override { device->setMouse("Razer"); }

  void buildKeyboard() override { device->setKeyboard("Cherry"); }

  void buildHeadphone() override { device->setHeadphone("Beyerdynamic"); }

  DeviceSuite& getDevice() const override { return *device; }

 private:
  std::unique_ptr<DeviceSuite> device;
};

class Life {
 public:
  DeviceSuite& createDevice(GameDevice& builder) {
    builder.buildMouse();
    builder.buildKeyboard();
    builder.buildHeadphone();
    return builder.getDevice();
  }
};

int main() {
  Life life;
  LOLGameDevice LOLBuilder;
  DNFGameDevice DNFBuilder;

  DeviceSuite LOLDevice = life.createDevice(LOLBuilder);
  DeviceSuite DNFDevice = life.createDevice(DNFBuilder);
}