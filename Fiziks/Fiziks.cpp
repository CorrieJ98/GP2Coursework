#include "pch.h"
#include "Fiziks.h"
#include <iostream>

extern "C" FIZIKS_API void HelloWorld()
{
    std::cout << "Hello from Fiziks DLL\n";
}