#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "interpolation.h"

// Function representing the original Runge's function
double f(double x) {
    return 1.0 / (1.0 + x * x);
}

// Generate a linearly spaced vector from start to end with num_points elements
std::vector<double> linspace(double start, double end, int num_points) {
    std::vector<double> points(num_points);
    double step = (end - start) / (num_points - 1);
    for (int i = 0; i < num_points; ++i) {
        points[i] = start + i * step;
    }
    return points;
}

// Function to perform interpolation and save results to a file
void runInterpolation(int n, const std::string& filename) {
    // Generate x and y values for interpolation
    std::vector<double> x_values = linspace(-5, 5, n + 1);
    std::vector<double> y_values;
    for (double x : x_values) {
        y_values.push_back(f(x));
    }

    // Create an interpolation object using the generated x and y values
    NewtonInterpolation interpolator(x_values, y_values);

    // Open file to save interpolated results
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Failed to open file " << filename << std::endl;
        return;
    }

    // Generate interpolated points and write to file
    std::vector<double> x_plot = linspace(-5, 5, 100);
    for (double x : x_plot) {
        outfile << x << " " << interpolator.interpolate(x) << std::endl;
    }
    outfile.close();
}

int main() {
    // Run interpolation for specified n values and save to respective files
    runInterpolation(2, "interpolation_n2.txt");
    runInterpolation(4, "interpolation_n4.txt");
    runInterpolation(6, "interpolation_n6.txt");
    runInterpolation(8, "interpolation_n8.txt");
    return 0;
}
