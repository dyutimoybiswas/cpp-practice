/**
 * @file multiple_threads.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * Demonstrates how to create multiple threads.
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

    std::vector<std::thread> threads;

    // this is wrong. same thread runs someTask and joins everytime.
    // for (size_t i {0}; i < 5; ++i) {
    //     threads.emplace_back(someTask, i + 1);
    //     threads[i].join();
    // }

    for (size_t i {0}; i < 5; ++i)
        threads.emplace_back(someTask, i + 1);

    for (size_t i {0}; i < 5; ++i)
        threads[i].join();

    return 0;
}
