#ifndef MAIN_H
#define MAIN_H

#include <cstdint>
void onDelayCalled(long millis);
void onMotorCalled(bool leftDirection, uint8_t leftSpeed, bool rightDirection, uint8_t rightSpeed);
unsigned int onReadSensorCalled(int sensor);
#endif
