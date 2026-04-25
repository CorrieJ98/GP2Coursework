#include "DLLManager.h"


// Get Singleton Instance
DLLManager& DLLManager::getInstance() {
    static DLLManager instance;
    return instance;
}

// Load a DLL
bool DLLManager::loadDLL(const std::string& dllName) {
    if (loadedDLLs.find(dllName) != loadedDLLs.end()) {
        std::cout << "[LOG] [DLL MANAGER] DLL already loaded: " << dllName << std::endl;
        return true;
    }

    HINSTANCE hDLL = LoadLibrary(dllName.c_str());
    if (!hDLL) {
        std::cerr << "[ERROR] [DLL MANAGER] Failed to load DLL: " << dllName << std::endl;
        return false;
    }

    loadedDLLs[dllName] = hDLL;
    std::cout << "[LOG] [DLL MANAGER] Successfully loaded DLL: " << dllName << std::endl;
    return true;
}

// Unload a specific DLL
void DLLManager::unloadDLL(const std::string& dllName) {
    auto it = loadedDLLs.find(dllName);
    if (it != loadedDLLs.end()) {
        FreeLibrary(it->second);
        loadedDLLs.erase(it);
        std::cout << "[LOG] [DLL MANAGER] Unloaded DLL: " << dllName << std::endl;

    }
    else {
        std::cerr << "[ERROR] [DLL MANAGER] DLL not found: " << dllName << std::endl;
    }
}

// Unload all DLLs on destruction
DLLManager::~DLLManager() {
    unloadAll();
}

// Unload all DLLs
void DLLManager::unloadAll() {
    while (!loadedDLLs.empty()) {
        auto it = loadedDLLs.begin();
        FreeLibrary(it->second);
        std::cout << "[LOG] [DLL MANAGER] Unloaded DLL: " << it->first << " #" << it->second << std::endl;
        loadedDLLs.erase(it);
    }
}

