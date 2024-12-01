/**
 * @file lock_guard.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * std::lock_guard<mutex> lock(m) used as scoped mutex.
 * Locks mutex automatically on creation and unlocks when going out of scope.
 * Cannot be copied.
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
    std::lock_guard<std::mutex> lock(m1);
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
