#ifndef B_FORM_H
#define B_FORM_H

#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <iomanip>

// B-样条类
class BForm {
public:
    // 构造函数，初始化 B-样条类
    BForm(const std::vector<double>& x, const std::vector<double>& y, int degree, const std::vector<double>& knots);

    // 计算 B-样条的系数
    void computeBSpline();

    // 导出计算结果到指定文件
    void exportData(const std::string& filename) const;

    // 在指定点 t 处评估 B-样条的值
    double evaluate(double t) const;

    // 获取样条系数
    const std::vector<std::vector<double>>& getCoefficients() const;

    // 获取 B-样条的阶数
    int getDegree() const;

    // 获取节点向量
    const std::vector<double>& getKnots() const;

    // 获取样本点 x 和 y
    const std::vector<double>& getX() const;
    const std::vector<double>& getY() const;

private:
    std::vector<double> x_;                         // 样本点 x 坐标
    std::vector<double> y_;                         // 样本点 y 坐标
    int degree_;                                    // 样条的阶数
    std::vector<double> knots_;                     // 节点向量
    std::vector<std::vector<double>> coefficients_; // 样条系数矩阵
    size_t n_;                                      // 样条段的数量

    // 递归计算 B-样条基函数
    double basisFunction(int i, int k, double t) const;

    // 求解三对角线性系统
    std::vector<double> solveTridiagonal(const std::vector<double>& a, 
                                         const std::vector<double>& b, 
                                         const std::vector<double>& c, 
                                         const std::vector<double>& d) const;

    // 检查输入数据是否有效
    void validateInput() const;
};

#endif // B_FORM_H