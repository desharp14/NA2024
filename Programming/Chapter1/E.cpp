#include <iostream>
#include <cmath>
#include "EquationSolver.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Constants for the problem
const double L = 10.0;       // Length of the trough (in feet)
const double r = 1.0;        // Radius of the semi-circular cross-section (in feet)
const double V_target = 12.4; // Target volume of water (in cubic feet)

// Function for volume equation
class VolumeFunction : public Function {
public:
    double operator()(double h) const override {
        // Volume equation based on the given formula
        return L * (0.5 * M_PI * r * r - r * r * asin(h / r) - h * sqrt(r * r - h * h)) - V_target;
    }

    // Derivative of the volume function (for Newton's method)
    double derivative(double h) const override {
        return L * (-r * r / sqrt(r * r - h * h) - sqrt(r * r - h * h));
    }
};

int main() {
    VolumeFunction volumeFunc;

    // Bisection method: h must be between 0 and 1 (since h < r = 1)
    BisectionMethod bisection(volumeFunc);
    double h_bisection = bisection.solve(0.0, 1.0, 100);  // 100 iterations max
    std::cout << "Bisection method result: h = " << h_bisection << " ft" << std::endl;

    // Newton's method: initial guess at h = 0.5
    NewtonMethod newton(volumeFunc);
    double h_newton = newton.solve(0.5, 0.0, 100);  // 100 iterations max
    std::cout << "Newton's method result: h = " << h_newton << " ft" << std::endl;

    // Secant method: initial guesses at h = 0.1 and h = 0.9
    SecantMethod secant(volumeFunc);
    double h_secant = secant.solve(0.1, 0.9, 100);  // 100 iterations max
    std::cout << "Secant method result: h = " << h_secant << " ft" << std::endl;

    return 0;
}
