#ifndef PIECEWISE_POLYNOMIAL_SPLINE_H
#define PIECEWISE_POLYNOMIAL_SPLINE_H

#include <vector>

class PiecewisePolynomialSpline {
public:
    PiecewisePolynomialSpline(const std::vector<double>& x, const std::vector<double>& y);
    double evaluate(double x) const;

private:
    std::vector<double> m_x;
    std::vector<double> m_y;
    std::vector<double> m_coefficients;

    void computeCoefficients();
};

#endif // PIECEWISE_POLYNOMIAL_SPLINE_H