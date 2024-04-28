#include "robot.h"
#include <cmath>
#include <raylib.h>

#define MAX_SPEED 100
#define MAX_ANGLE (2 * M_PIf)
#define ROTATION_CONST 0.01f

Robot::Robot(Vector2 position, float degreeAngle, float radius, Color color) {
    Robot::position = position;
    Robot::speed = Vector2 { 0.0f, 0.0f };

    Robot::radius = radius;
    Robot::radiansAngle = degreeAngle;

    Robot::color = color;
}

void Robot::motor(int leftDirection, uint8_t leftSpeed, int rightDirection, uint8_t rightSpeed) {
    Robot::speed.x = (leftDirection == GO_FORWARD ? 1 : -1) * (leftSpeed % 100);
    Robot::speed.y = (rightDirection == GO_FORWARD ? 1 : -1) * (rightDirection % 100);
}

void Robot::onUpdate() {
    // Update rotation based on speed
    float dirSpeed = (Robot::speed.x - Robot::speed.y) / MAX_SPEED;
    float rotationForce = dirSpeed *  ROTATION_CONST;
    Robot::radiansAngle = fmodf(radiansAngle + rotationForce, MAX_ANGLE);
    if (Robot::radiansAngle < 0) Robot::radiansAngle += MAX_ANGLE;

    // Update position based on speed
    float resultSpeed = (Robot::speed.x + Robot::speed.y) / MAX_SPEED;
    Robot::position.x = resultSpeed * std::cos(Robot::radiansAngle);
    Robot::position.y = resultSpeed * std::sin(Robot::radiansAngle);
}
