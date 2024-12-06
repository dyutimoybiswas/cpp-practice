/**
 * @file jthread.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * Demonstrates how to create jthread (joinable threads). Introduced since C++20.
 * Joins automatically at destruction.
 * @version 0.1
 * @date 2024-12-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <thread>
#include <iostream>
#include <vector>
#include <mutex>

std::mutex m;

int main(int argc, char const *argv[])
{
    auto someTask = [] (int x) {
        m.lock();
        std::cout << "Executing thread ID: " << std::this_thread::get_id() << ", arg passed = " << x << std::endl;
        m.unlock();
    };

    std::vector<std::jthread> jthreads;

    for (size_t i {0}; i < 5; ++i)
        jthreads.emplace_back(someTask, i + 1);

    return 0;
}
