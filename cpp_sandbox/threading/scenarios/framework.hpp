#pragma once

#include <future>
#include <mutex>
#include <string>
#include <thread>
#include <shared_mutex>
#include <condition_variable>

#include <fmt/core.h>

#define SCENARIO(name, description)            \
class name : public Scenario {                 \
public:                                        \
    name() : Scenario(description) {}          \
protected:                                     \
    void Run() override;                       \
};                                             \
void name::Run()                               \

namespace sandbox::threading {

class Scenario {
protected:
    virtual void Run() = 0;

    template<typename ... Args>
    void MLog(const char* pattern, Args&&... args) {
        const std::lock_guard lock(log_mutex_);
        Log(pattern, std::move(args)...);
    }

    template<typename ... Args>
    void Log(const char* pattern, Args&&... args) {
        if (log_.empty()) {
            log_ += "{";
        }
        log_ += "\n    ";
        log_ += fmt::format(pattern, args...);
    }

public:
    std::string_view GetDescription() const {
        return description_;
    };

    std::string GetResult() {
        Run();
        return log_ + "\n}";
    };

    Scenario(std::string_view description) : description_{description} {}
    virtual ~Scenario() = default;

private:
    Scenario() = delete;
    Scenario(const Scenario&) = delete;
    Scenario(Scenario&&) = delete;
    Scenario& operator=(const Scenario&) = delete;
    Scenario& operator=(Scenario&&) = delete;

    std::string_view description_;
    std::string log_;
    std::mutex log_mutex_;
};

}  // namespace sandbox::threading
