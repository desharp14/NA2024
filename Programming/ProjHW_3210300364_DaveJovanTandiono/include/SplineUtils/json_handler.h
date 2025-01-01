#ifndef JSON_HANDLER_H
#define JSON_HANDLER_H

#include <string>
#include <vector>
#include <json/json.h>

/**
 * @class JSONHandler
 * @brief 提供 JSON 文件的加载和保存功能，用于存储和读取数据。
 */
class JSONHandler {
public:
    /**
     * @brief 从 JSON 文件加载二维数据。
     * @param filePath JSON 文件路径。
     * @param x 加载后的 x 数据。
     * @param y 加载后的 y 数据。
     */
    static void loadData(const std::string& filePath, std::vector<double>& x, std::vector<double>& y);

    /**
     * @brief 保存二维数据到 JSON 文件。
     * @param filePath JSON 文件路径。
     * @param x 要保存的 x 数据。
     * @param y 要保存的 y 数据。
     */
    static void saveData(const std::string& filePath, const std::vector<double>& x, const std::vector<double>& y);

    /**
     * @brief 保存三维数据到 JSON 文件。
     * @param filePath JSON 文件路径。
     * @param x 要保存的 x 数据。
     * @param y 要保存的 y 数据。
     * @param z 要保存的 z 数据。
     */
    static void saveData3D(const std::string& filePath, 
                           const std::vector<double>& x, 
                           const std::vector<double>& y, 
                           const std::vector<double>& z);

    /**
     * @brief 从 JSON 文件加载三维数据。
     * @param filePath JSON 文件路径。
     * @param x 加载后的 x 数据。
     * @param y 加载后的 y 数据。
     * @param z 加载后的 z 数据。
     */
    static void loadData3D(const std::string& filePath, 
                           std::vector<double>& x, 
                           std::vector<double>& y, 
                           std::vector<double>& z);
};

#endif // JSON_HANDLER_H