#ifndef CORE_H 
#define CORE_H
#include <string>
class Serial {
    public:
        static void print(std::string text);
        static void println(std::string text);
};

long millis();
void delay(long millis);
#endif
