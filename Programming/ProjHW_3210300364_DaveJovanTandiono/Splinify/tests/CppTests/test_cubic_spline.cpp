#include "../../include/SplineUtils/CubicSpline.h"
#include <iostream>
#include <fstream>
#include <vector>

void testSpline(const std::string& testName, CubicSpline::BoundaryType boundaryType,
                const std::vector<std::pair<double, double>>& testPoints,
                double boundaryStart = 0.0, double boundaryEnd = 0.0) {
    CubicSpline spline;
    spline.setBoundaryType(boundaryType);

    if (boundaryType == CubicSpline::Clamped) {
        spline.setBoundaryValues(boundaryStart, boundaryEnd);
    }

    // 将控制点添加到样条中
    for (const auto& point : testPoints) {
        spline.addPoint(point.first, point.second);
    }

    // 计算插值系数
    spline.triggerComputation();

    // 生成数据文件
    std::ofstream outFile("build/data/" + testName + ".txt");

    // 获取控制点的范围
    double x_start = testPoints.front().first;
    double x_end = testPoints.back().first;

    // 在控制点的范围内进行插值计算
    for (double x = x_start; x <= x_end; x += 0.1) {
        try {
            double y = spline.interpolate(x);
            outFile << x << " " << y << std::endl;
            std::cout << "x: " << x << ", y: " << y << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error at x = " << x << ": " << e.what() << std::endl;
        }
    }
    outFile.close();
}

int main() {
    // 测试数据点
    std::vector<std::pair<double, double>> testPoints = {
        {0.0, 0.0}, {1.0, 2.0}, {2.0, 1.0}, {3.0, 3.0}, {4.0, 4.0}
    };

    // 运行不同的边界条件测试
    testSpline("Natural_Boundary_Test_CubicSpline", CubicSpline::Natural, testPoints);
    testSpline("Periodic_Boundary_Test_CubicSpline", CubicSpline::Periodic, testPoints);
    testSpline("Clamped_Boundary_Test_CubicSpline", CubicSpline::Clamped, testPoints, 1.0, -1.0);

    return 0;
}