/**
 * @file lock.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * std::lock() can lock multiple mutexes in random order.
 * case 1 - no deadlock: std::lock(m1, m2) on both threads
 * case 2 - no deadlock: std::lock(m1, m2) & std::lock(m2, m1)
 * case 3 - no deadlock: std::lock(m1, m2, m3, m4) on one thread and std::lock(m3, m4) & std::lock(m1, m2) on another
 * case 4 - possible deadlock: std::lock(m1, m2) & std::lock(m3, m4) on one thread and std::lock(m3, m4) & std::lock(m1, m2) on another
 * @version 0.1
 * @date 2024-11-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <thread>
#include <mutex>
#include <iostream>

std::mutex m1, m2;

// case 2 demo

void foo() {
    for (int i = 0; i < 10; ++i) {
        std::lock(m1, m2);
        std::cout << "foo" << std::endl;
        m1.unlock();
        m2.unlock();
    }
}

void bar() {
    for (int i = 0; i < 10; ++i) {
        std::lock(m2, m1);
        std::cout << "bar" << std::endl;
        m2.unlock();
        m1.unlock();
    }
}

int main(int argc, char const *argv[])
{
    // executes parallely.
    std::thread t1(foo);
    std::thread t2(bar);

    t1.join();
    t2.join();
    return 0;
}
