/**
 * @file try_lock.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * std::try_lock() is similar to mutex::try_lock(). Tries to lock lockable objects (eg mutex) passed as args, in order.
 * Returns -1 if all objects could be locked, else object index (0-based) which could not be locked.
 * In case of unsuccessful locking, releases all objects locked previously.
 * @version 0.1
 * @date 2024-11-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <string>

int X {0}, Y {0};
std::mutex m1, m2;

void sleepForTime(size_t seconds) { std::this_thread::sleep_for(std::chrono::seconds(seconds)); }

void incrementVariable(int& var, std::mutex& m, const std::string& desc) {
    for (size_t i = 0; i < 5; ++i) {
        m.lock();
        ++var;
        std::cout << desc << var << std::endl;
        m.unlock();
        sleepForTime(1);
    }
}

void consume() {
    int useCount {5}, sum {0};
    while (useCount) {
        int lockResult = std::try_lock(m1, m2);
        if (lockResult == -1 && X && Y) {
            --useCount;
            sum += X + Y;
            X = Y = 0;
            std::cout << "sum = " << sum << std::endl;
        }
        m1.unlock();
        m2.unlock();
    }
}

int main(int argc, char const *argv[])
{
    std::thread t1(incrementVariable, std::ref(X), std::ref(m1), "X ");
    std::thread t2(incrementVariable, std::ref(Y), std::ref(m2), "Y ");
    std::thread t3(consume);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}

