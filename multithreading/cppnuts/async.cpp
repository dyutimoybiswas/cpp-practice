/**
 * @file async.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * std::async runs a function asynchronously and returns std::future object that holds the result
 * launch policies for a task - std::launch::async, std::launch::deferred or a combination of these (or-ed)
 * std::async creates/picks a thread, passes a promise object and returns associated future object
 * functions, functors and lambdas can all be passed with std::async
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

long int findOdd(long int start, long int end, std::thread::id callingId) {
    long int oddSum {0};

    // thread IDs are same for deferred call and different for async call.
    std::cout << "This ID is " << (callingId == std::this_thread::get_id() ? "same as " : "different than ") << "calling ID." << std::endl;

    for (long int i = start; i < end; ++i)
        if (i & 1U)
            oddSum += i;

    return oddSum;
}

int main(int argc, char const *argv[])
{
    long int start = 0, end = 1900000000U;
    
    // findOdd executed only when get() is called on future, else an indicative statement.
    // std::future<long int>oddSum = std::async(std::launch::deferred, findOdd, start, end, std::this_thread::get_id());
    std::future<long int>oddSum = std::async(std::launch::async, findOdd, start, end, std::this_thread::get_id());      // thread created and executed normally

    std::cout << "Waiting for result..." << std::endl;
    std::cout << "Odd sum = " << oddSum.get() << std::endl;  // thread created and findOdd executed

    std::cout << "Done." << std::endl;
    return 0;
}
