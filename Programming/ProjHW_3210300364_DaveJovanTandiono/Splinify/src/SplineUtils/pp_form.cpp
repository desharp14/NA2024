#include "../../include/SplineUtils/pp_form.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <iomanip>

// 构造函数：初始化样本点和阶数
PPForm::PPForm(const std::vector<double>& x, const std::vector<double>& y, int degree)
    : x_(x), y_(y), degree_(degree), n_(x.size() - 1) {
    if (x.size() != y.size()) {
        throw std::invalid_argument("x and y must have the same size.");
    }
    if (x.size() < 2) {
        throw std::invalid_argument("At least two points are required.");
    }
    coefficients_.resize(n_, std::vector<double>(degree + 1, 0.0));
}

// 计算 Clamped 边界条件的样条
void PPForm::computeClampedSpline() {
    std::vector<double> a(n_ + 1), b(n_ + 1), c(n_ + 1), d(n_ + 1);

    // Step 1: 填充三对角矩阵系数
    for (size_t i = 1; i < n_; ++i) {
        a[i] = x_[i] - x_[i - 1];
        b[i] = 2.0 * (x_[i + 1] - x_[i - 1]);
        c[i] = x_[i + 1] - x_[i];
        d[i] = 6.0 * ((y_[i + 1] - y_[i]) / (x_[i + 1] - x_[i]) - (y_[i] - y_[i - 1]) / (x_[i] - x_[i - 1]));
    }

    // Clamped 边界条件
    b[0] = 2.0 * (x_[1] - x_[0]);
    c[0] = x_[1] - x_[0];
    d[0] = 6.0 * ((y_[1] - y_[0]) / (x_[1] - x_[0]));

    a[n_] = x_[n_] - x_[n_ - 1];
    b[n_] = 2.0 * (x_[n_] - x_[n_ - 1]);
    d[n_] = 6.0 * ((y_[n_] - y_[n_ - 1]) / (x_[n_] - x_[n_ - 1]));

    // Step 2: 求解三对角矩阵
    std::vector<double> m = solveTridiagonal(a, b, c, d);

    // Step 3: 计算样条系数
    for (size_t i = 0; i < n_; ++i) {
        coefficients_[i][0] = y_[i];
        coefficients_[i][1] = (y_[i + 1] - y_[i]) / (x_[i + 1] - x_[i]) - (x_[i + 1] - x_[i]) * (2.0 * m[i] + m[i + 1]) / 6.0;
        coefficients_[i][2] = m[i] / 2.0;
        coefficients_[i][3] = (m[i + 1] - m[i]) / (6.0 * (x_[i + 1] - x_[i]));
    }
}

// 计算 Natural 边界条件的样条
void PPForm::computeNaturalSpline() {
    std::vector<double> a(n_), b(n_ + 1), c(n_), d(n_ + 1);

    // Step 1: 填充三对角矩阵系数
    for (size_t i = 1; i < n_; ++i) {
        a[i] = x_[i] - x_[i - 1];
        b[i] = 2.0 * (x_[i + 1] - x_[i - 1]);
        c[i] = x_[i + 1] - x_[i];
        d[i] = 6.0 * ((y_[i + 1] - y_[i]) / (x_[i + 1] - x_[i]) - (y_[i] - y_[i - 1]) / (x_[i] - x_[i - 1]));
    }

    // Natural 边界条件
    b[0] = 1.0;
    c[0] = 0.0;
    d[0] = 0.0;

    a[n_ - 1] = 0.0;
    b[n_] = 1.0;
    d[n_] = 0.0;

    // Step 2: 求解三对角矩阵
    std::vector<double> m = solveTridiagonal(a, b, c, d);

    // Step 3: 计算样条系数
    for (size_t i = 0; i < n_; ++i) {
        coefficients_[i][0] = y_[i];
        coefficients_[i][1] = (y_[i + 1] - y_[i]) / (x_[i + 1] - x_[i]) - (x_[i + 1] - x_[i]) * (2.0 * m[i] + m[i + 1]) / 6.0;
        coefficients_[i][2] = m[i] / 2.0;
        coefficients_[i][3] = (m[i + 1] - m[i]) / (6.0 * (x_[i + 1] - x_[i]));
    }
}

// 计算 Periodic 边界条件的样条
void PPForm::computePeriodicSpline() {
    // Step 1: 设置矩阵
    std::vector<double> a(n_), b(n_), c(n_), d(n_);
    for (size_t i = 1; i < n_; ++i) {
        a[i] = x_[i] - x_[i - 1];
        b[i] = 2.0 * (x_[i + 1] - x_[i - 1]);
        c[i] = x_[i + 1] - x_[i];
        d[i] = 6.0 * ((y_[i + 1] - y_[i]) / (x_[i + 1] - x_[i]) - (y_[i] - y_[i - 1]) / (x_[i] - x_[i - 1]));
    }

    // Periodic 边界条件
    a[0] = x_[1] - x_[0];
    b[0] = 2.0 * (x_[n_] - x_[0]);
    c[0] = x_[n_] - x_[n_ - 1];
    d[0] = 6.0 * ((y_[1] - y_[0]) / (x_[1] - x_[0]) - (y_[n_] - y_[n_ - 1]) / (x_[n_] - x_[n_ - 1]));

    a[n_ - 1] = x_[n_] - x_[n_ - 1];
    b[n_ - 1] = 2.0 * (x_[n_] - x_[0]);
    c[n_ - 1] = x_[1] - x_[0];
    d[n_ - 1] = d[0];

    // Step 2: 求解三对角矩阵
    std::vector<double> m = solveTridiagonal(a, b, c, d);

    // Step 3: 计算样条系数
    for (size_t i = 0; i < n_; ++i) {
        coefficients_[i][0] = y_[i];
        coefficients_[i][1] = (y_[i + 1] - y_[i]) / (x_[i + 1] - x_[i]) - (x_[i + 1] - x_[i]) * (2.0 * m[i] + m[i + 1]) / 6.0;
        coefficients_[i][2] = m[i] / 2.0;
        coefficients_[i][3] = (m[i + 1] - m[i]) / (6.0 * (x_[i + 1] - x_[i]));
    }
}

// 导出样条数据到文件
void PPForm::exportData(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    outFile << std::fixed << std::setprecision(6);
    for (size_t i = 0; i < n_; ++i) {
        outFile << "Interval " << i << ": ";
        for (size_t j = 0; j <= degree_; ++j) {
            outFile << coefficients_[i][j] << " ";
        }
        outFile << "\n";
    }

    outFile.close();
}

// 解三对角矩阵方程
std::vector<double> PPForm::solveTridiagonal(const std::vector<double>& a, 
                                             const std::vector<double>& b, 
                                             const std::vector<double>& c, 
                                             const std::vector<double>& d) const {
    size_t n = d.size();
    std::vector<double> m(n), alpha(n), beta(n);

    alpha[0] = b[0];
    beta[0] = d[0] / alpha[0];

    for (size_t i = 1; i < n; ++i) {
        alpha[i] = b[i] - a[i] * c[i - 1] / alpha[i - 1];
        beta[i] = (d[i] - a[i] * beta[i - 1]) / alpha[i];
    }

    m[n - 1] = beta[n - 1];
    for (size_t i = n - 2; i < n; --i) {
        m[i] = beta[i] - c[i] * m[i + 1] / alpha[i];
    }

    return m;
}

// 返回样条系数
const std::vector<std::vector<double>>& PPForm::getCoefficients() const {
    return coefficients_;
}