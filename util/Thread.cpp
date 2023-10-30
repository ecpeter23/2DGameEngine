#include "Thread.h"

std::atomic<ulong> Thread::idCounter(0);

Thread::Thread() : id(++idCounter), stopped(false), loopEnabled(false), hertz(0) {}

void Thread::addFunction(const std::function<void()>& function, i32 index) {
    std::unique_lock<std::mutex> lock(mutex);
    if (index >= 0 && index < functions.size()) {
        functions.insert(functions.begin() + index, function);
        return;
    }

    functions.emplace_back(function);
}

void Thread::start(bool loop, f64 hertz) {
    std::unique_lock<std::mutex> lock(mutex);
    loopEnabled = loop;
    this->hertz = hertz;
    lock.unlock();

    thread = std::thread([this, hertz] {
        do {
            auto startTime = std::chrono::high_resolution_clock::now();

            {
                std::unique_lock<std::mutex> lock(mutex);
                cv.wait(lock, [this] { return !pauseFlag.load() && !stopped; });

                if(waitFlag.load()) {
                    lock.unlock();  // Unlock the mutex while sleeping
                    std::this_thread::sleep_for(waitDuration.load());
                    waitFlag.store(false);  // Reset the wait flag after waiting
                    waitDuration.store(std::chrono::milliseconds(0));
                } else {
                    for (auto& function : functions) {
                        if (stopped || !function) { // Check if the function object is valid
                            break;
                        }

                        function();
                    }
                }
            }

            if (loopEnabled && hertz > 0) {
                auto endTime = std::chrono::high_resolution_clock::now();
                auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
                auto sleepDuration = std::chrono::milliseconds((i32)(1000 / hertz)) - elapsedTime;

                if (sleepDuration.count() > 0) {
                    std::this_thread::sleep_for(sleepDuration);
                }
            }

        } while (loopEnabled && !stopped);
    });
}

void Thread::pause() {
    pauseFlag.store(true);
}

void Thread::wait(u32 milliseconds) {
    std::unique_lock<std::mutex> lock(mutex);  // Lock the mutex when setting the wait flags
    waitFlag.store(true);
    waitDuration.store(std::chrono::milliseconds(milliseconds));
}

void Thread::resume() {
    pauseFlag.store(false);
    waitFlag.store(false);
    cv.notify_all();  // Notify the thread to check the pause flag
}

void Thread::end() {
    {
        std::unique_lock<std::mutex> lock(mutex);
        pauseFlag.store(false);
        stopped = true;
    }
    cv.notify_all();

    if (thread.joinable()) {
        thread.join();
    }
}

bool Thread::running() const {
    std::lock_guard<std::mutex> lock(mutex);
    return thread.joinable() && !stopped.load();
}

ulong Thread::getID() const {
    return id;
}
