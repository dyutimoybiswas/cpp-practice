/**
 * @file mutex_try_lock.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * mutex::try_lock() is a non-blocking version of mutex::lock(). Returns true/false based on if locking was successful.
 * calling try_lock() more than once by same mutex in same thread results in deadlock.
 * @version 0.1
 * @date 2024-11-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <thread>
#include <mutex>

#define N 100000U

int counter {0};
std::mutex m;

void increaseCounter() {
    for (int i = 0; i < N; ++i) {
        if (m.try_lock()) {
            ++counter;
            m.unlock();
        }
    }
}

int main(int argc, char const *argv[])
{
    std::thread t1(increaseCounter);
    std::thread t2(increaseCounter);

    if (t1.joinable())
        t1.join();

    if (t2.joinable())
        t2.join();
        
    std::cout << "final counter value = " << counter << std::endl;  // <= 2 * N
    return 0;
}
