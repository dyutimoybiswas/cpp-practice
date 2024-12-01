/**
 * @file object_pool.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * Demonstrate object pooling.
 * Fixed number of objects handle resources. Worker threads execute tasks via these objects.
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
#include <string>
#include <sstream>
#include <memory>

std::string getThreadId() {
    auto id = std::this_thread::get_id();
    std::stringstream ss;
    ss << id;
    return ss.str();
}

// object to be reused by threads.
class Object {
    public:
        size_t num;
        Object(size_t n): num(n) {}
};

// manages object availability.
class ObjectPool {
    public:
        ObjectPool(size_t);
        std::shared_ptr<Object> acquireObject();        // fetches object if available
        void releaseObject(std::shared_ptr<Object>);    // returns object to pool for reuse

    private:
        std::queue<std::shared_ptr<Object>> pool;
        size_t poolSize;
        std::mutex m;
};

ObjectPool::ObjectPool(size_t size): poolSize(size) {
    for (size_t i {0}; i < poolSize; ++i) {
        std::cout << "Object " << i << std::endl;
        pool.push(std::make_shared<Object>(Object(i)));
    }
}

std::shared_ptr<Object> ObjectPool::acquireObject() {
    std::unique_lock<std::mutex> lock(m);
    std::shared_ptr<Object> obj;
    if (!pool.empty()) {
        obj = pool.front();
        printf("Thread %s acquired object = %d.\n", getThreadId().c_str(), obj->num);
        pool.pop();
    }
    return obj;
}

void ObjectPool::releaseObject(std::shared_ptr<Object> obj) {
    std::unique_lock<std::mutex> lock(m);
    printf("Thread %s released object = %d.\n", getThreadId().c_str(), obj->num);
    pool.push(obj);
}

void worker(ObjectPool& pool) {
    for (size_t i {0}; i < 15; ++i) {
        auto obj = pool.acquireObject();
        if (obj) {
            std::this_thread::sleep_for(std::chrono::milliseconds(600));    // simulate task
            pool.releaseObject(obj);
        } else {
            printf("Thread %s failed to acquire object.\n", getThreadId().c_str());     // since workers != objects, some workers may fail to acquire.
        }
    }
}

int main(int argc, char const *argv[])
{
    ObjectPool p(3);        // creates 3 objects and stores them in pool.
    std::vector<std::thread> workers;

    for (size_t i {0}; i < 5; ++i)      // create 5 worker threads
        workers.emplace_back(worker, std::ref(p));      // each worker acquires object, simulates task and releases object

    for (size_t i {0}; i < 5; ++i)
        workers[i].join();

    return 0;
}
