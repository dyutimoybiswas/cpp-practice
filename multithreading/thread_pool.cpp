/**
 * @file thread_pool.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * Specify number (pool) of threads to execute at the same time.
 * Note: always execute task in non-blocking manner.
 * Workers are created and all wait on condition variable.
 * Tasks are then enqueued sequentially.
 * Every enqueue notifies all workers, each of which dequeues a task randomly and executes it.
 * 
 * @version 0.1
 * @date 2024-11-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <functional>
#include <sstream>

class ThreadPool {
    public:
        ThreadPool(size_t);

        template <class F>
        void enqueue(F&& task) {
            std::unique_lock<std::mutex> lock(queueMutex);  // owns and locks mutex.
            tasks.emplace(std::forward<F>(task));           // add this to tasks
            lock.unlock();
            condition.notify_all();         // notifies cv.wait in constructor threads
        }

        ~ThreadPool();

    private:
        std::vector<std::thread> workers;
        std::queue<std::function<void()>> tasks;
        bool stop;
        std::condition_variable condition;
        std::mutex queueMutex;
};

ThreadPool::ThreadPool(size_t numWorkers): stop(false) {
    for (size_t i {0}; i < numWorkers; ++i) {
        
        workers.emplace_back([this]() {     // numWorkers number of threads are generated

            while (true) {      // ensures other tasks can be retrieved. Without this, only 5 tasks are executed.
                std::unique_lock<std::mutex> lock(this->queueMutex);
                this->condition.wait(lock, [this]() { return this->stop || !this->tasks.empty(); });    // release lock temporarily
                if (this->stop && this->tasks.empty())
                    return;
                auto task = std::move(this->tasks.front());     // after enqueue, tasks is not empty. task here contains thread number, printf message & delay
                this->tasks.pop();
                lock.unlock();      // releases lock. tasks is empty again.
                task();             // run (execute) task contents. If run before unlocking (blocking execution), 2s delay is observed per task
            }
        });
    }
}

// set stop flag to indicate end of execution, notify all waiting threads and join them.
ThreadPool::~ThreadPool() {
    stop = true;
    condition.notify_all();
    for (std::thread& worker: workers)
        worker.join();
}

std::string getThreadId() {
    auto id = std::this_thread::get_id();
    std::stringstream ss;
    ss << id;
    return ss.str();
}

int main(int argc, char const *argv[])
{
    ThreadPool pool(5);     // 5 worker threads, so 5 threads run at a time

    std::cout << "Pool created." << std::endl;

    for (size_t i {0}; i < 22; ++i)
        pool.enqueue([i]() {
            printf("Task %d %s executed by thread.\n", i, getThreadId().c_str());
            std::this_thread::sleep_for(std::chrono::seconds(2));    // this delay is overlapped in concurrent execution, hence 2s delay is observed instead of 10s
        });

    return 0;
}
