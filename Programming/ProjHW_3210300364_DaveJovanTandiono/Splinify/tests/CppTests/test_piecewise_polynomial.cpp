#include <iostream>
#include <fstream>
#include <vector>
#include "../../include/SplineUtils/PiecewisePolynomialSpline.h"

int main() {
    std::vector<double> x = {0, 1, 2, 3, 4};
    std::vector<double> y = {0, 1, 4, 9, 16};

    PiecewisePolynomialSpline spline(x, y);

    std::ofstream output("build/data/Piecewise_Polynomial_Spline.txt");
    if (!output.is_open()) {
        std::cerr << "无法打开输出文件！" << std::endl;
        return 1;
    }

    output << "x,y" << std::endl;
    for (double xi = 0; xi <= 4; xi += 0.1) {
        double yi = spline.evaluate(xi);
        output << xi << "," << yi << std::endl;
    }

    output.close();
    std::cout << "测试 PiecewisePolynomialSpline 已完成，结果写入: build/data/Piecewise_Polynomial_Spline.txt" << std::endl;
    return 0;
}