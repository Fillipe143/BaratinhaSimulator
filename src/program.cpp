#include "arduino/baratinha.h"
#include "arduino/core.h"
#include <string>

void setup() {
}

void loop() {
    int left = readSensor(SENSOR_LEFT);
    int right = readSensor(SENSOR_RIGHT);

    Serial::print("Left: " + std::to_string(left));
    Serial::println(" Right: " + std::to_string(right));

    // Turn to side furthest from the wall
    int maxDist = left > right ? left : right;
    motor(GO_FORWARD, 100.0 * maxDist / left, GO_FORWARD, 100.0 * maxDist / right);
}
