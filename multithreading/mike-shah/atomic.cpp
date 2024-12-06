/**
 * @file atomic.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * std::atomic allows threads to access critical sections without worrying about race condition.
 * critical section variable(s) can be declared atomic.
 * Cannot be copied or moved.
 * @version 0.1
 * @date 2024-12-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <thread>
#include <iostream>
#include <vector>
#include <atomic>

std::atomic<int> sharedValue {0};

int main(int argc, char const *argv[])
{
    auto increment = [] () {
        ++sharedValue;
    };

    std::vector<std::thread> threads;
    for (size_t i {0}; i < 100; ++i)
        threads.emplace_back(increment);

    for (size_t i {0}; i < 100; ++i)
        threads[i].join();

    std::cout << "Value = " << sharedValue << std::endl;    // always prints 100

    return 0;
}

