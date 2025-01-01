#include "../../include/SplineUtils/PiecewisePolynomialSpline.h"
#include <stdexcept>
#include <cmath>

PiecewisePolynomialSpline::PiecewisePolynomialSpline(const std::vector<double>& x, const std::vector<double>& y)
    : m_x(x), m_y(y) {
    if (x.size() < 2 || y.size() < 2 || x.size() != y.size()) {
        throw std::invalid_argument("输入数据点数量不足或 x 和 y 大小不匹配！");
    }
    computeCoefficients();
}

void PiecewisePolynomialSpline::computeCoefficients() {
    size_t n = m_x.size() - 1;
    m_coefficients.resize(n);
    for (size_t i = 0; i < n; ++i) {
        double dx = m_x[i + 1] - m_x[i];
        double dy = m_y[i + 1] - m_y[i];
        m_coefficients[i] = dy / dx; // 简单线性插值
    }
}

double PiecewisePolynomialSpline::evaluate(double x) const {
    if (x < m_x.front() || x > m_x.back()) {
        throw std::out_of_range("输入值超出插值范围！");
    }

    for (size_t i = 0; i < m_x.size() - 1; ++i) {
        if (x >= m_x[i] && x <= m_x[i + 1]) {
            double dx = x - m_x[i];
            return m_y[i] + m_coefficients[i] * dx;
        }
    }
    return m_y.back(); // 默认返回最后一个点的 y 值
}