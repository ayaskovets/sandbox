#include <iostream>

#include "scenarios.hpp"

int main(int argc, char* argv[]) {
    auto scenarios = sandbox::threading::GetScenarios();

    for (auto& scenario : scenarios) {
        std::cout << "[" << scenario->GetDescription() << "]: " << std::flush;
        std::cout << scenario->GetResult() << std::endl;
    }

    return 0;
}
