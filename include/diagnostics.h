#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "sensor.h"
#include "sensor_manager.h"
#include "utils.h"

// Diagnostics system - Singleton optional
class Diagnostics {
private:
    static std::unique_ptr<Diagnostics> instance;
    Diagnostics() = default;

public:
    static Diagnostics& getInstance();

    // Prevent copying
    Diagnostics(const Diagnostics&) = delete;
    Diagnostics& operator=(const Diagnostics&) = delete;

    // Core functionality
    std::vector<std::shared_ptr<Sensor>> detectFaultySensors(SensorManager& manager);
    std::string generateReport(SensorManager& manager);
    void saveReport(const std::string& path, const std::string& report);
};

#endif 
