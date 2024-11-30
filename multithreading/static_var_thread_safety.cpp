/**
 * @file static_var_thread_safety.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * Checks thread safety of static variables
 * @version 0.1
 * @date 2024-11-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <thread>
#include <mutex>

static int s {0};
std::mutex m;

void fun() {
    m.lock();
    for (int count {100000}; count > 0; --count)
        ++s;
    m.unlock();
    std::cout << s << std::endl;    // when not using mutex, possible to get incorrect ans since static s is shared between threads
}

int main(int argc, char const *argv[])
{
    std::thread t1(fun);
    std::thread t2(fun);

    t1.join();
    t2.join();
    return 0;
}
