#include "temperature_sensor.h"
#include "utils.h"
#include <iostream>
TemperatureSensor::TemperatureSensor(int id, const std::string& name)
    : Sensor(id, name, "Temperature", "°C") {}

double TemperatureSensor::readData() {
    // Generate random temperature between -20 and 100
    lastReading = Utils::randomDouble(-20.0, 100.0);

    if (lastReading > 90.0)
        status = SensorStatus::ERROR;
    else if (lastReading > 70.0)
        status = SensorStatus::WARNING;
    else
        status = SensorStatus::OK;

    // Simulate occasional fault based on chance (small)
    if (Utils::chance(0.01)) {
        setFaulty(true);
    }

    return lastReading;
}

void TemperatureSensor::calibrate() {
    // Simple calibration: reset to nominal reading and clear faults
    lastReading = 25.0;
    status = SensorStatus::OK;
    setFaulty(false);
}
