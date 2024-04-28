#ifndef ROBOT_H
#define ROBOT_H

#include <cstdint>
#include <raylib.h>

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

class Robot {
public:
    Vector2 position, speed;
    float radius, radiansAngle;
    Color color;

    Robot(Vector2 position, float degreeAngle = 0.0f, float radius = 20.0f, Color color = DARKGREEN);

    int readGyron();
    int readSensor(int sensorAddress);

    void rotate(float angle);
    void motor(int leftDirection, uint8_t leftSpeed, int rightDirection, uint8_t rightSpeed);

    void update();
    void render();
};

#endif
