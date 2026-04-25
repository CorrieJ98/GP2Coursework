#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include "windows.h"

class DLLManager {
public:
    // Singleton pattern
    static DLLManager& getInstance();

    // Load a DLL by filename
    bool loadDLL(const std::string& dllName);
     
    // Unload a specific DLL
    void unloadDLL(const std::string& dllName);

    // Unload all loaded DLLs
    void unloadAll();

    // Get a specific function from loaded DLL
    template<typename T>
    T getFunction(const std::string& dllName, const std::string& functionName) {
        auto i = loadedDLLs.find(dllName);
        if (i == loadedDLLs.end()) {
            std::cerr << "[ERROR] [DLL MANAGER] DLL not loaded: " << dllName << std::endl;
            return nullptr;
        }

        FARPROC func = GetProcAddress(i->second, functionName.c_str());
        if (!func) {
            std::cerr << "[ERROR] [DLL MANAGER] Function not found: " << functionName << " in DLL: " << dllName << std::endl;
            return nullptr;
        }

        return reinterpret_cast<T>(func);
    }

private:
    DLLManager() = default;
    ~DLLManager();

    std::unordered_map<std::string, HINSTANCE> loadedDLLs;  // Stores loaded DLLs

    // Prevent copy/move
    DLLManager(const DLLManager&) = delete;
    DLLManager& operator=(const DLLManager&) = delete;
};
