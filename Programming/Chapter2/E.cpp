#include <iostream>
#include <vector>
#include "interpolation.h"

int main() {
    // Days data and average weights for both samples
    std::vector<double> days = {0, 6, 10, 13, 17, 20, 28};
    std::vector<double> weights_sp1 = {6.67, 17.3, 42.7, 37.3, 30.1, 29.3, 28.7};
    std::vector<double> weights_sp2 = {6.67, 16.1, 18.9, 15.0, 10.6, 9.44, 8.89};

    // Interpolating for sample 1 (young leaves)
    NewtonInterpolation interpolator_sp1(days, weights_sp1);
    double prediction_sp1 = interpolator_sp1.interpolate(43);  // Predict weight at day 43

    // Interpolating for sample 2 (mature leaves)
    NewtonInterpolation interpolator_sp2(days, weights_sp2);
    double prediction_sp2 = interpolator_sp2.interpolate(43);  // Predict weight at day 43

    // Output the results
    std::cout << "Prediction for Sample 1 (Young Leaves) at Day 43: " << prediction_sp1 << " mg\n";
    std::cout << "Prediction for Sample 2 (Mature Leaves) at Day 43: " << prediction_sp2 << " mg\n";

    // Analysis based on predicted weights
    if (prediction_sp1 <= 0) {
        std::cout << "Sample 1 larvae may not survive after 43 days.\n";
    } else {
        std::cout << "Sample 1 larvae show signs of survival with a weight of " << prediction_sp1 << " mg.\n";
    }

    if (prediction_sp2 <= 0) {
        std::cout << "Sample 2 larvae may not survive after 43 days.\n";
    } else {
        std::cout << "Sample 2 larvae show signs of survival with a weight of " << prediction_sp2 << " mg.\n";
    }

    return 0;
}
