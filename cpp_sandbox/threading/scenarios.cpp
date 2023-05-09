#include "scenarios.hpp"

#include "scenarios/0_hardware_concurrency.hpp"
#include "scenarios/1_detach_join.hpp"
#include "scenarios/2_thread_local.hpp"
#include "scenarios/3_locks.hpp"
#include "scenarios/4_recursive_mutex.hpp"
#include "scenarios/5_unique_lock.hpp"
#include "scenarios/6_shared_mutex.hpp"
#include "scenarios/7_condition_variable.hpp"

namespace sandbox::threading {

std::vector<std::unique_ptr<Scenario>> GetScenarios() {
    std::vector<std::unique_ptr<Scenario>> scenarios;

    scenarios.push_back(std::make_unique<scenarios::HardwareConcurrency>());
    scenarios.push_back(std::make_unique<scenarios::DetachJoin>());
    scenarios.push_back(std::make_unique<scenarios::ThreadLocal>());
    scenarios.push_back(std::make_unique<scenarios::Locks>());
    scenarios.push_back(std::make_unique<scenarios::RecursiveMutex>());
    scenarios.push_back(std::make_unique<scenarios::UniqueLock>());
    scenarios.push_back(std::make_unique<scenarios::SharedMutex>());
    scenarios.push_back(std::make_unique<scenarios::ConditionVariable>());

    return scenarios;
}

}  // namespace sandbox::threading {
