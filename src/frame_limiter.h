#pragma once

#include <chrono>
#include <thread>

class FrameLimiter
{
    std::chrono::steady_clock::time_point last;
    std::chrono::steady_clock::duration spf;

public:
    FrameLimiter(int fps = 60) : spf(std::chrono::steady_clock::duration(1000000000U / fps))
    {
        last = std::chrono::steady_clock::now();
    }

    double next_frame()
    {
        using namespace std::chrono;
        std::this_thread::sleep_until(last + spf);
        auto tmp = last;
        last = steady_clock::now();
        return duration_cast<duration<double>>(last - tmp).count();
    }
};