#pragma once

#include "framework.hpp"

namespace sandbox::threading::scenarios {

SCENARIO(HardwareConcurrency, "0: get hardware concurrency") {
    Log("cores={}", std::thread::hardware_concurrency());
}

}  // namespace sandbox::threading::scenarios
