#pragma once
#include <chrono>

static class GameTime
{
public:
    GameTime()
    {
        lastTime = std::chrono::high_resolution_clock::now();
        deltaTime = 0.0;
    }

    void Update()
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = currentTime - lastTime;

        deltaTime = elapsed.count();
        lastTime = currentTime;
    }


    double GetDeltaTime() const { return deltaTime; }

private:
    std::chrono::high_resolution_clock::time_point lastTime;
    double deltaTime;

};
