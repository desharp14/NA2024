#include <iostream>
#include <fstream>
#include <sstream>
#include "interpolation.h"

// Function to save Bézier curve data to a file
void saveBezierData(const std::vector<std::pair<double, double>>& bezierPoints, int m) {
    // Construct the filename based on the current m value
    std::stringstream ss;
    ss << "bezier_data_m" << m << ".txt";
    std::ofstream outfile(ss.str());

    // Check if the file opened successfully
    if (outfile.is_open()) {
        // Write each point in the Bézier curve to the file
        for (const auto& point : bezierPoints) {
            outfile << point.first << " " << point.second << "\n";
        }
        outfile.close();
        std::cout << "Data saved to " << ss.str() << std::endl;
    } else {
        std::cerr << "Unable to open file for writing!" << std::endl;
    }
}

int main() {
    BezierCurve bezier;

    // Generate and save Bézier curve data for specified values of m
    for (int m : {10, 40, 160}) {
        std::vector<std::pair<double, double>> bezierPoints = bezier.generateHeartBezier(m);
        saveBezierData(bezierPoints, m);
    }

    return 0;
}
