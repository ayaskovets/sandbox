#include <iostream>

#include "coro_pool.hpp"
#include "thread_pool.hpp"

void Run(ThreadPool& thread_pool, CoroPool& coro_pool, Task* task) {
    auto coro = coro_pool.Take();
    task->Attach(std::move(coro));
    thread_pool.Schedule(task);
}

int main(int argc, char* argv[]) {
    CoroPool coro_pool(12);
    ThreadPool thread_pool(2);

    Task task1([](Task* task){
        for (std::size_t i = 0; i < 10; ++i) {
            std::cout << "hello from handler(1): " << i << std::endl;
            task->Yield();
        }
    });

    Task task2([](Task* task){
        for (std::size_t i = 0; i < 10; ++i) {
            std::cout << "hello from handler(2): " << i << std::endl;
            task->Yield();
        }
    });

    Task task3([](Task* task){
        for (std::size_t i = 0; i < 10; ++i) {
            std::cout << "hello from handler(3): " << i << std::endl;
            task->Yield();
        }
    });

    Run(thread_pool, coro_pool, &task1);
    Run(thread_pool, coro_pool, &task2);
    Run(thread_pool, coro_pool, &task3);

    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 0;
}
