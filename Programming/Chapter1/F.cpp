#include <iostream>
#include <cmath>
#include "EquationSolver.h"  // Include the EquationSolver header

const double pi = 3.14159265358979323846;
const double l = 89, h = 49, beta1 = 11.5 / 180 * pi;
double A, B, C, D = 55, E;

// Function to update the values of A, B, C, and E based on the current D
void updateValues() {
    A = l * sin(beta1);
    B = l * cos(beta1);
    C = (h + 0.5 * D) * sin(beta1) - 0.5 * D * tan(beta1);
    E = (h + 0.5 * D) * cos(beta1) - 0.5 * D;
}

// Define the function and its derivative
// Let x = sin(alpha), so the equation is written in terms of x
class MyFunction : public Function {
public:
    double operator()(double x) const override {
        return A * x * sqrt(1 - x * x) + B * x * x - C * sqrt(1 - x * x) - E * x;
    }

    double derivative(double x) const override {
        return A * (1 - 2 * x * x) / sqrt(1 - x * x) + 2 * B * x + C * x / sqrt(1 - x * x) - E;
    }
};

int main() {
    updateValues();

    // Instantiate MyFunction
    MyFunction func;

    // Instantiate the solvers using EquationSolver.h
    NewtonMethod newtonSolver(func);
    SecantMethod secantSolver(func);

    // Part (a): Newton's method for D = 55
    std::cout << "Question (a):" << std::endl;
    double alpha_a = newtonSolver.solve(0.5, 0, 100); // Initial guess for sin(alpha) is 0.5
    std::cout << "The solution of alpha is: " << asin(alpha_a) * 180 / pi << " (degree)." << std::endl << std::endl;

    // Part (b): Newton's method for D = 30
    D = 30;
    updateValues();
    double alpha_b = newtonSolver.solve(0.5, 0, 100); // Initial guess for sin(alpha) is 0.5
    std::cout << "Question (b):" << std::endl;
    std::cout << "The solution of alpha is: " << asin(alpha_b) * 180 / pi << " (degree)." << std::endl << std::endl;

    // Part (c): Secant method with far away guess
    std::cout << "Question (c):" << std::endl;
    double alpha_c = secantSolver.solve(0.0, 0.1, 100); // Initial guesses far from 0.5
    std::cout << "The solution of alpha is: " << asin(alpha_c) * 180 / pi << " (degree)." << std::endl << std::endl;

    return 0;
}
