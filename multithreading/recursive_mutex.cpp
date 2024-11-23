/**
 * @file recursive_mutex.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * used in context of recursive functions. same thread can lock a mutex multiple times.
 * @version 0.1
 * @date 2024-11-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <thread>
#include <mutex>

std::recursive_mutex rm;
int buffer {0};

void recursion(char ch, int calledFor) {
    if (calledFor < 0)
        return;

    rm.lock();
    std::cout << ch << " " << buffer++ << std::endl;
    recursion(ch, --calledFor);
    rm.unlock();
    std::cout << "Unlocked by thread - " << ch << std::endl;    // printed for 10 (calledFor) times per thread
}

int main(int argc, char const *argv[])
{
    // both run for 10 calls, one after another.
    std::thread t1(recursion, 'a', 10);
    std::thread t2(recursion, 'b', 10);

    t1.join();
    t2.join();

    // loop demo.
    for (int i = 0; i < 5; ++i) {
        rm.lock();
        std::cout << "locked " << i << std::endl;
    }
    for (int i = 0; i < 5; ++i) {
        rm.unlock();
        std::cout << "unlocked " << i << std::endl;
    }

    return 0;
}

