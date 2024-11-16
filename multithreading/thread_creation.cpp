/**
 * @file thread_creation.cpp
 * @author Dyutimoy Biswas
 * @brief 
 * Demonstrates ways to create threads (5) - func ptr, lambda expr, callable class(functor?), static and non-static member functions
 * Threads may not execute in the same order in which they are created.
 * @version 0.1
 * @date 2024-11-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <thread>
#include <iostream>

void foo(int val) {
    while (val--)
        std::cout << val << std::endl;
}

class Baz {
    public:
        void operator()(int val) {
            while (0 <= val && val < 30)
                std::cout << val++ << std::endl;
        }
};

class Base {
    public:
        static void run(int val) {
            while (val && val <= 20)
                std::cout << val-- << std::endl;
        }
        void bam(int val) {
            while (val && val <= 20)
                std::cout << val++ << std::endl;
        }
};

int main(int argc, char const *argv[])
{
    // using function call.
    std::thread t1(foo, 10);
    std::thread t2(foo, 21);
    std::thread t3(foo, 32);
    
    // executes in random order (run multiple times to verify)
    t1.join();
    t2.join();
    t3.join();

    auto bar = [](int val) -> void {
        while (val++ < 40)
            std::cout << val << std::endl;
    };

    // using lambda expression.
    std::thread t4(bar, 25);    // can also write lambda expression instead of bar.
    std::thread t5(bar, 36);

    t4.join();
    t5.join();

    // using callable class.
    Baz b;
    std::thread t6(b, 16);
    std::thread t7(b, 4);

    t6.join();
    t7.join();

    // using static function.
    std::thread t8(Base::run, 12);

    t8.join();

    // using non-static function.
    Base obj;
    std::thread t9(&Base::bam, &obj, 6);

    t9.join();

    return 0;
}
