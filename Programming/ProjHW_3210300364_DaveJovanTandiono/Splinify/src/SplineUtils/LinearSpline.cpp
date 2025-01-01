// LinearSpline.cpp
#include "../../include/SplineUtils/LinearSpline.h"
#include <algorithm> // For std::lower_bound
#include <stdexcept> // For std::domain_error

void LinearSpline::addPoint(double x, double y) {
    // Ensure that points are added in a sorted manner
    auto it = std::lower_bound(points.begin(), points.end(), std::make_pair(x, y),
                               [](const std::pair<double, double>& a, const std::pair<double, double>& b) {
                                   return a.first < b.first;
                               });
    points.insert(it, std::make_pair(x, y));
}

double LinearSpline::interpolate(double x) const {
    if (points.size() < 2) {
        throw std::domain_error("Not enough points to interpolate");
    }

    // Find the segment containing 'x'
    auto it = std::lower_bound(points.begin(), points.end(), std::make_pair(x, 0.0),
                               [](const std::pair<double, double>& a, const std::pair<double, double>& b) {
                                   return a.first < b.first;
                               });

    if (it == points.begin() || it == points.end()) {
        throw std::domain_error("Interpolation point out of bounds");
    }

    auto [x1, y1] = *(it - 1);
    auto [x2, y2] = *it;

    // Linear interpolation formula
    double t = (x - x1) / (x2 - x1);
    return y1 + t * (y2 - y1);
}

void LinearSpline::clear() {
    points.clear();
}

const std::vector<std::pair<double, double>>& LinearSpline::getPoints() const {
    return points;
}