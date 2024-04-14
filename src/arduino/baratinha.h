#ifndef BARATINHA_H
#define BARATINHA_H
#include <cstdint>

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

unsigned int readSensor(int sensor);
void motor(bool leftDirection, uint8_t leftSpeed, bool rightDirection, uint8_t rightSpeed);

#endif
