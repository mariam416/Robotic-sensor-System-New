#include "sensor.h"
#include <string>

// Constructor implementation
Sensor::Sensor(int id, std::string name, std::string type, std::string unit)
    : id(id), name(std::move(name)), type(std::move(type)), unit(std::move(unit)),
      lastReading(0.0), status(SensorStatus::OK), isFaulty(false) {
    // No extra code here
}

// Virtual printInfo implementation
void Sensor::printInfo() const {
    std::cout << "Sensor Info:" << std::endl;
    std::cout << "  ID: " << id << std::endl;
    std::cout << "  Name: " << name << std::endl;
    std::cout << "  Type: " << type << std::endl;
    std::cout << "  Unit: " << unit << std::endl;
    std::cout << "  Last Reading: " << lastReading << std::endl;

    // Print status as text
    std::string statusStr;
    switch (status) {
        case SensorStatus::OK: statusStr = "OK"; break;
        case SensorStatus::WARNING: statusStr = "WARNING"; break;
        case SensorStatus::ERROR: statusStr = "ERROR"; break;
    }
    std::cout << "  Status: " << statusStr << std::endl;
    std::cout << "  Faulty: " << (isFaulty ? "Yes" : "No") << std::endl;
    std::cout << std::endl;
}

// setFaulty implementation
void Sensor::setFaulty(bool faulty) {
    isFaulty = faulty;
    if (faulty) {
        status = SensorStatus::ERROR;
    } else {
        status = SensorStatus::OK;
    }
}