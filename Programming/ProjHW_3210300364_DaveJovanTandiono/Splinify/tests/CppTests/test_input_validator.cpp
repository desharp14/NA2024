#include "../../include/SplineUtils/InputValidator.h"
#include <iostream>
#include <vector>

int main() {
    try {
        // 正常输入数据测试
        std::vector<std::pair<double, double>> validPoints = {
            {0.0, 0.0}, {1.0, 2.0}, {2.0, 1.0}, {3.0, 3.0}
        };

        std::cout << "正在验证正确数据..." << std::endl;
        InputValidator::validateInput(validPoints);
        std::cout << "正确数据验证通过！" << std::endl;

        // 异常输入测试：x 值重复
        std::vector<std::pair<double, double>> invalidPoints1 = {
            {0.0, 0.0}, {1.0, 2.0}, {1.0, 1.0}, {3.0, 3.0}
        };

        std::cout << "\n正在验证 x 值重复数据..." << std::endl;
        InputValidator::validateInput(invalidPoints1);

    } catch (const std::exception& e) {
        std::cerr << "错误：" << e.what() << std::endl;
    }

    try {
        // 异常输入测试：数据点过少
        std::vector<std::pair<double, double>> invalidPoints2 = {{0.0, 0.0}};

        std::cout << "\n正在验证数据点过少..." << std::endl;
        InputValidator::validateInput(invalidPoints2);

    } catch (const std::exception& e) {
        std::cerr << "错误：" << e.what() << std::endl;
    }

    return 0;
}