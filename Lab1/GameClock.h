#pragma once
#include <chrono>
#include <thread>

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

    // Define static member outside class
    //int counter::counter_ = 0;

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

} // namespace gc