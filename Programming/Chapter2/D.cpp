#include <iostream>
#include <vector>
#include "interpolation.h"

int main() {
    // Given data points
    std::vector<double> time = {0, 3, 5, 8, 13};
    std::vector<double> displacement = {0, 225, 383, 623, 993};
    std::vector<double> velocity = {75, 77, 80, 74, 72};

    // Create Hermite interpolation object
    HermiteInterpolation hermite(time, displacement, velocity);

    // Predict position and speed at t = 10 seconds
    double t = 10.0;
    double position = hermite.evaluate(t);  // Corrected from interpolate to evaluate
    double speed = hermite.derivative(t);

    // Output results
    std::cout << "Position at t = " << t << " seconds: " << position << " feet" << std::endl;
    std::cout << "Speed at t = " << t << " seconds: " << speed << " feet/second" << std::endl;

    // Check speed limit
    if (speed > 81.0) {
        std::cout << "The car exceeds the speed limit of 81 feet/second." << std::endl;
    } else {
        std::cout << "The car does not exceed the speed limit of 81 feet/second." << std::endl;
    }

    return 0;
}
