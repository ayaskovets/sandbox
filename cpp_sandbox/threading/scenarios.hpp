#pragma once

#include <vector>
#include <memory>

#include "scenarios/framework.hpp"

namespace sandbox::threading {

std::vector<std::unique_ptr<Scenario>> GetScenarios();

}  // namespace sandbox::threading {
