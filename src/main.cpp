#include <iostream>
#include <memory>
#include <limits>
#include "sensor_manager.h"
#include "temperature_sensor.h"
#include "lidar_sensor.h"
#include "camera_sensor.h"
#include "diagnostics.h"
#include "utils.h"

void printMenu() {
    std::cout << "\n===== ROBOTIC SENSOR CONTROL SYSTEM =====\n"
              << "1. Add Sensor\n"
              << "2. Remove Sensor\n"
              << "3. List All Sensors\n"
              << "4. Read All Sensors\n"
              << "5. Run Diagnostics\n"
              << "6. Save Logs\n"
              << "7. Exit\n"
              << "Select option: ";
}

void addSensorCLI(SensorManager& manager) {
    std::cout << "Select Sensor Type (1-Temp, 2-Lidar, 3-Camera): ";
    int type; std::cin >> type;

    std::string name;
    std::cout << "Enter sensor name: ";
    std::cin >> name;

    int id = Utils::generateID();
    std::shared_ptr<Sensor> sensor;

    switch (type) {
        case 1: sensor = std::make_shared<TemperatureSensor>(id, name); break;
        case 2: sensor = std::make_shared<LidarSensor>(id, name); break;
        case 3: sensor = std::make_shared<CameraSensor>(id, name); break;
        default: std::cout << "Invalid type!\n"; return;
    }

    manager.addSensor(sensor);
    std::cout << "Sensor added with ID: " << id << "\n";
}

int main() {
    SensorManager manager;
    bool running = true;

    while (running) {
        printMenu();
        int choice;
        std::cin >> choice;

        try {
            switch (choice) {
                case 1: addSensorCLI(manager); break;
                case 2: {
                    int id;
                    std::cout << "Enter Sensor ID to remove: ";
                    std::cin >> id;
                    manager.removeSensor(id);
                    std::cout << "Sensor removed.\n";
                    break;
                }
                case 3:
                    manager.listAllSensors();
                    break;
                case 4:
                    manager.readAllSensors();
                    break;
                case 5: {
                    auto& diag = Diagnostics::getInstance();
                    std::string report = diag.generateReport(manager);
                    std::cout << "\n" << report;
                    diag.saveReport("data/diagnostic_report.txt", report);
                    break;
                }
                case 6:
                    manager.saveLogs("data/logs.txt");
                    std::cout << "Logs saved.\n";
                    break;
                case 7:
                    running = false;
                    std::cout << "Exiting...\n";
                    break;
                default:
                    std::cout << "Invalid option.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }

        // Clear input buffer
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}
