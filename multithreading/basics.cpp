/**
 * @file basics.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * Every application contains a default thread (main()), other threads can be created
 * from within this function.
 * Thread can also be considered as a lightweight process.
 * Common examples are - browser tabs, VSCode editor and autocomplete, etc.
 * Optimization level 3 (-O3) is needed for best results.
 * Optimization is done to reduce compile time and debuggability (debugging introduces additional checks)
 * @version 0.1
 * @date 2024-11-16
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <chrono>
#include <thread>

typedef unsigned long long ull;

void OddCount(ull, ull);
void EvenCount(ull, ull);
ull oddsCount {0}, evensCount {0};

int main(int argc, char const *argv[])
{
    ull start = 0, end = 1900000000;

    auto startTime = std::chrono::high_resolution_clock::now();

    std::thread t1(OddCount, start, end);
    std::thread t2(EvenCount, start, end);

    t1.join();
    t2.join();

    // OddCount(start, end);
    // EvenCount(start, end);

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);

    std::cout << "odds = " << oddsCount << std::endl;
    std::cout << "evens = " << evensCount << std::endl;
    std::cout << "Time taken = " << duration.count() << " seconds" << std::endl;

    return 0;
}

void OddCount(ull start, ull end) {
    oddsCount = 0;

    for (ull num = start; num != end; ++num)
        if (num & 1U)
            ++oddsCount;
}

void EvenCount(ull start, ull end) {
    evensCount = 0;

    for (ull num = start; num != end; ++num)
        if (!(num & 1U))
            ++evensCount;
}
