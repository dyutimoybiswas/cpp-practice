#include <iostream>

int main(void) {
    // Excercise 1.2
    #ifdef EX1_2
    return -1; // prints 255
    #endif

    // Excercise 1.3
    std::cout << "Hello, World!" << std::endl;

    // Excercise 1.4
    int a = 0, b = 0;
    std::cin >> a >> b;
    std::cout << "The product of " << a
    << " and " <<b
    << " is " << a*b << std::endl;

    // Excercise 1.9
    int sum = 0, m = 50;
    while (m <= 100) {
        sum += m;
        m++;
    }
    std::cout << "Sum of numbers from 50 to 100 is " << sum << std::endl;

    // Excercise 1.10
    int n = 10;
    while (n >= 0) {
        std::cout << n << " ";
        n--;
    }
    std::cout << std::endl;

    // Excercise 1.12
    sum = 0;
    for (int i = -100; i <= 100; ++i) sum += i;
    std::cout << sum << std::endl;  // 0

    // Excercise 1.16
    #ifdef EX1_16
    int x; sum = 0;
    while (std::cin >> x) {
        sum += x;
    }
    std::cout << sum << std::endl;
    #endif

    // Assignment can appear as a condition
    if (int x = 5) std::cout << "Always executes." << std::endl;

    // Print numbers as they are entered and calculate frequencies in real time.
    int value = 0, lastValue = 0;
    if (std::cin >> lastValue) {    // To ensure at least one value has been entered.
        int count = 1;
        while (std::cin >> value) {
            if (value == lastValue) {   // Value is repeated.
                count++;
            } else {    // Print value as well as its frequency.
                std::cout << "Value - " << lastValue << " occurs " << count << " times." << std::endl;
                lastValue = value;
                count = 1;
            }
        }
        // To print the last occurring value.
        std::cout << "Value - " << lastValue << " occurs " << count << " times." << std::endl;
    }

}
