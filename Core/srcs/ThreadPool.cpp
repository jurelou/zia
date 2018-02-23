//
// Created by marmus_a on 31/01/18.
//

#include <iostream>
#include "ThreadPool.hpp"

ThreadPool::ThreadPool(int nbThread) : stop(false) {
    for (auto cpt = 0; cpt < nbThread; cpt++) {
        this->workers.emplace_back([this]() {
            while (true) {
                Task task;
                {
                    std::unique_lock<std::mutex> lock(this->mutex);
                    this->condition.wait(lock, [this]() {
                        return (this->stop || !this->tasks.empty());
                    });
                    if (this->stop && this->tasks.empty()) {
                        return;
                    }
                    task = this->tasks.front();
                    this->tasks.pop();
                }
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(this->mutex);
        this->stop = true;
    }
    condition.notify_all();
    for (auto& thread : this->workers) {
        thread.join();
    }
}

bool ThreadPool::runAsync(ThreadPool::Task task) {
    {
        std::unique_lock<std::mutex> lock(this->mutex);
        if (this->stop) {
            std::cout << std::boolalpha << this->stop << std::noboolalpha << std::endl;
            return false;
        }
        this->tasks.emplace(task);
    }
    condition.notify_one();
    return (true);
}
