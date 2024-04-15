#include "lib/window.h"
#include "program.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_timer.h>
#include <array>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

int robotRadius = 10;
double robotX = robotRadius, robotY = robotRadius;
int robotLeftMotorSpeed = 0, robotRightMotorSpeed = 0;
double robotAngle = 0;

// 0-100 | 0 = wall | 100 = no wall
int sensorsValue[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int sensorAngles[8] = {0, 90, 270, 135, 315, 225, 45, 180};
std::vector<std::array<SDL_Point, 2>> lines;

void renderRobot(Window* window) {
    window->setColor(255, 0, 0);
    window->drawRay(robotX, robotY, robotAngle + 0, sensorsValue[0] + robotRadius);               // 1
    window->drawRay(robotX, robotY, robotAngle + 45 , sensorsValue[6] + robotRadius);             // 7
    window->drawRay(robotX, robotY, robotAngle + 90, sensorsValue[1] + robotRadius);              // 2
    window->drawRay(robotX, robotY, robotAngle + 90 + 45, sensorsValue[3] + robotRadius);         // 4

    // Not works in real life
    //window->drawRay(robotX, robotY, robotAngle + 180, 100);        // 8

    window->drawRay(robotX, robotY, robotAngle + 360 - 45, sensorsValue[4] + robotRadius);        // 5
    window->drawRay(robotX, robotY, robotAngle + 360 - 90, sensorsValue[2] + robotRadius);        // 3
    window->drawRay(robotX, robotY, robotAngle + 360 - 90 - 45, sensorsValue[5] + robotRadius);   // 6

    window->setColor(0, 100, 40);
    window->fillCircle(robotX, robotY, robotRadius);

    window->setColor(40, 40, 40);
    window->fillRotatedRect(robotX - (double) robotRadius/1.5, robotY - (double) robotRadius/4, robotRadius, (double) robotRadius/2, robotAngle, robotX, robotY);
}

int intersec2d(SDL_Point k, SDL_Point l, SDL_Point m, SDL_Point n, double &s, double &t) {
    double det = (n.x - m.x) * (l.y - k.y)  -  (n.y - m.y) * (l.x - k.x);
    if (det == 0.0) return 0;

    s = ((n.x - m.x) * (m.y - k.y) - (n.y - m.y) * (m.x - k.x))/ det;
    t = ((l.x - k.x) * (m.y - k.y) - (l.y - k.y) * (m.x - k.x))/ det;

    return 1;
}

void updateSensorsValue() {
    for (int i = 0; i < 8; i++) {
        int endX = robotX + static_cast<int>((robotRadius + 100) * std::cos((robotAngle + sensorAngles[i]) * M_PI / 180.0));
        int endY = robotY + static_cast<int>((robotRadius + 100) * std::sin((robotAngle + sensorAngles[i]) * M_PI / 180.0));
        SDL_Point k = {(int) robotX, (int) robotY};
        SDL_Point l = {endX, endY};

        sensorsValue[i] = 100;
        for (auto line : lines) {
            double s, t;
            if (intersec2d(k, l, line[0], line[1], s, t)) {
                int x = k.x + (l.x - k.x)*s;
                int y = k.y + (l.y - k.y)*s;

                int maxLineX = line[0].x > line[1].x ? line[0].x : line[1].x;
                int maxLineY = line[0].y > line[1].y ? line[0].y : line[1].y;
                int minLineX = line[0].x < line[1].x ? line[0].x : line[1].x;
                int minLineY = line[0].y < line[1].y ? line[0].y : line[1].y;

                // Check if x and y is in range of line
                if (x >= minLineX && x <= maxLineX && y >= minLineY && y <= maxLineY) {
                    // Check if x and y is in range of robot
                    int endRayX = robotX + static_cast<int>(100 * std::cos((sensorAngles[i] + robotAngle) * M_PI / 180.0));
                    int endRayY = robotY + static_cast<int>(100 * std::sin((sensorAngles[i] + robotAngle) * M_PI / 180.0));

                    int maxRobotX = robotX > endRayX ? robotX : endRayX;
                    int maxRobotY = robotY > endRayY ? robotY : endRayY;
                    int minRobotX = robotX < endRayX ? robotX : endRayX;
                    int minRobotY = robotY < endRayY ? robotY : endRayY;

                    if (x >= minRobotX && x <= maxRobotX && y >= minRobotY && y <= maxRobotY) {
                        int dist = sqrt(pow((double) x - robotX, 2) + pow((double)y - robotY, 2)) - robotRadius;
                        if (dist <= 100 && sensorsValue[i] > dist) sensorsValue[i] = dist;
                    }
                }
            }
        }
    }
}

void updateRobot() {
    double dirSpeed = (double) (robotLeftMotorSpeed - robotRightMotorSpeed) / 100;
    double cRotation = 0.01;

    double rotationForce = dirSpeed * cRotation;
    robotAngle += rotationForce * 180.0 /  M_PI;
    if (robotAngle >= 360) robotAngle -= 360;
    if (robotAngle <= -360) robotAngle += 360;

    double resultSpeed = (robotLeftMotorSpeed + robotRightMotorSpeed) / 200.0;
    robotX += resultSpeed * std::cos(robotAngle * M_PI / 180.0);
    robotY += resultSpeed * std::sin(robotAngle * M_PI / 180.0);
    updateSensorsValue();
}

long delayValue = 0;
int main() {
    Window window = Window("Baratinha Simulator", 800, 600);
    setup();
    robotX = 200;
    robotY = 200;

    int sx = 0, sy = 0, ex = 0, ey = 0;

    bool quit = false;
    while (!quit) {
        auto start = std::chrono::steady_clock::now();
        window.clear();

        SDL_Event* event;
        while ((event = window.poolEvent()) != nullptr) {
            if (event->type == SDL_QUIT) {
                quit = true;
                continue;
            } else if (event->type == SDL_MOUSEBUTTONDOWN) {
                sx = event->button.x;
                sy = event->button.y;
                ex = sx;
                ey = sy;
            } else if (event->type == SDL_MOUSEMOTION) {
                if (sx != 0 || ey != 0) {
                    ex = event->button.x;
                    ey = event->button.y;
                }
            } else if (event->type == SDL_MOUSEBUTTONUP) {
                std::array<SDL_Point, 2> line = {{{sx, sy}, {ex, ey}}};
                lines.push_back(line);
                sx = 0;
                sy = 0;
                ex = 0;
                ey = 0;
            }
        }

        loop();
        updateRobot();

        window.setColor(255, 255, 255);
        for (auto line : lines) {
            window.drawThickLine(line[0].x, line[0].y, line[1].x, line[1].y, 1);
        }

        if (sx != 0 || sy != 0 || ex != 0 || ey != 0) {
            window.drawThickLine(sx, sy, ex, ey, 1);
        }

        renderRobot(&window);
        window.present();


        //robotAngle = (robotAngle + 1) % 360;

        auto diff = std::chrono::steady_clock::now() - start;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
        long delay = (1000 / 60) - ms.count();
        SDL_Delay(delay + delayValue);
    }

    return 0;
}

void onDelayCalled(long delay) {
    delayValue = delay;
}

void onMotorCalled(bool leftDirection, uint8_t leftSpeed, bool rightDirection, uint8_t rightSpeed) {
    robotLeftMotorSpeed = leftSpeed * (leftDirection ? 1 : -1);
    robotRightMotorSpeed = rightSpeed * (rightDirection ? 1 : -1);
}

unsigned int onReadSensorCalled(int sensor) {
    if (sensor >= 1 && sensor <= 8) {
        return sensorsValue[sensor - 1];
    }
    return 0;
}
