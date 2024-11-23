/**
 * @file timed_mutex.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * timed_mutex::try_lock_for() is similar to mutex::try_lock(). 
 * timed_mutex::try_lock_until() waits until specified time.
 * Tries to lock mutex for specified duration passed as arg, or until mutex is locked successfully.
 * Returns true/false based on whether locking was successful.
 * @version 0.1
 * @date 2024-11-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

int amount = 0;
std::timed_mutex tm;

void increment(int i) {
    auto now = std::chrono::steady_clock::now();
    // if (tm.try_lock_for(std::chrono::seconds(1))) {
    if (tm.try_lock_until(now + std::chrono::seconds(1))) {     // equivalent
        ++amount;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Thread " << i << " entered." << std::endl;
        tm.unlock();
    } else {
        std::cout << "Thread " << i << " didn't enter." << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    // either of these threads will be locked, the other will execute.
    std::thread t1(increment, 1);
    std::thread t2(increment, 2);

    t1.join();
    t2.join();

    std::cout << "amount = " << amount << std::endl;

    return 0;
}
