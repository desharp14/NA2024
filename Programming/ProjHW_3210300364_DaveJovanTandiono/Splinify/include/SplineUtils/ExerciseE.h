#ifndef EXERCISEE_H
#define EXERCISEE_H

#include <vector>
#include <string>

namespace SplineUtils {

class ExerciseE {
public:
    ExerciseE(const std::vector<double>& x_vals, const std::vector<double>& y_vals);

    // 计算样条插值
    void calculateSpline();

    // 打印结果
    void printResults() const;

    // 保存结果到文件
    void saveResults(const std::string& filename) const;

    // 根据输入值进行插值
    double interpolate(double x_val) const;

private:
    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> y_spline;  // 存储计算后的样条插值结果
};

} // namespace SplineUtils

#endif // EXERCISEE_H