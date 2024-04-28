#include "robot.h"
#include <cmath>
#include <raylib.h>

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
   // double dirSpeed = (double)(robotLeftMotorSpeed - robotRightMotorSpeed) / 100;
   // double cRotation = 0.01;

   // double rotationForce = dirSpeed * cRotation;
   // robotAngle += rotationForce * 180.0 / M_PI;
   // if (robotAngle >= 360) robotAngle -= 360;
   // if (robotAngle <= -360) robotAngle += 360;

   // double resultSpeed = (robotLeftMotorSpeed + robotRightMotorSpeed) / 200.0;
   // robotX += resultSpeed * std::cos(robotAngle * M_PI / 180.0);
   // robotY += resultSpeed * std::sin(robotAngle * M_PI / 180.0);
   // updateSensorsValue();

    float dirSpeed = (Robot::speed.x - Robot::speed.y) / 100.0f;
    float rotationForce = dirSpeed * 0.01f;
    Robot::radiansAngle = fmodf(radiansAngle + rotationForce, 2 * M_PIf);
    if (Robot::radiansAngle < 0) Robot::radiansAngle += 2 * M_PIf;

}
