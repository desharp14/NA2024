#include "interpolation.h"
#include <vector>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <utility>

#ifndef M_PI
#define M_PI 3.14159265358979323846  // Define Pi if not defined
#endif

// NewtonInterpolation Implementation

// Constructor: Initializes NewtonInterpolation with x and y values, and computes divided differences
NewtonInterpolation::NewtonInterpolation(const std::vector<double>& x_values, const std::vector<double>& y_values)
    : x_values_(x_values), y_values_(y_values), divided_diffs_(y_values) {
    computeDividedDifferences();
}

// Computes divided differences needed for the Newton interpolation polynomial
void NewtonInterpolation::computeDividedDifferences() {
    size_t n = x_values_.size();
    for (size_t j = 1; j < n; ++j) {
        for (size_t i = n - 1; i >= j; --i) {
            divided_diffs_[i] = (divided_diffs_[i] - divided_diffs_[i - 1]) / (x_values_[i] - x_values_[i - j]);
        }
    }
}

// Interpolates the value at x based on Newton's polynomial
double NewtonInterpolation::interpolate(double x) const {
    double result = divided_diffs_.back();
    for (int i = divided_diffs_.size() - 2; i >= 0; --i) {
        result = result * (x - x_values_[i]) + divided_diffs_[i];
    }
    return result;
}

// HermiteInterpolation Implementation

// Constructor: Initializes HermiteInterpolation with x values, function values, and derivatives
HermiteInterpolation::HermiteInterpolation(const std::vector<double>& x_values, const std::vector<double>& y_values, const std::vector<double>& y_prime_values)
    : x(x_values), y(y_values), y_derivatives(y_prime_values) {
    computeCoefficients();
}

// Computes coefficients for Hermite interpolation
void HermiteInterpolation::computeCoefficients() {
    int n = x.size();
    coefficients.resize(2 * n);
    std::vector<double> z(2 * n);  // Holds duplicated x values for Hermite calculation
    std::vector<double> Q(2 * n * 2 * n, 0.0);  // Divided differences table

    // Initialize z and Q with function values and derivatives
    for (int i = 0; i < n; ++i) {
        z[2 * i] = x[i];
        z[2 * i + 1] = x[i];
        Q[2 * i * 2 * n + 0] = y[i];
        Q[(2 * i + 1) * 2 * n + 0] = y[i];
        Q[(2 * i + 1) * 2 * n + 1] = y_derivatives[i];

        if (i != 0) {
            Q[2 * i * 2 * n + 1] = (Q[2 * i * 2 * n + 0] - Q[(2 * i - 1) * 2 * n + 0]) / (z[2 * i] - z[2 * i - 1]);
        }
    }

    // Fill in the rest of the divided difference table
    for (int j = 2; j < 2 * n; ++j) {
        for (int i = j; i < 2 * n; ++i) {
            Q[i * 2 * n + j] = (Q[i * 2 * n + j - 1] - Q[(i - 1) * 2 * n + j - 1]) / (z[i] - z[i - j]);
        }
    }

    // Store coefficients from the main diagonal of Q
    for (int i = 0; i < 2 * n; ++i) {
        coefficients[i] = Q[i * 2 * n + i];
    }
}

// Evaluates the Hermite polynomial at a given point t
double HermiteInterpolation::evaluate(double t) {
    int n = x.size();
    double result = coefficients[0];
    double product = 1.0;

    // Create the z array with duplicated x values
    std::vector<double> z(2 * n);
    for (int i = 0; i < n; ++i) {
        z[2 * i] = x[i];
        z[2 * i + 1] = x[i];
    }

    // Evaluate the polynomial using Horner's method
    for (int i = 1; i < 2 * n; ++i) {
        product *= (t - z[i - 1]);
        result += coefficients[i] * product;
    }

    return result;
}

// Computes the derivative of the Hermite polynomial at a given point t
double HermiteInterpolation::derivative(double t) {
    int n = x.size();
    double result = 0.0;

    std::vector<double> z(2 * n);  // Duplicated x values
    for (int i = 0; i < n; ++i) {
        z[2 * i] = x[i];
        z[2 * i + 1] = x[i];
    }

    // Sum terms for the derivative calculation
    for (int i = 1; i < 2 * n; ++i) {
        double term = coefficients[i];
        double derivative_product = 0.0;

        // Sum products for each term in the polynomial
        for (int j = 0; j < i; ++j) {
            double partial_product = 1.0;
            for (int k = 0; k < i; ++k) {
                if (k == j) {
                    partial_product *= 1;
                } else {
                    partial_product *= (t - z[k]);
                }
            }
            derivative_product += partial_product;
        }
        result += term * derivative_product;
    }

    return result;
}

// BezierCurve Implementation

// Default constructor
BezierCurve::BezierCurve() {}

// Heart shape function used to generate points for Bézier curve approximation
std::pair<double, double> BezierCurve::heartFunction(double t) {
    double x = 2.0 * std::sin(t);
    double y = std::sqrt(std::fabs(x)) - 1.5 * std::cos(t); 
    return {x, y};
}

// Generates a Bézier curve approximation of a heart shape with m segments
std::vector<std::pair<double, double>> BezierCurve::generateHeartBezier(int m) {
    std::vector<std::pair<double, double>> points;
    double step = 2 * M_PI / m;

    // Generate points along the heart shape using the step size
    for (int i = 0; i <= m; ++i) {
        double t = i * step;
        points.push_back(heartFunction(t));
    }

    // Compute Bézier curves based on generated points
    return computeBezierCurve(points, m);
}

// Computes the Bézier curve for given control points and number of segments
std::vector<std::pair<double, double>> BezierCurve::computeBezierCurve(
    const std::vector<std::pair<double, double>>& points, int m) {
    std::vector<std::pair<double, double>> bezierPoints;
    
    // For each segment, create a cubic Bézier curve using control points
    for (int i = 0; i < m; ++i) {
        auto p0 = points[i];
        auto p1 = points[i + 1];
        
        // Calculate intermediate control points for smooth transitions
        std::pair<double, double> q0 = p0;
        std::pair<double, double> q1 = {p0.first + (p1.first - p0.first) / 3.0, p0.second + (p1.second - p0.second) / 3.0};
        std::pair<double, double> q2 = {p1.first - (p1.first - p0.first) / 3.0, p1.second - (p1.second - p0.second) / 3.0};
        std::pair<double, double> q3 = p1;
        
        // Append calculated points to the Bézier curve points
        bezierPoints.push_back(q0);
        bezierPoints.push_back(q1);
        bezierPoints.push_back(q2);
        bezierPoints.push_back(q3);
    }

    return bezierPoints;
}
