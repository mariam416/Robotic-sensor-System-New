#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <random>
#include <ctime>

namespace Utils {
    int generateID();
    double randomDouble(double min, double max);
    bool chance(double probability); // e.g. 0.1 = 10% chance
    std::string currentDateTime();
}

#endif
