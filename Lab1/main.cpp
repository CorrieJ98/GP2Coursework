#include <iostream>
#include "MainGame.h"
#include "DLLManager.h"

int main(int argc, char** argv) //argument used to call SDL main
{
	MainGame mainGame;
	mainGame.Run();
    //TestHelloWorldDLL();
	return 0;
}

void TestHelloWorldDLL()
{
    DLLManager& dllManager = DLLManager::getInstance();

    const std::string dllName = "Fiziks.dll";

    // Ensure the DLL is loaded
    if (!dllManager.loadDLL(dllName)) {
        std::cerr << "[ERROR] Failed to load DLL: " << dllName << std::endl;
        return;
    }

    // Define function pointer type
    using HelloWorldFunc = void(*)();

    // Get the function
    HelloWorldFunc helloWorld = dllManager.getFunction<HelloWorldFunc>(dllName, "HelloWorld");

    if (!helloWorld) {
        std::cerr << "[ERROR] Failed to get HelloWorld function\n";
        return;
    }

    // Call the function
    helloWorld();
}