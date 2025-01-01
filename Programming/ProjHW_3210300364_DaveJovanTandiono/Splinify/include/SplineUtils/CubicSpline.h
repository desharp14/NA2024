#ifndef CUBICSPLINE_H
#define CUBICSPLINE_H

#include <vector>
#include <utility> // 用于 std::pair

class CubicSpline {
public:
    enum BoundaryType {
        Natural,   // 自然边界
        Periodic,  // 周期边界
        Clamped    // 夹持边界
    };

    CubicSpline();
    ~CubicSpline();

    void setBoundaryType(BoundaryType type);  // 设置边界条件类型
    void setBoundaryValues(double first_derivative_start, double first_derivative_end);  // 设置边界处的一阶导数值
    void addPoint(double x, double y);  // 添加控制点
    double interpolate(double x) const;  // 插值计算
    void clear();  // 清除所有控制点和计算结果
    void triggerComputation();  // 提供一个触发计算的公共方法

private:
    std::vector<std::pair<double, double>> points;  // 控制点
    std::vector<double> coefficients;  // 插值系数
    BoundaryType boundaryType = Natural;  // 边界条件，默认为自然边界
    double boundaryFirstDerivativeStart = 0.0;  // 起始点的一阶导数
    double boundaryFirstDerivativeEnd = 0.0;  // 结束点的一阶导数

    void computeCoefficients();  // 计算插值系数
};

#endif // CUBICSPLINE_H