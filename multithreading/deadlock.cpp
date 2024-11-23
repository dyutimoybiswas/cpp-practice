/**
 * @file deadlock.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * predict deadlock in below scenarios.
 * @version 0.1
 * @date 2024-11-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex m1, m2;

void thread1() {
    m1.lock();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    m2.lock();  // locked by other thread, doesn't proceed further
    std::cout << "Critical section - thread1" << std::endl;
    m1.unlock();
    m2.unlock();
}

void thread2() {
    m2.lock();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    m1.lock();  // locked by other thread, doesn't proceed further
    std::cout << "Critical section - thread2" << std::endl;
    m2.unlock();
    m1.unlock();
}

int main(int argc, char const *argv[])
{
    // NOT a deadlock if mutex locking order is same in both cases.
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();
    return 0;
}
