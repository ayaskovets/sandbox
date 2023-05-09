#pragma once

#include "framework.hpp"

namespace sandbox::threading::scenarios {

SCENARIO(SharedMutex, "6: shared mutex") {
    std::shared_mutex mutex;

    std::thread thread1([&mutex](){
        std::shared_lock lock(mutex);
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    });

    std::thread thread2([&mutex](){
        std::shared_lock lock(mutex);
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
    });

    std::thread thread3([&mutex, this](){
        while (true) {
            const auto try_lock = mutex.try_lock();

            MLog("thread3 try_lock={}", try_lock);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            if (try_lock) {
                break;
            }
        }
        mutex.unlock();
    });

    thread1.join();
    MLog("joined thread1");
    thread2.join();
    MLog("joined thread2");

    thread3.join();
    Log("joined thread3");

    std::lock_guard lock(mutex);
    Log("try_lock_shared={}", mutex.try_lock_shared());
}

}  // namespace sandbox::threading::scenarios
