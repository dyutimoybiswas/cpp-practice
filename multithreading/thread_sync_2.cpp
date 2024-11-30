/**
 * @file thread_sync_2.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * problem: given a string, number of characters (N) and number of threads (T),
 * use T threads to print N characters at a time without overlap, in cyclic way.
 * @version 0.1
 * @date 2024-11-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <chrono> // For delay

class MyPrinter {
public:
    MyPrinter(const std::string& s, size_t chars, size_t threads)
        : str(s), charCount(chars), threadCount(threads), allowedThread(0), nextChar(0) {}

    void run();

private:
    void printThread(size_t threadIndex);

    std::string str;
    size_t charCount;
    size_t threadCount;
    std::vector<std::thread> threads;
    std::mutex m;
    std::condition_variable cv;
    size_t allowedThread;
    size_t nextChar;
};

void MyPrinter::run() {
    for (size_t i = 0; i < threadCount; ++i) {
        threads.emplace_back(&MyPrinter::printThread, this, i);
    }

    for (auto& t : threads) {
        t.join();
    }
}

void MyPrinter::printThread(size_t threadIndex) {
    while (true) {
        std::unique_lock<std::mutex> ul(m);

        // Wait until it's this thread's turn
        cv.wait(ul, [this, threadIndex]() { return allowedThread == threadIndex; });

        // Print `charCount` characters starting from `nextChar`
        std::cout << "Thread " << threadIndex << ": ";
        size_t printCount = 0;

        for (size_t i = 0; printCount < charCount; ++i, ++printCount) {
            size_t charIndex = (nextChar + i) % str.length(); // Wrap around the string
            std::cout << str[charIndex];
        }

        nextChar = (nextChar + charCount) % str.length(); // Update for the next cycle

        std::cout << std::endl;

        // Update the allowed thread for the next turn
        allowedThread = (allowedThread + 1) % threadCount;

        // Simulate real-time output with a delay
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        ul.unlock();
        cv.notify_all();
    }
}

int main(int argc, char const* argv[]) {
    if (argc != 4)
        throw std::logic_error("3 arguments needed - string, char count, and thread count");

    MyPrinter printer(argv[1], std::atoi(argv[2]), std::atoi(argv[3]));
    printer.run();

    return 0;
}
