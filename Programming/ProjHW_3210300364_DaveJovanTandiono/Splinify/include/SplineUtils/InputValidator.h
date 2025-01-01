#ifndef INPUT_VALIDATOR_H
#define INPUT_VALIDATOR_H

#include <vector>
#include <utility>
#include <stdexcept>

// 数据输入验证类
class InputValidator {
public:
    /**
     * 验证输入点的有效性
     * @param points 数据点列表，每个点为 (x, y) 格式
     * @throws std::invalid_argument 如果数据点不符合要求
     */
    static void validateInput(const std::vector<std::pair<double, double>>& points);
};

#endif // INPUT_VALIDATOR_H