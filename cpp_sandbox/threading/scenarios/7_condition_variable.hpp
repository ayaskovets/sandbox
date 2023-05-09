#pragma once

#include <vector>

#include "framework.hpp"

namespace sandbox::threading::scenarios {

SCENARIO(ConditionVariable, "7: condition variable") {
    std::mutex mutex;
    std::condition_variable cv;

    std::vector<int> stack{};

    std::thread producer([&mutex, &cv, &stack](){
        for (int i = 0; i < 2; ++i) {
            {
                std::unique_lock lock(mutex);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                stack.push_back(i);
                cv.notify_one();
            }
        }
    });

    std::thread consumer1([&mutex, &cv, &stack, this](){
        std::unique_lock lock(mutex);
        cv.wait(lock, [&stack](){ return !stack.empty(); }); // unlock, wait for predicate

        MLog("consumer1 got {}", stack.back());
        stack.pop_back();
    });

    std::thread consumer2([&mutex, &cv, &stack, this](){
        std::unique_lock lock(mutex);
        cv.wait(lock, [&stack](){ return !stack.empty(); });

        MLog("consumer2 got {}", stack.back());
        stack.pop_back();
    });

    producer.join();
    consumer1.join();
    consumer2.join();
    Log("joined all threads");
}

}  // namespace sandbox::threading::scenarios
