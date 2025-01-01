#include <iostream>
#include <vector>
#include "../../include/SplineUtils/ExerciseE.h"

int main() {
    // 创建一些测试数据
    std::vector<double> x_vals = {0.0, 1.0, 2.0, 3.0, 4.0};
    std::vector<double> y_vals = {0.0, 1.0, 4.0, 9.0, 16.0}; // y = x^2

    // 创建 ExerciseE 类的对象，传入测试数据
    SplineUtils::ExerciseE spline(x_vals, y_vals);

    // 计算样条插值
    spline.calculateSpline();

    // 打印插值结果
    spline.printResults();

    // 保存结果到文件
    spline.saveResults("build/data/Exercise_E_Spline_Results.txt");

    // 测试插值功能：给定一个值，返回插值结果
    double test_x = 2.5;
    double interpolated_y = spline.interpolate(test_x);
    std::cout << "Interpolated y at x = " << test_x << " : " << interpolated_y << std::endl;

    return 0;
}