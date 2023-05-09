#pragma once

#include "framework.hpp"

namespace sandbox::threading::scenarios {

SCENARIO(ThreadLocal, "2: thread_local") {
    const auto worker = [](int start, int finish){
        static thread_local int sum = 0;

        for (int i = start; i < finish; ++i) {
            sum += i;
        }

        return sum;
    };

    auto future1 = std::async(worker, 0, 5);
    auto future2 = std::async(worker, 5, 10);

    Log("future1 result={}", future1.get());
    Log("future2 result={}", future2.get());
}

}  // namespace sandbox::threading::scenarios
