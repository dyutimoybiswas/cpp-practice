/**
 * @file binary_semaphore.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * Signals other threads after execution.
 * semaphore::acquire decrements internal counter by 1. blocks calling thread if counter is 0.
 * semaphore::release increments internal counter by specified value (1 for binary semaphore). threads waiting on value of counter will be unblocked
 * If zero, semaphore is blocked.
 * @version 0.1
 * @date 2024-11-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <chrono>
#include <semaphore>
#include <thread>

std::binary_semaphore main2thread{0}, thread2main{0};

void proc() {
    main2thread.acquire();
    std::cout << "thread got the signal" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "thread sent the signal" << std::endl;
    thread2main.release();
}

int main(int argc, char const *argv[])
{
    std::thread t(proc);

    main2thread.release();
    thread2main.acquire();

    std::cout << "main got the signal" << std::endl;

    t.join();
    return 0;
}
