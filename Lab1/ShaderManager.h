#pragma once
#include <unordered_map>
#include <memory>
#include <iostream>
#include <string>
#include "Shader.h"
class ShaderManager {
public:
    static ShaderManager& Instance() {
        static ShaderManager instance;
        return instance;
    }

    std::shared_ptr<Shader> loadShader(const std::string& tag, const std::string& vertFile, const std::string& fragFile);
    std::shared_ptr<Shader> getShader(const std::string& tag);

protected:
    ShaderManager() = default; // Private constructor (Singleton)
    ~ShaderManager() = default;
    ShaderManager(const ShaderManager&) = delete;

private:
    void cleanupShaders();
    ShaderManager& operator=(const ShaderManager&) = delete;
    std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
};