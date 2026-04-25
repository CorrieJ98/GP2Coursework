#include "ShaderManager.h"

std::shared_ptr<Shader> ShaderManager::loadShader(const std::string& tag, const std::string& vertFile, const std::string& fragFile)
{
    if (shaders.find(tag) != shaders.end()) {
        std::cerr << "Shader already loaded: " << tag << std::endl;
        return shaders[tag];
    }

    std::shared_ptr<Shader> shader = std::make_shared<Shader>(); // declare shared pointer on the heap.
    shader->init(vertFile, fragFile);
    shaders[tag] = shader;
    return shader;
}

std::shared_ptr<Shader> ShaderManager::getShader(const std::string& tag) {
    if (shaders.find(tag) == shaders.end()) {
        std::cerr << "Shader not found: " << tag << std::endl;
        return nullptr;
    }
    return shaders[tag];
}

void ShaderManager::cleanupShaders() {
    shaders.clear();
}
