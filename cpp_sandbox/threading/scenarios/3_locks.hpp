#pragma once

#include "framework.hpp"

namespace sandbox::threading::scenarios {

SCENARIO(Locks, "3: locks") {
    std::timed_mutex mutex1, mutex2{};
    std::thread thread{};

    {
        const std::scoped_lock lock(mutex1, mutex2);
        thread = std::thread([&mutex1, &mutex2, this](){
            mutex1.try_lock_for(std::chrono::milliseconds(20));
            mutex2.try_lock_for(std::chrono::milliseconds(20));
            Log("thread locks timeout");
        });

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    thread.join();
    Log("joined thread");
}

}  // namespace sandbox::threading::scenarios
