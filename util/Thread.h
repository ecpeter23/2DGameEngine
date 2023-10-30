#pragma once

#include "datatypes.h"
#include <functional>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>

class Thread {
public:
    Thread();

    void start(bool loop = false, f64 hertz = 0);
    void wait(u32 nanoseconds);
    void pause();
    void resume();
    void end();
    [[nodiscard]] bool running() const;
    [[nodiscard]] unsigned long getID() const;
    void addFunction(const std::function<void()>& function, i32 index = -1);

    template <typename Func, typename... Args>
    void addFunctionWithArgs(const Func& function, Args&&... args) {
        auto bound_function = std::bind(function, std::forward<Args>(args)...);
        addFunction(bound_function);
    }

    template <typename Func, typename... Args>
    void addFunctionWithArgs(const Func& function, int index, Args&&... args) {
        auto bound_function = std::bind(function, std::forward<Args>(args)...);
        addFunction(bound_function, index);
    }



private:
    std::thread thread;
    std::vector<std::function<void()>> functions;
    mutable std::mutex mutex;
    std::condition_variable cv;
    std::atomic<bool> stopped;
    std::atomic<bool> pauseFlag;
    std::atomic<bool> waitFlag;
    std::atomic<std::chrono::milliseconds> waitDuration;
    bool loopEnabled;
    f64 hertz;
    ulong id;
    static std::atomic<ulong> idCounter;
};
