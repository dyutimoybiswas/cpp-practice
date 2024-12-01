/**
 * @file join_detach.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * thread.join() waits for thread to finish before joining with parent thread.
 * joinable() can be used to check if a thread can be joined, as joining a thread more than once causes program termination.
 * thread.detach() is used to detach it from parent thread.
 * check is thread is joinable before detaching, else detaching multiple times results in program termination.
 * either join or detach must be used else program terminates.
 * @version 0.1
 * @date 2024-11-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <thread>
#include <chrono>
#include <iostream>

void run(int count) {
    while (count--)
        std::cout << "Run called." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3)); // if this is omitted, 'Run called.' might get printed.
}

int main(int argc, char const *argv[])
{
    std::thread t1(run, 10);

    if (t1.joinable())
        t1.detach();    // main thread no longer waits for t1 to join.
    // t1.detach();    // error

    // if (t1.joinable())
    //     t1.join();
    // t1.join();  // error

    std::cout << "main()" << std::endl;     // doesn't print until t1 joins.


    return 0;
}
