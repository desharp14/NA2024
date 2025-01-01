#ifndef BSPLINE_H
#define BSPLINE_H

#include <vector>
#include <stdexcept>
#include <cmath>

class BSpline {
public:
    BSpline(int degree, const std::vector<double>& knots, const std::vector<double>& controlPoints);

    double interpolate(double x) const;

private:
    int degree_; // 样条阶数
    std::vector<double> knots_; // 节点向量
    std::vector<double> controlPoints_; // 控制点

    double basisFunction(int i, int k, double t) const; // 基函数计算
};

#endif // BSPLINE_H