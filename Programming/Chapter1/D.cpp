#include "EquationSolver.h"
#include "Function.h"
#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Define the first function for the secant method: f(x) = sin(x / 2) - 1
class SecantF1 : public Function {
public:
    double operator()(double x) const override {
        return std::sin(x / 2) - 1;
    }
};

// Define the second function: f(x) = e^x - tan(x)
class SecantF2 : public Function {
public:
    double operator()(double x) const override {
        return std::exp(x) - std::tan(x);
    }
};

// Define the third function: f(x) = x^3 - 12x^2 + 3x + 1
class SecantF3 : public Function {
public:
    double operator()(double x) const override {
        return std::pow(x, 3) - 12 * std::pow(x, 2) + 3 * x + 1;
    }
};

int main() {
    const int maxIterations = 1000;

    // Create Secant Method Solver instances for each function
    SecantF1 secantF1;
    SecantF2 secantF2;
    SecantF3 secantF3;

    SecantMethod secantSolver1(secantF1);
    SecantMethod secantSolver2(secantF2);
    SecantMethod secantSolver3(secantF3);

    // Solve for f(x) = sin(x / 2) - 1 with initial guesses 0 and pi/2
    double root1 = secantSolver1.solve(0, M_PI / 2, maxIterations);
    std::cout << "Root of f1 (sin(x / 2) - 1) near 0 and pi/2: " << root1 << std::endl;

    // Solve for f(x) = e^x - tan(x) with initial guesses 1 and 1.4
    double root2 = secantSolver2.solve(1, 1.4, maxIterations);
    std::cout << "Root of f2 (e^x - tan(x)) near 1 and 1.4: " << root2 << std::endl;

    // Solve for f(x) = x^3 - 12x^2 + 3x + 1 with initial guesses 0 and -0.5
    double root3 = secantSolver3.solve(0, -0.5, maxIterations);
    std::cout << "Root of f3 (x^3 - 12x^2 + 3x + 1) near 0 and -0.5: " << root3 << std::endl;

    return 0;
}
