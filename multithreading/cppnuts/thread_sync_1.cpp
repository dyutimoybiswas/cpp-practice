/**
 * @file thread_sync_1.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * synchronize threads wrt accessing critical section (section of a program accessed by threads)
 * critical section(s) should be accessed by one thread at a time to avoid anomalous results
 * @version 0.1
 * @date 2024-11-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <thread>
#include <mutex>
#include <iostream>

long long balance {0};
std::mutex m;

void addMoney(long long val) {
    m.lock();
    balance += val;     // critical section
    m.unlock();
}

int main(int argc, char const *argv[])
{
    std::thread t1(addMoney, 100);
    std::thread t2(addMoney, 200);

    t1.join();
    t2.join();

    std::cout << "final balance = " << balance << std::endl;
    return 0;
}

