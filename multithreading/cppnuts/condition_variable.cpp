/**
 * @file condition_variable.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * used to 1. notify other threads 2. wait for some conditions
 * notified using notify_one() / notify_all()
 * wait, wait_for, wait_until are used to wait
 * Checking for mutex lock consumes CPU cycles. cv.wait() only executes if variant(s) of notify() is called.
 * @version 0.1
 * @date 2024-11-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::condition_variable cv;
std::mutex m;
long balance {0};

void addMoney(int money) {
    std::lock_guard<std::mutex> lock(m);
    balance += money;
    std::cout << "Amount added. Current balance = " << balance << std::endl;
    cv.notify_one();        // notifies other thread (withdrawMoney) where unique_lock locks mutex
}

void withdrawMoney(int money) {
    std::unique_lock<std::mutex> lock(m);
    cv.wait(lock, []() -> bool { return balance != 0; });   // wait (thread sleeps) till predicate returns true. mutex is unlocked while waiting (since unique_lock)
    if (balance >= money) {
        balance -= money;
        std::cout << "Amount deducted = " << money << std::endl;
    } else {
        std::cout << "Cannot withdraw, not enough funds." << std::endl;
    }
    std::cout << "Current balance = " << balance << std::endl;
}

int main(int argc, char const *argv[])
{
    std::thread t1(withdrawMoney, 300);
    std::thread t2(addMoney, 500);

    t1.join();
    t2.join();
    return 0;
}
