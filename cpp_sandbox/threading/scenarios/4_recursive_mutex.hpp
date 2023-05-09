#pragma once

#include "framework.hpp"

namespace sandbox::threading::scenarios {

SCENARIO(RecursiveMutex, "4: recursive mutex") {
    std::recursive_mutex mutex;

    mutex.lock();
    mutex.lock();

    mutex.unlock();
    Log("unlocked mutex");

    std::thread thread([&mutex, this](){
        while (true) {
            const auto try_lock = mutex.try_lock();

            Log("thread try_lock={}", try_lock);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            if (try_lock) {
                break;
            }
        }
        mutex.unlock();
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    mutex.unlock();

    thread.join();
    Log("joined thread");
}

}  // namespace sandbox::threading::scenarios
