#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>

// 函数：目标函数
double targetFunction(double x) {
    return std::pow(x, 2) + std::sin(x);
}

// 函数：生成均匀分布的节点
std::vector<double> generateUniformNodes(double start, double end, int n) {
    std::vector<double> nodes(n);
    double step = (end - start) / (n - 1);
    for (int i = 0; i < n; ++i) {
        nodes[i] = start + i * step;
    }
    return nodes;
}

// 函数：导出数据到文件
void exportData(const std::string &filename, const std::vector<double> &x, const std::vector<double> &y) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return;
    }
    file << "x,y\n";
    for (size_t i = 0; i < x.size(); ++i) {
        file << x[i] << "," << y[i] << "\n";
    }
    file.close();
}

int main() {
    // 定义范围和节点数量
    double start = 0.0;
    double end = 10.0;
    int n = 20;  // 节点数量

    // 生成节点并计算目标函数值
    std::vector<double> x = generateUniformNodes(start, end, n);
    std::vector<double> y(x.size());
    for (size_t i = 0; i < x.size(); ++i) {
        y[i] = targetFunction(x[i]);
    }

    // 导出数据
    std::string outputFilename = "build/data/Exercise_A_Test.txt";
    exportData(outputFilename, x, y);

    std::cout << "测试 Exercise_A_Test 已完成，结果写入: " << outputFilename << std::endl;

    return 0;
}