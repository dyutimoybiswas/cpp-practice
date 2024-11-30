/**
 * @file producer_consumer_semaphore.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * implement producer-consumer using binary semaphore
 * @version 0.1
 * @date 2024-11-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <chrono>
#include <semaphore>
#include <thread>

std::binary_semaphore signal2producer{1}, signal2consumer{0};
int buff[5];

void producer() {
    while (true) {
        signal2producer.acquire();
        std::cout << "Produced - ";
        for (int i = 0; i < 5; ++i) {
            buff[i] = i * i;
            std::cout << buff[i] << " ";
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        std::cout << std::endl;
        signal2consumer.release();
    }
}

void consumer() {
    while (true) {
        signal2consumer.acquire();
        std::cout << "Consumed - ";
        for (int i = 4; i >= 0; --i) {
            std::cout << buff[i] << " ";
            buff[i] = 0;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        std::cout << std::endl;
        signal2producer.release();
    }
}

int main(int argc, char const *argv[])
{
    std::thread p(producer);
    std::thread c(consumer);
    p.join();
    c.join();
    return 0;
}


