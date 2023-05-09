#pragma once

#include "framework.hpp"

namespace sandbox::threading::scenarios {

SCENARIO(DetachJoin, "1: start, join a thread") {
    std::thread thread([](){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    });

    thread.detach();

    Log("started thread (joinable={})", thread.joinable());

    try {
        thread.join();
    } catch (const std::system_error& e) {
        Log("{}", e.what());
    }
}

}  // namespace sandbox::threading::scenarios
