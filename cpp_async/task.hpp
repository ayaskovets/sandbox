#pragma once

#include <boost/coroutine2/all.hpp>

#include "task.hpp"

enum class Status {
    kNew,
    kSuspended,
    kDone
};

class Task {
    using Function = std::function<void(Task*)>;
    using Coroutine = typename boost::coroutines2::coroutine<Task*>::push_type;
    using TaskPipe = typename boost::coroutines2::coroutine<Task*>::pull_type;

public:
    Task(Function&& f)
    : f_{std::move(f)} {
        status_ = Status::kNew;
    }

    void Attach(std::unique_ptr<Coroutine>&& coroutine) {
        coroutine_ = std::move(coroutine);
    }

    void Attach(TaskPipe* task_pipe) {
        task_pipe_ = task_pipe;
    }

    void Perform() {
        f_(this);
        status_ = Status::kDone;
    }

    void Yield() {
        (*task_pipe_)();
        status_ = Status::kSuspended;
    }

    Status GetStatus() {
        return status_;
    }

    void DoStep() {
        (*coroutine_)(this);
    }

private:
    Function f_;
    TaskPipe* task_pipe_;
    std::unique_ptr<Coroutine> coroutine_;
    Status status_;
};
