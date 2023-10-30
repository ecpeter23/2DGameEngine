#pragma once

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

    void start(bool loop = false, double hertz = 0);
    void pause();
    void resume();
    void end();
    [[nodiscard]] bool running() const;
    [[nodiscard]] unsigned long getID() const;
    void addFunction(const std::function<void()>& function, int index = -1);

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
    bool paused;
    bool stopped;
    bool loopEnabled;
    int hertz;
    unsigned long id;
    static std::atomic<unsigned long> idCounter;
};
