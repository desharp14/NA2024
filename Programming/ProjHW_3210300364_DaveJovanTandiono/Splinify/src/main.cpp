#include <iostream>
#include "../include/SplineUtils/CubicSpline.h"
#include "../include/SplineUtils/BSpline.h"

int main() {
    std::cout << "Welcome to the CubicSpline and BSpline Program!" << std::endl;

    // CubicSpline 测试
    CubicSpline cubicSpline;
    std::cout << "Testing CubicSpline..." << std::endl;

    // 添加样例点
    cubicSpline.addPoint(0.0, 0.0);
    cubicSpline.addPoint(1.0, 2.0);
    cubicSpline.addPoint(2.0, 1.0);
    cubicSpline.addPoint(3.0, 3.0);
    cubicSpline.addPoint(4.0, 4.0);

    // 设置边界条件并计算系数
    cubicSpline.setBoundaryType(CubicSpline::Natural);
    cubicSpline.triggerComputation();

    // 插值计算示例
    std::cout << "CubicSpline Interpolation Results:" << std::endl;
    for (double x = 0.0; x <= 4.0; x += 0.5) {
        try {
            double y = cubicSpline.interpolate(x);
            std::cout << "x: " << x << ", y: " << y << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    // BSpline 测试
    BSpline bSpline;
    std::cout << "\nTesting BSpline..." << std::endl;

    // 添加样例点
    bSpline.addPoint(0.0, 0.0);
    bSpline.addPoint(1.0, 2.0);
    bSpline.addPoint(2.0, 1.0);
    bSpline.addPoint(3.0, 3.0);
    bSpline.addPoint(4.0, 4.0);

    // 设置边界条件并计算节点
    bSpline.setBoundaryType(BSpline::Natural);
    bSpline.triggerComputation();

    // 插值计算示例
    std::cout << "BSpline Interpolation Results:" << std::endl;
    for (double x = 0.0; x <= 4.0; x += 0.5) {
        try {
            double y = bSpline.interpolate(x);
            std::cout << "x: " << x << ", y: " << y << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    std::cout << "\nProgram completed successfully!" << std::endl;

    return 0;
}