#include "../../include/SplineUtils/CubicSpline.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <iostream>

CubicSpline::CubicSpline() {}

CubicSpline::~CubicSpline() {}

void CubicSpline::addPoint(double x, double y) {
    points.emplace_back(x, y);
    std::sort(points.begin(), points.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });
}

void CubicSpline::computeCoefficients() {
    const size_t n = points.size();
    if (n < 3) {
        throw std::runtime_error("进行三次样条插值需要至少三个点。");
    }

    std::vector<double> h(n - 1), a(n), b(n), c(n), d(n), alpha(n);

    for (size_t i = 0; i < n - 1; i++) {
        h[i] = points[i + 1].first - points[i].first;
    }

    alpha[0] = 3.0 * ((points[1].second - points[0].second) / h[0] - boundaryFirstDerivativeStart);
    alpha[n - 1] = 3.0 * (boundaryFirstDerivativeEnd - (points[n - 1].second - points[n - 2].second) / h[n - 2]);

    for (size_t i = 1; i < n - 1; i++) {
        alpha[i] = 3.0 * ((points[i + 1].second - points[i].second) / h[i] - (points[i].second - points[i - 1].second) / h[i - 1]);
    }

    b[0] = 2.0 * h[0];
    c[0] = h[0];
    d[0] = alpha[0];

    for (size_t i = 1; i < n - 1; i++) {
        a[i] = h[i - 1];
        b[i] = 2.0 * (h[i - 1] + h[i]);
        c[i] = h[i];
        d[i] = alpha[i];
    }

    a[n - 1] = h[n - 2];
    b[n - 1] = 2.0 * h[n - 2];
    d[n - 1] = alpha[n - 1];

    std::vector<double> c_prime(n, 0.0);
    std::vector<double> d_prime(n, 0.0);

    c_prime[0] = c[0] / b[0];
    d_prime[0] = d[0] / b[0];

    for (size_t i = 1; i < n; i++) {
        double m = 1.0 / (b[i] - a[i] * c_prime[i - 1]);
        c_prime[i] = c[i] * m;
        d_prime[i] = (d[i] - a[i] * d_prime[i - 1]) * m;
    }

    coefficients.resize(n);
    coefficients[n - 1] = d_prime[n - 1];

    for (int i = n - 2; i >= 0; i--) {
        coefficients[i] = d_prime[i] - c_prime[i] * coefficients[i + 1];
    }
}

double CubicSpline::interpolate(double x) const {
    if (points.empty()) {
        throw std::runtime_error("没有控制点，无法进行插值。");
    }

    auto it = std::lower_bound(points.begin(), points.end(), std::make_pair(x, 0.0), [](const std::pair<double, double>& a, const std::pair<double, double>& b) {
        return a.first < b.first;
    });

    if (it == points.end() || (it == points.begin() && x < points.front().first)) {
        throw std::out_of_range("插值点超出范围。");
    }

    if (it == points.end()) {
        return points.back().second;
    }

    size_t i = std::distance(points.begin(), it);
    double h = points[i].first - points[i - 1].first;
    double s = (x - points[i - 1].first) / h;
    double y = (1 - s) * points[i - 1].second + s * points[i].second + s * (1 - s) * (coefficients[i - 1] * (1 - s) + coefficients[i] * s) * h * h / 6;

    return y;
}

void CubicSpline::setBoundaryType(BoundaryType type) {
    boundaryType = type;
}

void CubicSpline::setBoundaryValues(double first_derivative_start, double first_derivative_end) {
    boundaryFirstDerivativeStart = first_derivative_start;
    boundaryFirstDerivativeEnd = first_derivative_end;
}

void CubicSpline::clear() {
    points.clear();
    coefficients.clear();
}

void CubicSpline::triggerComputation() {
    computeCoefficients();
}