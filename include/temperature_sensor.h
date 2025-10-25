#pragma once
#include "sensor.h"

class TemperatureSensor : public Sensor {
public:
    TemperatureSensor(int id, const std::string& name);

    double readData() override;
    void calibrate() override;
};
