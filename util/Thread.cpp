#include "Thread.h"

std::atomic<unsigned long> Thread::idCounter(0);

Thread::Thread() : id(++idCounter), paused(false), stopped(false), loopEnabled(false), hertz(0) {}

void Thread::addFunction(const std::function<void()>& function, int index) {
    std::unique_lock<std::mutex> lock(mutex);
    if (index >= 0 && index < functions.size()) {
        functions.insert(functions.begin() + index, function);
        return;
    }

    functions.emplace_back(function);
}

void Thread::start(bool loop, double hertz) {
    std::unique_lock<std::mutex> lock(mutex);
    loopEnabled = loop;
    this->hertz = hertz;
    lock.unlock();

    thread = std::thread([this, hertz] {
        do {
            auto startTime = std::chrono::high_resolution_clock::now();
            {
                std::unique_lock<std::mutex> lock(mutex);
                for (auto& function : functions) {
                    cv.wait(lock, [this] { return !paused && !stopped; });

                    if (stopped || !function) { // Check if the function object is valid
                        break;
                    }

                    function();
                }
            }

            if (loopEnabled && hertz > 0) {
                auto endTime = std::chrono::high_resolution_clock::now();
                auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
                auto sleepDuration = std::chrono::milliseconds((int)(1000 / hertz)) - elapsedTime;

                if (sleepDuration.count() > 0) {
                    std::this_thread::sleep_for(sleepDuration);
                }
            }

        } while (loopEnabled && !stopped);
    });
}

void Thread::pause() {
    std::unique_lock<std::mutex> lock(mutex);
    paused = true;
}

void Thread::resume() {
    std::unique_lock<std::mutex> lock(mutex);
    paused = false;
    cv.notify_all();
}

void Thread::end() {
    {
        std::unique_lock<std::mutex> lock(mutex);
        stopped = true;
        paused = false;
    }
    cv.notify_all();

    if (thread.joinable()) {
        thread.join();
    }
}

bool Thread::running() const {
    return thread.joinable() && !stopped;
}

unsigned long Thread::getID() const {
    return id;
}
