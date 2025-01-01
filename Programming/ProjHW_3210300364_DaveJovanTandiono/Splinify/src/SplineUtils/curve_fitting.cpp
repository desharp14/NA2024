#include "../../include/SplineUtils/curve_fitting.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <stdexcept>

void CurveFitting::linearFit(const std::vector<double>& x, const std::vector<double>& y, std::vector<double>& coefficients) {
    if (x.size() != y.size() || x.empty()) {
        throw std::invalid_argument("Invalid input data for linear fitting.");
    }

    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
    size_t n = x.size();

    for (size_t i = 0; i < n; ++i) {
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumX2 += x[i] * x[i];
    }

    double slope = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    double intercept = (sumY - slope * sumX) / n;

    coefficients = {intercept, slope};
}

void CurveFitting::quadraticFit(const std::vector<double>& x, const std::vector<double>& y, std::vector<double>& coefficients) {
    if (x.size() != y.size() || x.empty()) {
        throw std::invalid_argument("Invalid input data for quadratic fitting.");
    }

    double sumX = 0, sumX2 = 0, sumX3 = 0, sumX4 = 0;
    double sumY = 0, sumXY = 0, sumX2Y = 0;
    size_t n = x.size();

    for (size_t i = 0; i < n; ++i) {
        double xi = x[i];
        double yi = y[i];
        sumX += xi;
        sumX2 += xi * xi;
        sumX3 += xi * xi * xi;
        sumX4 += xi * xi * xi * xi;
        sumY += yi;
        sumXY += xi * yi;
        sumX2Y += xi * xi * yi;
    }

    // Solve the system of linear equations using Cramer's rule
    double det = n * (sumX2 * sumX4 - sumX3 * sumX3) - sumX * (sumX * sumX4 - sumX3 * sumX2) + sumX2 * (sumX * sumX3 - sumX2 * sumX2);
    if (std::abs(det) < 1e-10) {
        throw std::runtime_error("Singular matrix encountered during quadratic fitting.");
    }

    double a = (sumY * (sumX2 * sumX4 - sumX3 * sumX3) - sumX * (sumXY * sumX4 - sumX3 * sumX2Y) + sumX2 * (sumXY * sumX3 - sumX2 * sumX2Y)) / det;
    double b = (n * (sumXY * sumX4 - sumX3 * sumX2Y) - sumY * (sumX * sumX4 - sumX3 * sumX2) + sumX2 * (sumX * sumX2Y - sumY * sumX3)) / det;
    double c = (n * (sumX2 * sumX2Y - sumXY * sumX3) - sumX * (sumX * sumX2Y - sumY * sumX3) + sumY * (sumX * sumX2 - sumX2 * sumX)) / det;

    coefficients = {a, b, c};
}

void CurveFitting::cubicFit(const std::vector<double>& x, const std::vector<double>& y, std::vector<double>& coefficients) {
    // Placeholder: You can expand this function to include cubic polynomial fitting logic.
    throw std::runtime_error("Cubic fitting not implemented yet.");
}

double CurveFitting::predict(const std::vector<double>& coefficients, double x) {
    double result = 0;
    for (size_t i = 0; i < coefficients.size(); ++i) {
        result += coefficients[i] * std::pow(x, i);
    }
    return result;
}

void CurveFitting::saveFitResults(const std::string& filePath, const std::vector<double>& coefficients) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for saving fit results: " + filePath);
    }

    file << "Fitting coefficients:\n";
    for (size_t i = 0; i < coefficients.size(); ++i) {
        file << "Coefficient " << i << ": " << coefficients[i] << "\n";
    }

    file.close();
}

double CurveFitting::computeError(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& coefficients) {
    if (x.size() != y.size() || x.empty()) {
        throw std::invalid_argument("Invalid input data for error computation.");
    }

    double error = 0;
    for (size_t i = 0; i < x.size(); ++i) {
        double predictedY = predict(coefficients, x[i]);
        error += std::pow(predictedY - y[i], 2);
    }

    return error / x.size();
}