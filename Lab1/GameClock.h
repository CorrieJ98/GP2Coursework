#pragma once
#include <chrono>
#include <thread>

#ifndef DESIRED_FPS
#define DESIRED_FPS 60
#endif // !DESIRED_FPS

#ifndef GAMECLOCK_H
#define GAMECLOCK_H

/*
IMPLEMENTATION
        
GameLoop()
{
    while(gameLooping)
    {
        counter.IncrementCounter(1);
        deltaTime._deltaTimeFrameStart();
        ProcessInput();
        UpdateAllGameObjects();
        DrawGame();
        deltaTime._deltaTimeFrameEnd();
        deltaTime.CapFrameRate(DESIRED_FPS);


        std::printf(" Frame Time: %.2f ms, Target FPS: %d, Current FPS: %.2f, Counter: %d \r",deltaTime.GetDT_ms(), DESIRED_FPS, 1000.0f / deltaTime.GetDT_ms(), counter.ReadCounter());
        fflush(stdout);
    }
}
    1. deltaTime and counter singletons must be instantiated in the main game file
    2. deltaTime must be captured before first update and after last draw call each frame
    3. DESIRED_FPS can be defined either in here or in the main game file before including GameClock.h
    4. std::printf line is optional, but gives real-time feedback on frame time. Be aware that fflush(stdout) will remove any other printf/std::cout statements from console.
*/

namespace gc {

    constexpr float FPS_MAX_FRAME_TIME = 16.6666666667f; // 1000ms / desired FPS (60)

    class counter {
    public:

        static counter& Instance() {
            static counter instance; // single instance
            return instance;
        }

        int ReadCounter() const { return counter_; }
        void ResetCounter() { counter_ = 0; }

        void IncrementCounter()
        {
            _checkMaxValue();
            counter_++;
        }
        void IncrementCounter(int64_t delta)
        {
            _checkMaxValue();
            counter_ += delta;
        }

    protected:
        void _checkMaxValue() {
            if (counter_ >= INT32_MAX - 1000) {
                ResetCounter();
            }
        }

    private:
        int counter_;
    };



#ifndef DELTATIME
#define DELTATIME
    class dt {
    public:
        static dt& Instance() {
            static dt instance; // single instance
            return instance;
        }

        float GetDT_ms() const { return deltaTime; }
        float GetDT_sec() const { return deltaTime / 1000.0f; }

        void _deltaTimeFrameStart() {
            frameStart = std::chrono::steady_clock::now();
        }

        void _deltaTimeFrameEnd() {
            frameEnd = std::chrono::steady_clock::now();
            updateDeltaTime();
        }

        // if no fps specified, cap to 60fps
        void CapFrameRate() {
            float frameTime = GetDT_ms();
            if (frameTime < FPS_MAX_FRAME_TIME) {
                auto sleepDuration = std::chrono::milliseconds(static_cast<int>(FPS_MAX_FRAME_TIME - frameTime));
                std::this_thread::sleep_for(sleepDuration);
                // Update deltaTime after sleeping
                frameEnd = std::chrono::steady_clock::now();
                updateDeltaTime();
            }
        }

        void CapFrameRate(int fps) {
            float frameTime = GetDT_ms();
            float maxFrameTime = 1000.0f / static_cast<float>(fps);
            if (frameTime < (1000 / fps)) {
                auto sleepDuration = std::chrono::milliseconds(static_cast<int>(maxFrameTime - frameTime));
                std::this_thread::sleep_for(sleepDuration);
                // Update deltaTime after sleeping
                frameEnd = std::chrono::steady_clock::now();
                updateDeltaTime();
            }
        }

    private:
        dt() : deltaTime(0.0f) {} // private constructor

        void updateDeltaTime() {
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart);
            deltaTime = static_cast<float>(duration.count());
        }

        float deltaTime;
        std::chrono::steady_clock::time_point frameStart;
        std::chrono::steady_clock::time_point frameEnd;
    };
#endif // !DELTATIME

} 

#endif // !GAMECLOCK_H


/*
    I am super fucking proud of this implementation. It works as intended,
    and is easy to use. Just include GameClock.h in your main game file,
    record the delta time at the start and end of each frame, and call
    CapFrameRate() to limit the frame rate.

    Any objects that require the use of delta time can access it via the
    main Update() method and taking deltaTime as a parameter. Easy peasy.
*/