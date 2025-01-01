#include "../../include/SplineUtils/json_handler.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

void JSONHandler::loadData(const std::string& filePath, std::vector<double>& x, std::vector<double>& y) {
    std::ifstream file(filePath, std::ifstream::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open JSON file: " + filePath);
    }

    Json::Value root;
    file >> root;

    for (const auto& value : root["x"]) {
        x.push_back(value.asDouble());
    }

    for (const auto& value : root["y"]) {
        y.push_back(value.asDouble());
    }

    file.close();
}

void JSONHandler::saveData(const std::string& filePath, const std::vector<double>& x, const std::vector<double>& y) {
    Json::Value root;
    for (const auto& value : x) {
        root["x"].append(value);
    }
    for (const auto& value : y) {
        root["y"].append(value);
    }

    std::ofstream file(filePath, std::ofstream::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open JSON file: " + filePath);
    }

    file << root;
    file.close();
}

void JSONHandler::saveData3D(const std::string& filePath, 
                             const std::vector<double>& x, 
                             const std::vector<double>& y, 
                             const std::vector<double>& z) {
    Json::Value root;
    for (const auto& value : x) {
        root["x"].append(value);
    }
    for (const auto& value : y) {
        root["y"].append(value);
    }
    for (const auto& value : z) {
        root["z"].append(value);
    }

    std::ofstream file(filePath, std::ofstream::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open JSON file: " + filePath);
    }

    file << root;
    file.close();
}

void JSONHandler::loadData3D(const std::string& filePath, 
                             std::vector<double>& x, 
                             std::vector<double>& y, 
                             std::vector<double>& z) {
    std::ifstream file(filePath, std::ifstream::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open JSON file: " + filePath);
    }

    Json::Value root;
    file >> root;

    for (const auto& value : root["x"]) {
        x.push_back(value.asDouble());
    }
    for (const auto& value : root["y"]) {
        y.push_back(value.asDouble());
    }
    for (const auto& value : root["z"]) {
        z.push_back(value.asDouble());
    }

    file.close();
}