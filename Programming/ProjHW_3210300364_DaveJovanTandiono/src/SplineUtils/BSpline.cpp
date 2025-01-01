#include "../../include/SplineUtils/BSpline.h"

// 构造函数
BSpline::BSpline(int degree, const std::vector<double>& knots, const std::vector<double>& controlPoints)
    : degree_(degree), knots_(knots), controlPoints_(controlPoints) {
    int requiredKnotCount = controlPoints_.size() + degree_ + 1;
    if (knots_.size() != requiredKnotCount) {
        throw std::invalid_argument("节点数量与控制点数量不匹配！"
                                    "节点数量需要为控制点数量 + 阶数 + 1。"
                                    "当前节点数量: " + std::to_string(knots_.size()) +
                                    ", 需要的节点数量: " + std::to_string(requiredKnotCount));
    }
}

// 插值计算
double BSpline::interpolate(double x) const {
    if (x < knots_[degree_] || x > knots_[knots_.size() - degree_ - 1]) {
        throw std::out_of_range("插值点超出有效范围！");
    }

    double result = 0.0;
    for (size_t i = 0; i < controlPoints_.size(); ++i) {
        result += controlPoints_[i] * basisFunction(i, degree_, x);
    }
    return result;
}

// 基函数计算
double BSpline::basisFunction(int i, int k, double t) const {
    if (k == 0) {
        return (t >= knots_[i] && t < knots_[i + 1]) ? 1.0 : 0.0;
    }

    double coeff1 = (t - knots_[i]) / (knots_[i + k] - knots_[i]);
    double coeff2 = (knots_[i + k + 1] - t) / (knots_[i + k + 1] - knots_[i + 1]);

    double term1 = (knots_[i + k] > knots_[i]) ? coeff1 * basisFunction(i, k - 1, t) : 0.0;
    double term2 = (knots_[i + k + 1] > knots_[i + 1]) ? coeff2 * basisFunction(i + 1, k - 1, t) : 0.0;

    return term1 + term2;
}