#include "../../include/SplineUtils/b_form.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <iomanip>

// 构造函数：初始化样本点、阶数和节点向量
BForm::BForm(const std::vector<double>& x, const std::vector<double>& y, int degree, const std::vector<double>& knots)
    : x_(x), y_(y), degree_(degree), knots_(knots), n_(x.size()) {
    if (knots.size() != n_ + degree + 1) {
        throw std::invalid_argument("Knots size must be equal to number of points plus degree plus one.");
    }
    if (x.size() != y.size()) {
        throw std::invalid_argument("Input x and y must have the same size.");
    }
    computeBSpline(); // 初始化时计算样条系数
}

// 验证输入数据是否有效
void BForm::validateInput() const {
    if (x_.size() != y_.size()) {
        throw std::invalid_argument("X and Y must have the same size.");
    }
    if (knots_.size() != x_.size() + degree_ + 1) {
        throw std::invalid_argument("Knots vector size is invalid.");
    }
}

// 计算 B-样条系数
void BForm::computeBSpline() {
    size_t m = knots_.size() - 1; // 节点向量大小
    coefficients_.resize(n_);

    // 初始化系数矩阵
    std::vector<double> a(n_ - 1, 0.0), b(n_, 0.0), c(n_ - 1, 0.0), d(n_, 0.0);

    // 填充系数矩阵，三对角方程
    for (size_t i = 1; i < n_ - 1; ++i) {
        a[i - 1] = (knots_[i + degree_] - knots_[i]) / (knots_[i + degree_] - knots_[i - 1]);
        c[i - 1] = 1.0 - a[i - 1];
        b[i] = 2.0;
        d[i] = 6.0 * ((y_[i + 1] - y_[i]) / (x_[i + 1] - x_[i]) - (y_[i] - y_[i - 1]) / (x_[i] - x_[i - 1]));
    }

    // 边界条件
    b[0] = 1.0;
    b[n_ - 1] = 1.0;
    d[0] = 0.0;
    d[n_ - 1] = 0.0;

    // 求解三对角矩阵
    std::vector<double> solution = solveTridiagonal(a, b, c, d);
    coefficients_ = {solution}; // 保存结果
}

// 导出数据到指定文件
void BForm::exportData(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    outFile << std::fixed << std::setprecision(6);
    for (double t = knots_[degree_]; t <= knots_[knots_.size() - degree_ - 1]; t += 0.01) {
        outFile << t << " " << evaluate(t) << "\n";
    }
    outFile.close();
}

// 评估 B-样条值
double BForm::evaluate(double t) const {
    double result = 0.0;
    for (size_t i = 0; i < coefficients_.size(); ++i) {
        result += coefficients_[i][0] * basisFunction(i, degree_, t);
    }
    return result;
}

// 递归计算 B-样条基函数
double BForm::basisFunction(int i, int k, double t) const {
    if (k == 0) {
        return (knots_[i] <= t && t < knots_[i + 1]) ? 1.0 : 0.0;
    } else {
        double coef1 = (t - knots_[i]) / (knots_[i + k] - knots_[i]);
        double coef2 = (knots_[i + k + 1] - t) / (knots_[i + k + 1] - knots_[i + 1]);

        return coef1 * basisFunction(i, k - 1, t) + coef2 * basisFunction(i + 1, k - 1, t);
    }
}

// 求解三对角线性方程组
std::vector<double> BForm::solveTridiagonal(const std::vector<double>& a, 
                                            const std::vector<double>& b, 
                                            const std::vector<double>& c, 
                                            const std::vector<double>& d) const {
    size_t n = b.size();
    std::vector<double> x(n, 0.0), cp(n, 0.0), dp(n, 0.0);

    cp[0] = c[0] / b[0];
    dp[0] = d[0] / b[0];

    for (size_t i = 1; i < n; ++i) {
        double denom = b[i] - a[i - 1] * cp[i - 1];
        cp[i] = c[i] / denom;
        dp[i] = (d[i] - a[i - 1] * dp[i - 1]) / denom;
    }

    x[n - 1] = dp[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        x[i] = dp[i] - cp[i] * x[i + 1];
    }

    return x;
}

// 获取 B-样条的阶数
int BForm::getDegree() const {
    return degree_;
}

// 获取节点向量
const std::vector<double>& BForm::getKnots() const {
    return knots_;
}

// 获取样本点 x 和 y
const std::vector<double>& BForm::getX() const {
    return x_;
}

const std::vector<double>& BForm::getY() const {
    return y_;
}

// 获取样条系数
const std::vector<std::vector<double>>& BForm::getCoefficients() const {
    return coefficients_;
}