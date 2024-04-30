#pragma once

#include <list>
#include <fmt/format.h>
#include <mutex>
#include <stdexcept>

#include <boost/coroutine2/all.hpp>

#include "task.hpp"

class CoroPool {
public:
    using Coroutine = typename boost::coroutines2::coroutine<Task*>::push_type;
    using TaskPipe = typename boost::coroutines2::coroutine<Task*>::pull_type;

public:
    CoroPool(std::size_t max_size)
        : max_size_{max_size}
        , total_coroutines_{0} {
    }

    std::unique_ptr<Coroutine> Take() {
        std::lock_guard<std::mutex> lock(mutex_);
        std::unique_ptr<Coroutine> coroutine;
        if (!free_.empty()) {
            coroutine = std::move(free_.front());
            free_.pop_front();
        } else {
            coroutine = std::make_unique<Coroutine>([](TaskPipe& pipe){
                for (auto* task : pipe) {
                    task->Attach(&pipe);
                    task->Perform();
                }
            });
            ++total_coroutines_;
        }
        return coroutine;
    }

    void Return(std::unique_ptr<Coroutine>&& coroutine) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (total_coroutines_ < max_size_) {
            free_.push_back(std::move(coroutine));
        }
    }

private:
    std::size_t max_size_;

    std::mutex mutex_;
    std::list<std::unique_ptr<Coroutine>> free_;
    std::size_t total_coroutines_;
};
