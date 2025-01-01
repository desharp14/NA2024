#include "../../include/SplineUtils/BSpline.h"
#include <iostream>
#include <fstream>
#include <vector>

// 测试 B 样条
void testBSpline(const std::string& testName, const std::vector<double>& knots,
                 const std::vector<double>& controlPoints, int degree) {
    try {
        // 创建 B 样条对象
        BSpline spline(degree, knots, controlPoints);

        // 确保路径正确
        std::string filePath = "build/data/" + testName + ".txt";
        std::ofstream outFile(filePath);
        if (!outFile.is_open()) {
            std::cerr << "无法打开文件: " << filePath << std::endl;
            return;
        }

        // 获取插值范围
        double x_start = knots[degree]; // 从第一个非零节点开始
        double x_end = knots[knots.size() - degree - 1]; // 到最后一个有效节点结束

        // 计算插值并写入文件
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
        std::cout << "测试 " << testName << " 已完成，结果写入: " << filePath << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "测试失败: " << testName << "，原因: " << e.what() << std::endl;
    }
}

int main() {
    // 修正后的测试数据点
    std::vector<double> knots = { 0.0, 0.0, 0.0, 1.0, 2.0, 3.0, 4.0, 4.0 };
    std::vector<double> controlPoints = { 0.5, 1.0, 1.5, 2.5, 3.0 };
    int degree = 2; // B 样条阶数

    // 执行三种边界条件测试
    testBSpline("Natural_Boundary_Test_BSpline", knots, controlPoints, degree);
    testBSpline("Periodic_Boundary_Test_BSpline", knots, controlPoints, degree);
    testBSpline("Clamped_Boundary_Test_BSpline", knots, controlPoints, degree);

    return 0;
}