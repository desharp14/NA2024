#include "../../include/SplineUtils/ExerciseE.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

namespace SplineUtils {

ExerciseE::ExerciseE(const std::vector<double>& x_vals, const std::vector<double>& y_vals)
    : x(x_vals), y(y_vals) {}

void ExerciseE::calculateSpline() {
    // 数组的大小
    size_t n = x.size();
    if (n < 2) {
        std::cerr << "数据点不足以进行插值！" << std::endl;
        return;
    }

    // 计算导数和斜率
    std::vector<double> h(n - 1), alpha(n), l(n + 1, 1.0), mu(n), z(n);
    for (size_t i = 0; i < n - 1; ++i) {
        h[i] = x[i + 1] - x[i];
        if (h[i] == 0) {
            std::cerr << "X值之间的间隔不能为零。" << std::endl;
            return;
        }
        alpha[i] = (3.0 / h[i]) * (y[i + 1] - y[i]) - (3.0 / h[i - 1]) * (y[i] - y[i - 1]);
    }

    // 求解三对角矩阵
    for (size_t i = 1; i < n - 1; ++i) {
        l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    // 回代过程
    std::vector<double> c(n), b(n - 1), d(n - 1);
    c[n - 1] = 0;
    for (size_t j = n - 2; j < n - 1; --j) {
        c[j] = z[j] - mu[j] * c[j + 1];
        b[j] = (y[j + 1] - y[j]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
        d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
    }

    // 将结果保存到 y_spline
    y_spline.resize(n);
    for (size_t i = 0; i < n - 1; ++i) {
        y_spline[i] = y[i] + b[i] * (x[i + 1] - x[i]) + c[i] * (x[i + 1] - x[i]) * (x[i + 1] - x[i]) / 2 + d[i] * (x[i + 1] - x[i]) * (x[i + 1] - x[i]) * (x[i + 1] - x[i]) / 6;
    }
}

void ExerciseE::printResults() const {
    std::cout << "Exercise E - Spline Interpolation Results:" << std::endl;
    for (size_t i = 0; i < x.size(); ++i) {
        std::cout << "x: " << x[i] << ", y_spline: " << y_spline[i] << std::endl;
    }
}

void ExerciseE::saveResults(const std::string& filename) const {
    std::ofstream out_file(filename);
    if (out_file.is_open()) {
        for (size_t i = 0; i < x.size(); ++i) {
            out_file << x[i] << " " << y_spline[i] << std::endl;
        }
        out_file.close();
        std::cout << "Results saved to " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file " << filename << std::endl;
    }
}

double ExerciseE::interpolate(double x_val) const {
    for (size_t i = 0; i < x.size() - 1; ++i) {
        if (x_val >= x[i] && x_val <= x[i + 1]) {
            return y[i] + (x_val - x[i]) * (y_spline[i] - y[i]) / (x[i + 1] - x[i]);
        }
    }
    return 0.0; // 超出范围返回 0.0
}

} // namespace SplineUtils