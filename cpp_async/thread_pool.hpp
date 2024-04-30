#pragma once

#include <atomic>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>

#include "task.hpp"

class ThreadPool {
public:
    ThreadPool(std::size_t size) {
        threads_.reserve(size);
        for (std::size_t i = 0; i < size; ++i) {
            threads_.push_back(std::thread([this](){
                while (!cancel_.test(std::memory_order::acquire)) {
                    std::unique_lock<std::mutex> lock(mutex);
                    if (tasks_.empty()) {
                        lock.unlock();
                        std::this_thread::yield();
                        continue;
                    }
                    Task* task = tasks_.front();
                    tasks_.pop();
                    lock.unlock();
                    task->DoStep();
                    if (task->GetStatus() != Status::kDone) {
                        tasks_.push(task);
                    }
                }
            }));
        }
    }

    ~ThreadPool() {
        cancel_.test_and_set(std::memory_order::release);
        for (auto& thread : threads_) {
            thread.join();
        }
    }

    void Schedule(Task* task) {
        std::lock_guard<std::mutex> lock(mutex);
        tasks_.push(task);
    }

private:
    std::vector<std::thread> threads_;

    std::mutex mutex;
    std::queue<Task*> tasks_;
    std::atomic_flag cancel_ = ATOMIC_FLAG_INIT;
};