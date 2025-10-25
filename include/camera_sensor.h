#pragma once
#include "sensor.h"

class CameraSensor : public Sensor {
private:
    int nominalFPS;
public:
    CameraSensor(int id, const std::string& name);

    double readData() override;
    void calibrate() override;
};
