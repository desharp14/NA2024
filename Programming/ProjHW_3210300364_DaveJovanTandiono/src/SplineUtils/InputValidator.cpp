#include "../../include/SplineUtils/InputValidator.h"

void InputValidator::validateInput(const std::vector<std::pair<double, double>>& points) {
    // 检查数据点数量是否足够
    if (points.size() < 2) {
        throw std::invalid_argument("输入的数据点数量必须至少为 2 个！");
    }

    // 检查 x 值是否严格递增
    for (size_t i = 1; i < points.size(); ++i) {
        if (points[i].first <= points[i - 1].first) {
            throw std::invalid_argument("数据点的 x 值必须严格递增！");
        }
    }
}