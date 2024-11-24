/**
 * @file producer_consumer.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * producer is a thread that generates data, and consumer is a thread that utilizes this data
 * both use a common space (critical section), where producer stores generated data and consumer fetches data from this space
 * producer acquires mutex lock, stores the data, notifies consumer and unlocks mutex.
 * on getting notified, consumer acquires mutex lock, retrieves data, notifies producer and unlocks mutex
 * a program can have m producers and n consumers
 * @version 0.1
 * @date 2024-11-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <thread>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <deque>

std::mutex m;
std::condition_variable cv;
std::deque<int> buffer;
constexpr unsigned int MAX_BUFFER_SIZE {50};

void producer(int val) {
    while (val) {   // keeps adding till value is positive
        std::unique_lock<std::mutex> ul(m);
        cv.wait(ul, []() -> bool { return buffer.size() < MAX_BUFFER_SIZE; });  // waits if size exceeds predefined capacity, before producing
        
        buffer.push_back(val);      // "producing" value.

        std::cout << "Produced " << val-- << std::endl;
        ul.unlock();
        cv.notify_one();
    }
}

void consumer() {
    while (true) {      // checks for produced data at all times
        std::unique_lock<std::mutex> ul(m);
        cv.wait(ul, []() -> bool { return buffer.size() > 0; });    // waits until there is data to consume
        
        /*"consuming" value */
        int val = buffer.back();
        buffer.pop_back();

        std::cout << "Consumed " << val << std::endl;
        ul.unlock();
        cv.notify_one();
    }
}

int main(int argc, char const *argv[])
{
    // run parallely.
    // Note that producer can produce multiple times before consumer consumes one, and 
    // consumer can consume multiple times before producer produces one.
    std::thread prod(producer, 100);
    std::thread cons(consumer);

    prod.join();
    cons.join();    // doesn't join because of infinite loop

    return 0;
}
