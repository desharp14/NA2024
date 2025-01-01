#ifndef PP_FORM_H
#define PP_FORM_H

#include <vector>
#include <string>

// Piecewise Polynomial Form (PPForm) 类，用于实现分段多项式样条
class PPForm {
public:
    // 构造函数：初始化节点和样本值，并设置样条的阶数
    PPForm(const std::vector<double>& x, const std::vector<double>& y, int degree);

    // 计算带 Clamped 边界条件的样条
    void computeClampedSpline();

    // 计算带 Natural 边界条件的样条
    void computeNaturalSpline();

    // 计算带 Periodic 边界条件的样条
    void computePeriodicSpline();

    // 导出样条数据到文件
    void exportData(const std::string& filename) const;

    // 返回计算后的样条系数，用于进一步分析或绘图
    const std::vector<std::vector<double>>& getCoefficients() const;

private:
    std::vector<double> x_;                          // 样本点的 x 坐标
    std::vector<double> y_;                          // 样本点的 y 坐标
    int degree_;                                     // 样条的阶数
    size_t n_;                                       // 样本点数量 - 1
    std::vector<std::vector<double>> coefficients_;  // 样条系数

    // 解三对角矩阵方程的工具函数
    std::vector<double> solveTridiagonal(const std::vector<double>& a, 
                                         const std::vector<double>& b, 
                                         const std::vector<double>& c, 
                                         const std::vector<double>& d) const;

    // 生成均匀分布的插值节点
    std::vector<double> generateUniformKnots(size_t numPoints) const;

    // 用于生成样条插值的工具函数
    double evaluateSpline(double t, const std::vector<double>& coeffs) const;
};

#endif