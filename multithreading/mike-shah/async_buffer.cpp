/**
 * @file async_buffer.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * Load resources aynchronously (buffering) e.g. progress indicator.
 * 
 * @version 0.1
 * @date 2024-12-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <thread>
#include <iostream>
#include <chrono>
#include <future>

bool bufferedFileLoader() {
    size_t bytesLoaded {0};
    while (bytesLoaded < 20000) {
        std::cout << "Simulating task.." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        bytesLoaded += 1000;
    }
    return true;
}

int main(int argc, char const *argv[])
{
    std::future<bool> backgroundThread = std::async(std::launch::async, bufferedFileLoader);
    std::future_status status;      // specified by return value of wait_for/wait_until

    while (true) {
        std::cout << "Main thread running..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        status = backgroundThread.wait_for(std::chrono::milliseconds(1));   // waits for result *for* the specified duration
        if (status == std::future_status::ready) {
            std::cout << "Data is ready." << std::endl;
            break;
        }
    }

    return 0;
}
