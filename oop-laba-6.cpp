#include <iostream>
#include <string>
#include <vector>
#include <memory>

enum class Material { Plastic, Metal, Glass };

class MeasurementDevice {
protected:
  std::string name;
  std::string unit;
  double minValue;
  double maxValue;
  Material material;
  bool isDeviceActiveForMeasurement;

  static const std::vector<std::string> materials;

public:
  MeasurementDevice() : isDeviceActiveForMeasurement(false) {}

  virtual ~MeasurementDevice() = default;

  virtual void initialize() {
    std::cout << "Enter device name: ";
    std::getline(std::cin >> std::ws, name);
    std::cout << "Enter unit: ";
    std::getline(std::cin >> std::ws, unit);
    std::cout << "Enter min value: ";
    std::cin >> minValue;
    std::cout << "Enter max value: ";
    std::cin >> maxValue;
    int materialChoice;
    do {
      std::cout << "Enter material (1 for Plastic, 2 for Metal, 3 for Glass): ";
      std::cin >> materialChoice;
      if (materialChoice >= 1 && materialChoice <= 3) {
        material = static_cast<Material>(materialChoice - 1);
        break;
      }
      else {
        std::cout << "Invalid choice. Please try again." << std::endl;
      }
    } while (true);
  }

  virtual void startMeasuring() {
    if (!isDeviceActiveForMeasurement) {
      std::cout << "\nStart of measurement" << std::endl;
      isDeviceActiveForMeasurement = true;
    }
  }

  virtual void stopMeasuring() {
    if (isDeviceActiveForMeasurement) {
      std::cout << "End of measurement\n" << std::endl;
      isDeviceActiveForMeasurement = false;
    }
  }

  virtual void print() const {
    std::cout << "============" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Unit: " << unit << std::endl;
    std::cout << "Min Value: " << minValue << std::endl;
    std::cout << "Max Value: " << maxValue << std::endl;
    std::cout << "Material: " << materials[static_cast<int>(material)] << std::endl;
    std::cout << "============" << std::endl;
  }

  virtual void setMeasurement() = 0; // чиста віртуальна функція

  void setName() {
    std::cout << "Enter new device name: ";
    std::getline(std::cin >> std::ws, name);
    print();
  }

  void setUnit() {
    std::cout << "Enter new unit: ";
    std::getline(std::cin >> std::ws, unit);
    print();
  }

  void setMinValue() {
    std::cout << "Enter new min value: ";
    std::cin >> minValue;
    print();
  }

  void setMaxValue() {
    std::cout << "Enter new max value: ";
    std::cin >> maxValue;
    print();
  }

  void setMaterial() {
    int materialChoice;
    do {
      std::cout << "Enter material (1 for Plastic, 2 for Metal, 3 for Glass): ";
      std::cin >> materialChoice;
      if (materialChoice >= 1 && materialChoice <= 3) {
        material = static_cast<Material>(materialChoice - 1);
        break;
      }
      else {
        std::cout << "Invalid choice. Please try again." << std::endl;
      }
    } while (true);
    print();
  }
};

const std::vector<std::string> MeasurementDevice::materials = { "Plastic", "Metal", "Glass" };

class TemperatureMeasurementDevice : public MeasurementDevice {
private:
  double currentTemperature;
  enum class TemperatureScale { Celsius, Fahrenheit, Kelvin };
  TemperatureScale temperatureScale;

  static const std::vector<std::string> scales;

public:
  TemperatureMeasurementDevice() : currentTemperature(0) {}

  void initialize() override {
    MeasurementDevice::initialize();
    int userChoice;
    do {
      std::cout << "Enter temperature scale (1 for Celsius, 2 for Fahrenheit, 3 for Kelvin): ";
      std::cin >> userChoice;
      if (userChoice >= 1 && userChoice <= 3) {
        temperatureScale = static_cast<TemperatureScale>(userChoice - 1);
        break;
      }
      else {
        std::cout << "Invalid choice. Please try again." << std::endl;
      }
    } while (true);
  }

  void startMeasuring() override {
    MeasurementDevice::startMeasuring();
    std::cout << "Temperature measurement started" << std::endl;
  }

  void stopMeasuring() override {
    MeasurementDevice::stopMeasuring();
    std::cout << "Temperature measurement stopped" << std::endl;
  }

  void print() const override {
    MeasurementDevice::print();
    printTemperature();
  }

  void setMeasurement() override {
    setCurrentTemperature();
    print();
  }

  void setCurrentTemperature() {
    if (isDeviceActiveForMeasurement) {
      double rangeTemp;
      do {
        std::cout << "Enter current temperature (" << minValue << " - " << maxValue << "): ";
        std::cin >> rangeTemp;
        if (rangeTemp < minValue || rangeTemp > maxValue) {
          std::cout << "Temperature out of range. Please enter a value between " << minValue << " and " << maxValue << "." << std::endl;
        }
        else {
          currentTemperature = rangeTemp;
          break;
        }
      } while (true);
    }
    else {
      std::cout << "Device is not ACTIVE!!!" << std::endl;
    }
  }

  void printTemperature() const {
    std::cout << "Current Temperature: " << currentTemperature << " " << scales[static_cast<int>(temperatureScale)] << std::endl;
  }

  void setTemperatureScale() {
    int userChoice;
    do {
      std::cout << "Enter temperature scale (1 for Celsius, 2 for Fahrenheit, 3 for Kelvin): ";
      std::cin >> userChoice;
      if (userChoice >= 1 && userChoice <= 3) {
        temperatureScale = static_cast<TemperatureScale>(userChoice - 1);
        break;
      }
      else {
        std::cout << "Invalid choice. Please try again." << std::endl;
      }
    } while (true);
    print();
  }
};

const std::vector<std::string> TemperatureMeasurementDevice::scales = { "Celsius", "Fahrenheit", "Kelvin" };

class AdvancedTemperatureMeasurementDevice : public TemperatureMeasurementDevice {
private:
  double calibrationOffset;

public:
  AdvancedTemperatureMeasurementDevice() : calibrationOffset(0) {}

  void initialize() override {
    TemperatureMeasurementDevice::initialize();
    std::cout << "Enter calibration offset: ";
    std::cin >> calibrationOffset;
  }

  void print() const override {
    TemperatureMeasurementDevice::print();
    std::cout << "Calibration Offset: " << calibrationOffset << std::endl;
  }

  void setMeasurement() override {
    TemperatureMeasurementDevice::setMeasurement();
    applyCalibration();
  }

  void applyCalibration() {
    if (isDeviceActiveForMeasurement) {
      std::cout << "Applying calibration offset: " << calibrationOffset << std::endl;
    }
  }

  void setCalibrationOffset() {
    std::cout << "Enter new calibration offset: ";
    std::cin >> calibrationOffset;
    print();
  }
};

int main() {
  std::vector<std::unique_ptr<MeasurementDevice>> devices;
  int currentDeviceIndex = -1;
  int option;

  do {
    std::cout << "\nMain Menu:\n1. Add new device\n2. Select device\n3. Start measuring\n4. Stop measuring\n5. Print device info\n6. Set measurement\n7. Change device attributes\n0. Exit\nEnter option: ";
    std::cin >> option;

    switch (option) {
    case 1: {
      int deviceType;
      std::cout << "Enter device type (1 for Temperature, 2 for Advanced Temperature): ";
      std::cin >> deviceType;

      std::unique_ptr<MeasurementDevice> device;
      if (deviceType == 1) {
        device = std::make_unique<TemperatureMeasurementDevice>();
      }
      else if (deviceType == 2) {
        device = std::make_unique<AdvancedTemperatureMeasurementDevice>();
      }

      if (device) {
        device->initialize();
        devices.push_back(std::move(device));
        currentDeviceIndex = devices.size() - 1;
      }
      break;
    }
    case 2: {
      if (devices.empty()) {
        std::cout << "No devices available. Please add a new device first." << std::endl;
        break;
      }

      std::cout << "Select device index (1 to " << devices.size() << "): ";
      std::cin >> currentDeviceIndex;
      if (currentDeviceIndex < 1 || currentDeviceIndex > devices.size()) {
        std::cout << "Invalid device index." << std::endl;
        currentDeviceIndex = -1;
      }
      else {
        currentDeviceIndex--;
      }
      break;
    }
    case 3: {
      if (currentDeviceIndex != -1) {
        devices[currentDeviceIndex]->startMeasuring();
      }
      else {
        std::cout << "No device selected." << std::endl;
      }
      break;
    }
    case 4: {
      if (currentDeviceIndex != -1) {
        devices[currentDeviceIndex]->stopMeasuring();
      }
      else {
        std::cout << "No device selected." << std::endl;
      }
      break;
    }
    case 5: {
      if (currentDeviceIndex != -1) {
        devices[currentDeviceIndex]->print();
      }
      else {
        std::cout << "No device selected." << std::endl;
      }
      break;
    }
    case 6: {
      if (currentDeviceIndex != -1) {
        devices[currentDeviceIndex]->setMeasurement();
      }
      else {
        std::cout << "No device selected." << std::endl;
      }
      break;
    }
    case 7: {
      if (currentDeviceIndex != -1) {
        int attributeOption;
        std::cout << "Change attribute:\n1. Name\n2. Unit\n3. Min Value\n4. Max Value\n5. Material\n6. Temperature Scale (if applicable)\n7. Calibration Offset (if applicable)\nEnter option: ";
        std::cin >> attributeOption;

        switch (attributeOption) {
        case 1: devices[currentDeviceIndex]->setName(); break;
        case 2: devices[currentDeviceIndex]->setUnit(); break;
        case 3: devices[currentDeviceIndex]->setMinValue(); break;
        case 4: devices[currentDeviceIndex]->setMaxValue(); break;
        case 5: devices[currentDeviceIndex]->setMaterial(); break;
        case 6: {
          auto* tempDevice = dynamic_cast<TemperatureMeasurementDevice*>(devices[currentDeviceIndex].get());
          if (tempDevice) {
            tempDevice->setTemperatureScale();
          }
          else {
            std::cout << "Selected device is not a TemperatureMeasurementDevice." << std::endl;
          }
          break;
        }
        case 7: {
          auto* advTempDevice = dynamic_cast<AdvancedTemperatureMeasurementDevice*>(devices[currentDeviceIndex].get());
          if (advTempDevice) {
            advTempDevice->setCalibrationOffset();
          }
          else {
            std::cout << "Selected device is not an AdvancedTemperatureMeasurementDevice." << std::endl;
          }
          break;
        }
        default: std::cout << "Invalid option." << std::endl; break;
        }
      }
      else {
        std::cout << "No device selected." << std::endl;
      }
      break;
    }
    case 0: break;
    default: std::cout << "Invalid option. Please try again." << std::endl; break;
    }
  } while (option != 0);

  return 0;
}
