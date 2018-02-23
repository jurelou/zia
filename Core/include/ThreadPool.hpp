//
// Created by marmus_a on 31/01/18.
//

#ifndef CPP_ZIA_THREADPOOL_HPP
#define CPP_ZIA_THREADPOOL_HPP


#include <thread>
#include <vector>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>

class ThreadPool {
public:
    using Task = std::function<void()>;

    ThreadPool(int nbThread);
    ~ThreadPool();
    bool                                runAsync(Task task);
private:
    std::vector<std::thread>            workers;
    std::queue<Task>                    tasks;
    std::mutex                          mutex;
    std::condition_variable             condition;
    bool                                stop;
};


#endif //CPP_ZIA_THREADPOOL_HPP
