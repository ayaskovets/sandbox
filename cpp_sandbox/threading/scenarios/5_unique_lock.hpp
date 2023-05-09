#pragma once

#include "framework.hpp"

namespace sandbox::threading::scenarios {

SCENARIO(UniqueLock, "5: unique lock") {
    std::mutex mutex1;

    std::mutex mutex2;
    mutex2.lock();

    std::timed_mutex mutex3;
    mutex3.lock();

    {
        std::unique_lock lock1(mutex1, std::defer_lock);
        std::unique_lock lock2(mutex2, std::try_to_lock);
        std::unique_lock lock3(mutex3, std::adopt_lock);

        Log("lock1 owns_lock={} on construction", lock1.owns_lock());
        Log("lock2 owns_lock={} on construction", lock2.owns_lock());
        Log("lock2 owns_lock={} on construction", lock3.owns_lock());

        lock1.lock();
        Log("lock1 owns_lock={} on lock()", lock1.owns_lock());
    }

    Log("lock2 try_lock={} on destruction", mutex2.try_lock());

    std::lock_guard lock(mutex3);
    Log("lock3 is unlocked on descruction");
}

}  // namespace sandbox::threading::scenarios
