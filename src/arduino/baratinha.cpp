#include <cstdint>
#include "../main.h"

unsigned int readSensor(int sensor) {
    return onReadSensorCalled(sensor);
}

void motor(bool leftDirection, uint8_t leftSpeed, bool rightDirection, uint8_t rightSpeed) {
    return onMotorCalled(leftDirection, leftSpeed, rightDirection, rightSpeed);
}
