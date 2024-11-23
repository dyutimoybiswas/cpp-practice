/**
 * @file unique_lock.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * similar to lock_guard. Options = defer_lock, try_to_lock, adopt_lock.
 * defer_lock does not acquire ownership of mutex.
 * try_to_lock tries to acquire ownership (non-blocking)
 * adopt_lock assumes calling thread already owns the mutex
 * unique_lock object can be used with mutex functions like try_lock_for, try_lock_until etc.
 * allows moving but not copying
 * @version 0.1
 * @date 2024-11-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <thread>
#include <mutex>
#include <string>

std::mutex m1;
int buffer {0};

void task(const std::string& threadNumber, int loopFor) {
    // std::unique_lock<std::mutex> lock(m1);      // same as std::lock_guard
    std::unique_lock<std::mutex> lock(m1, std::defer_lock);     // takes ownership of mutex but doesn't lock automatically.
    lock.lock();    // lock explicitly when using defer_lock
    for (int i = 0; i < loopFor; ++i) {
        buffer++;
        std::cout << threadNumber << " " << buffer << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    std::thread t1(task, "T1", 10);
    std::thread t2(task, "T2", 10);

    t1.join();
    t2.join();
    return 0;
}
