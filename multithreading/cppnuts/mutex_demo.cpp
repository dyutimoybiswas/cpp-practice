/**
 * @file mutex_demo.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * race cond - 2 or more threads try to modify common data at the same time.
 * data attempted to be modified is called critical section.
 * Mutex/lock/unlock used to avoid race condition
 * @version 0.1
 * @date 2024-11-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <thread>
#include <mutex>

int amount {0};
std::mutex m;

void modifyAmount() {
    m.lock();
    ++amount;
    std::cout << amount << std::endl;
    m.unlock();
}

int main(int argc, char const *argv[])
{
    // race - amount is getting modified by both threads.
    std::thread t1(modifyAmount);
    std::thread t2(modifyAmount);

    if (t1.joinable())
        t1.join();

    if (t2.joinable())
        t2.join();
        
    return 0;
}
