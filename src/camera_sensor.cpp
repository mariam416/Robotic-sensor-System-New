#include "camera_sensor.h"
#include "utils.h"
#include <iostream>

CameraSensor::CameraSensor(int id, const std::string& name)
    : Sensor(id, name, "Camera", "FPS"), nominalFPS(30) {}

double CameraSensor::readData() {
    // FPS between 15 and 60
    lastReading = Utils::randomDouble(15.0, 60.0);

    if (lastReading < 20.0)
        status = SensorStatus::WARNING;
    else
        status = SensorStatus::OK;

    // Occasional camera drop/fault
    if (Utils::chance(0.008)) {
        setFaulty(true);
    }

    return lastReading;
}

void CameraSensor::calibrate() {
    lastReading = static_cast<double>(nominalFPS);
    status = SensorStatus::OK;
    setFaulty(false);
}
