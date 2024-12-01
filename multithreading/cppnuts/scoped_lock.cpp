/**
 * @file scoped_lock.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * std::scoped_lock is available in C++17 and above. syn - std::scoped_lock l(lockable_object1, ...)
 * controls ownership in scope, released in destructor.
 * acquires and locks at definition, locking cannot be deferred or time-bound (difference with unique_lock)
 * never faces deadlock
 * @version 0.1
 * @date 2024-11-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <thread>
#include <iostream>
#include <mutex>

std::mutex m1, m2;

void processData(int id) {
    std::scoped_lock sl(m1, m2);
    std::cout << "Thread " << id << " processing data..." << std::endl;
}

int main(int argc, char const *argv[])
{
    constexpr int numThreads {40};
    std::thread threads[numThreads] ;

    for (int i {0}; i < numThreads; ++i)
        threads[i] = std::thread(processData, i);

    for (int i {0}; i < numThreads; ++i)
        threads[i].join();

    return 0;
}
