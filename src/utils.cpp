#include "utils.h"
#include <sstream>
#include <iomanip>
#include <chrono>

namespace Utils {

int generateID() {
    static int idCounter = 1000;
    return idCounter++;
}

double randomDouble(double min, double max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(min, max);
    return dist(gen);
}

bool chance(double probability) {
    return randomDouble(0.0, 1.0) < probability;
}

std::string currentDateTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_t = std::chrono::system_clock::to_time_t(now);
    std::tm* timeinfo = std::localtime(&now_t);

    std::ostringstream oss;
    oss << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

} 
