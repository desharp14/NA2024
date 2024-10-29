#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <vector>
#include <stdexcept>
#include <utility>

// NewtonInterpolation class for interpolating using Newton's divided differences
class NewtonInterpolation {
public:
    // Constructor: Initializes the interpolation points
    NewtonInterpolation(const std::vector<double>& x_values, const std::vector<double>& y_values);
    
    // Computes divided differences required for Newton's interpolation
    void computeDividedDifferences();
    
    // Interpolates a given x value based on the computed polynomial
    double interpolate(double x) const;

private:
    std::vector<double> x_values_;       // Interpolation x-coordinates
    std::vector<double> y_values_;       // Interpolation y-coordinates
    std::vector<double> divided_diffs_;  // Divided differences for interpolation
};

// HermiteInterpolation class for Hermite interpolation, including function and derivative values
class HermiteInterpolation {
public:
    std::vector<double> x;                 // Interpolation points
    std::vector<double> y;                 // Function values at interpolation points
    std::vector<double> y_derivatives;     // Derivative values at interpolation points 
    std::vector<double> coefficients;      // Computed coefficients for Hermite interpolation

    // Constructor: Initializes Hermite interpolation with x values, y values, and y' (derivative) values
    HermiteInterpolation(const std::vector<double>& x_values, const std::vector<double>& y_values, const std::vector<double>& y_prime_values);
    
    // Evaluates the Hermite polynomial at a given point t
    double evaluate(double t);  
    
    // Evaluates the derivative of the Hermite polynomial at a given point t
    double derivative(double t);
    
    // Computes coefficients for the Hermite polynomial
    void computeCoefficients();
};

// BezierCurve class to generate and compute cubic Bézier curves, used here for heart shape approximation
class BezierCurve {
public:
    // Default constructor
    BezierCurve(); 
    
    // Generates Bézier curve points to approximate a heart shape, parameterized by m
    std::vector<std::pair<double, double>> generateHeartBezier(int m); 

private:
    // Defines the heart shape function parameterized by t
    std::pair<double, double> heartFunction(double t);
    
    // Computes the Bézier curve using a set of control points and a specified number of subdivisions m
    std::vector<std::pair<double, double>> computeBezierCurve(
        const std::vector<std::pair<double, double>>& points, int m);
};

#endif // INTERPOLATION_H
