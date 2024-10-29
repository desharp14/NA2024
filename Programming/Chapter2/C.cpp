#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "interpolation.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Define the Runge function f(x) = 1 / (1 + 25 * x^2)
double f(double x) {
    return 1.0 / (1.0 + 25.0 * x * x);
}

// Generate Chebyshev nodes within the range [-1, 1]
std::vector<double> chebyshev_points(int n) {
    std::vector<double> points(n);
    for (int i = 0; i < n; ++i) {
        points[i] = cos(M_PI * (2 * i + 1) / (2.0 * n));
    }
    return points;
}

// Perform Chebyshev interpolation and save results
void runInterpolation(int n, const std::string& filename) {
    // Generate Chebyshev nodes and corresponding function values
    std::vector<double> x_values = chebyshev_points(n);
    std::vector<double> y_values(n);
    for (int i = 0; i < n; ++i) {
        y_values[i] = f(x_values[i]);
    }

    // Create interpolation object with Chebyshev nodes
    NewtonInterpolation interpolator(x_values, y_values);

    // Open file to save interpolated results
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    // Evaluate interpolated polynomial over the range [-1, 1] and write to file
    for (double x = -1.0; x <= 1.0; x += 0.05) {
        outfile << x << " " << interpolator.interpolate(x) << std::endl;
    }
    outfile.close();
}

int main() {
    // Run interpolation for specified n values and save results
    runInterpolation(5, "C_data_n5.txt");
    runInterpolation(10, "C_data_n10.txt");
    runInterpolation(15, "C_data_n15.txt");
    runInterpolation(20, "C_data_n20.txt");
    return 0;
}
