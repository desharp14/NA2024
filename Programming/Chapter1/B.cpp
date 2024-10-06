#include "EquationSolver.h"
#include "Function.h"
#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Define functions specific to Bisection method test cases
class F1 : public Function {
public:
    double operator()(double x) const override {
        return 1.0 / x - std::tan(x);
    }
};

class F2 : public Function {
public:
    double operator()(double x) const override {
        return 1.0 / x - std::pow(2, x);
    }
};

class F3 : public Function {
public:
    double operator()(double x) const override {
        return std::pow(2, -x) + std::exp(x) + 2 * std::cos(x) - 6;
    }
};

class F4 : public Function {
public:
    double operator()(double x) const override {
        return (std::pow(x, 3) + 4 * std::pow(x, 2) + 3 * x + 5) /
            (2 * std::pow(x, 3) - 9 * std::pow(x, 2) + 18 * x - 2);
    }
};

int main() {
    const int maxIterations = 1000;

    // Create Bisection Method Solver instances
    F1 f1;
    F2 f2;
    F3 f3;
    F4 f4;
    BisectionMethod bisectionSolver1(f1);
    BisectionMethod bisectionSolver2(f2);
    BisectionMethod bisectionSolver3(f3);
    BisectionMethod bisectionSolver4(f4);

    // Solve using Bisection Method
    double root1 = bisectionSolver1.solve(0, M_PI / 2, maxIterations);
    double root2 = bisectionSolver2.solve(0, 1, maxIterations);
    double root3 = bisectionSolver3.solve(1, 3, maxIterations);
    double root4 = bisectionSolver4.solve(0, 4, maxIterations);

    // Output results
    std::cout << "Root of f1 (1/x - tan(x)) on [0, pi/2]: " << root1 << std::endl;
    std::cout << "Root of f2 (1/x - 2^x) on [0, 1]: " << root2 << std::endl;
    std::cout << "Root of f3 (2^(-x) + e^x + 2cos(x) - 6) on [1, 3]: " << root3 << std::endl;
    std::cout << "Root of f4 on [0, 4]: " << root4 << std::endl;

    return 0;
}
