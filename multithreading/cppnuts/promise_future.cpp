/**
 * @file promise_future.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * std::promise is used to set values/exceptions
 * std::future waits for the promise, checks with promise if a value is available and if so, gets the value 
 * @version 0.1
 * @date 2024-11-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <thread>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <future>

void findOdd(std::promise<long int>&& oddSumPromise, long int start, long int end) {
    long int oddSum {0};
    for (long int i = start; i < end; ++i)
        if (i & 1U)
            oddSum += i;
    oddSumPromise.set_value(oddSum);
}

int main(int argc, char const *argv[])
{
    long int start = 0, end = 1900000000U;
    
    std::promise<long int>oddSum;
    std::future<long int>oddFuture = oddSum.get_future();   // link future

    std::cout << "Thread created." << std::endl;
    std::thread t(findOdd, std::move(oddSum), start, end);  // can also use std::ref(oddSum) to pass by lvalue reference, more common according to ChatGPT

    std::cout << "Waiting for result..." << std::endl;
    std::cout << "Odd sum = " << oddFuture.get() << std::endl;  // get the value set by promise.

    std::cout << "Done." << std::endl;
    t.join();
    return 0;
}
