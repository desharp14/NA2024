#include "EquationSolver.h"
#include "Function.h"
#include <iostream>
#include <cmath>

// Define the function for Newton's method: f(x) = x - tan(x)
class NewtonF : public Function {
public:
    double operator()(double x) const override {
        return x - std::tan(x);  // f(x) = x - tan(x)
    }

    double derivative(double x) const override {
        return 1 - (1 / std::pow(std::cos(x), 2));  // Derivative of f(x) = x - tan(x)
    }
};

int main() {
    const int maxIterations = 1000;

    // Create Newton Method Solver instance for f(x) = x - tan(x)
    NewtonF newtonF;
    NewtonMethod newtonSolver(newtonF);  // NewtonMethod defined in EquationSolver.h

    // Find the root near 4.5
    double root1 = newtonSolver.solve(4.5, 0, maxIterations);
    std::cout << "Root near 4.5: " << root1 << std::endl;

    // Find the root near 7.7
    double root2 = newtonSolver.solve(7.7, 0, maxIterations);
    std::cout << "Root near 7.7: " << root2 << std::endl;

    return 0;
}
