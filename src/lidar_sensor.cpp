#include "lidar_sensor.h"
#include "utils.h"
#include <cmath>
#include <iostream>

LidarSensor::LidarSensor(int id, const std::string& name)
    : Sensor(id, name, "Lidar", "m"), noiseFactor(0.1) {}

double LidarSensor::readData() {
    double baseValue = Utils::randomDouble(0.1, 50.0);

    // Apply ±noiseFactor percent noise
    double noise = baseValue * noiseFactor * Utils::randomDouble(-1.0, 1.0);
    lastReading = baseValue + noise;

    if (lastReading <= 0.0)
        status = SensorStatus::ERROR;
    else
        status = SensorStatus::OK;

    // Occasional random fault
    if (Utils::chance(0.005)) {
        setFaulty(true);
    }

    return lastReading;
}

void LidarSensor::calibrate() {
    // Reset noise factor to nominal and clear faults
    noiseFactor = 0.1;
    status = SensorStatus::OK;
    setFaulty(false);
}
