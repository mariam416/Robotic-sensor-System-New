#pragma once
#include "sensor.h"

class LidarSensor : public Sensor {
private:
    double noiseFactor;
public:
    LidarSensor(int id, const std::string& name);

    double readData() override;
    void calibrate() override;
};
