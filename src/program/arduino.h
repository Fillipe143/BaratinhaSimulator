#ifndef ARDUINO_H
#define ARDUINO_H

#include <cstdint>
#include <iostream>
#include <string>

#define GO_FORWARD 1
#define GO_BACK 0

#define SENSOR_FRONT 1
#define SENSOR_RIGHT 2
#define SENSOR_LEFT 3
#define SENSOR_BACK_RIGHT 4
#define SENSOR_FRONT_LEFT 5
#define SENSOR_BACK_LEFT 6
#define SENSOR_FRONT_RIGHT 7
#define SENSOR_BACK 8

#define Serial ArduinoSerial {}
#define String(s) (std::to_string(s))

typedef std::string String;


class ArduinoSerial {
public:
    void print(String s) {
        std::cout << s;
    }

    void println(String s) {
        std::cout << s << std::endl;
    }
};

void setup();
void loop();

long map(long x, long in_min, long in_max, long out_min, long out_max);
void delay(unsigned long millis);
unsigned long millis();

int readAngle();
int readSensor(int sensor);
void motor(bool leftDirection, uint8_t leftSpeed, bool rightDirection, uint8_t rightSpeed);
#endif

