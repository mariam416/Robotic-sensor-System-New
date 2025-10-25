#include "diagnostics.h"

std::unique_ptr<Diagnostics> Diagnostics::instance = nullptr;

Diagnostics& Diagnostics::getInstance() {
    if (!instance)
        instance = std::unique_ptr<Diagnostics>(new Diagnostics());
    return *instance;
}

std::vector<std::shared_ptr<Sensor>> Diagnostics::detectFaultySensors(SensorManager& manager) {
    std::vector<std::shared_ptr<Sensor>> faulty;
    auto sensors = manager.getAllSensors();
    for (auto& [id, sensor] : sensors) {
        if (sensor->getStatus() == SensorStatus::FAULTY) {
            faulty.push_back(sensor);
        }
    }
    return faulty;
}

std::string Diagnostics::generateReport(SensorManager& manager) {
    std::ostringstream report;
    auto faulty = detectFaultySensors(manager);

    report << "===== SYSTEM DIAGNOSTICS REPORT =====\n";
    report << "Generated: " << Utils::currentDateTime() << "\n";
    report << "Total Sensors: " << manager.getAllSensors().size() << "\n";
    report << "Faulty Sensors: " << faulty.size() << "\n\n";

    if (faulty.empty()) {
        report << "All sensors operational.\n";
    } else {
        report << "Faulty Sensors List:\n";
        for (auto& s : faulty) {
            report << " - ID: " << s->getId()
                   << " | Name: " << s->getName()
                   << " | Type: " << s->getType()
                   << " | Last Reading: " << s->getLastReading()
                   << " | Status: FAULTY\n";
        }
    }

    report << "=====================================\n";
    return report.str();
}

void Diagnostics::saveReport(const std::string& path, const std::string& report) {
    std::ofstream out(path, std::ios::app);
    if (!out) throw std::runtime_error("Failed to open report file: " + path);
    out << report << "\n";
    out.close();
}
