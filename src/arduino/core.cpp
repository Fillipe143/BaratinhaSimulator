#include "core.h"
#include "main.h"
#include <chrono>
#include <iostream>
#include <string>

auto start = std::chrono::steady_clock::now();

void Serial::print(std::string text) {
    std::cout << text;
}

void Serial::println(std::string text) {
    std::cout << text << std::endl;
}

long millis() {
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
    return ms.count();
}

void delay(long millis) {
    onDelayCalled(millis);
}
