#ifndef EQUATION_SOLVER_H
#define EQUATION_SOLVER_H

#include "Function.h"
#include <iostream>
#include <cmath>

// Base class for solvers
class EquationSolver {
protected:
    const Function& func;

public:
    EquationSolver(const Function& f) : func(f) {}
    virtual double solve(double initialGuess1, double initialGuess2, int maxIterations) = 0;
    virtual ~EquationSolver() = default;
};

// Bisection Method Solver
class BisectionMethod : public EquationSolver {
public:
    BisectionMethod(const Function& f) : EquationSolver(f) {}

    double solve(double a, double b, int maxIterations) override {
        if (func(a) * func(b) >= 0) {
            std::cerr << "Bisection method fails. f(a) and f(b) must have opposite signs." << std::endl;
            return NAN;
        }

        double c;
        for (int i = 0; i < maxIterations; ++i) {
            c = (a + b) / 2;
            if (std::fabs(func(c)) < 1e-6 || (b - a) / 2 < 1e-6) {
                return c;
            }
            if (func(c) * func(a) < 0) {
                b = c;
            }
            else {
                a = c;
            }
        }
        return c;
    }
};

// Newton's Method Solver
class NewtonMethod : public EquationSolver {
public:
    NewtonMethod(const Function& f) : EquationSolver(f) {}

    double solve(double x0, double, int maxIterations) override {
        double x = x0;
        for (int i = 0; i < maxIterations; ++i) {
            double fx = func(x);
            double fPrimeX = func.derivative(x);
            if (std::fabs(fx) < 1e-6 || std::fabs(fPrimeX) < 1e-6) {
                return x;
            }
            x = x - fx / fPrimeX;
        }
        return x;
    }
};

// Secant Method Solver
class SecantMethod : public EquationSolver {
public:
    SecantMethod(const Function& f) : EquationSolver(f) {}

    double solve(double x0, double x1, int maxIterations) override {
        double x2;
        for (int i = 0; i < maxIterations; ++i) {
            double fx0 = func(x0);
            double fx1 = func(x1);
            if (std::fabs(fx1 - fx0) < 1e-6) {
                return x1;
            }
            x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);
            if (std::fabs(func(x2)) < 1e-6) {
                return x2;
            }
            x0 = x1;
            x1 = x2;
        }
        return x2;
    }
};

#endif // EQUATION_SOLVER_H
