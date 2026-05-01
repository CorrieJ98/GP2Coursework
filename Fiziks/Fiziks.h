#pragma once

#ifdef FIZIKS_EXPORTS
#define FIZIKS_API __declspec(dllexport)
#else
#define FIZIKS_API __declspec(dllimport)
#endif

#include "pch.h"
#include "framework.h"

extern "C" FIZIKS_API void HelloWorld();