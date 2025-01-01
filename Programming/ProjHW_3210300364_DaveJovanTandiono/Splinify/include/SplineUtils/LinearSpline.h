// LinearSpline.h
#ifndef LINEARSPLINE_H
#define LINEARSPLINE_H

#include <vector>
#include <utility> // For std::pair

class LinearSpline {
public:
    LinearSpline() = default;
    ~LinearSpline() = default;

    void addPoint(double x, double y);
    double interpolate(double x) const;
    void clear();
    const std::vector<std::pair<double, double>>& getPoints() const;

private:
    std::vector<std::pair<double, double>> points;
};

#endif // LINEARSPLINE_H