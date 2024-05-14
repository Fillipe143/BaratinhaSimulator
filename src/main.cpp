#include "./program/arduino.h"
#include <chrono>
#include <cmath>
#include <cstddef>
#include <raylib.h>
#include <thread>

#define DEFAULT_RADIUS 15
#define TARGET_FPS 60

#define MAX_SENSOR 100
#define MAX_SPEED 100
#define MAX_ANGLE (2 * M_PIf)
#define ROTATION_CONST 0.01f

#define RADIANS_TO_DEGREE(r) (r * 180.0f / M_PIf)
#define DEGREE_TO_RADIANS(r) (r * M_PIf / 180.0f)

void updateRobot();
void updateSensors();

void renderRobot();
void renderSensors();

const int sensorAngles[8] = { 90, 180, 0, 225, 45, 315, 135, 270 };
// const int sensorAngles[8] = { 0, 90, 270, 135, 315, 225, 45, 180 };

struct Robot {
    Vector2 position;
    int sensors[8];
    Vector2 speed;
    float angle = M_PI_2f;
    float radius;
    Color color;
};

Robot robot = {
    .position = { DEFAULT_RADIUS, DEFAULT_RADIUS },
    .sensors = { MAX_SENSOR, MAX_SENSOR, MAX_SENSOR, MAX_SENSOR, MAX_SENSOR, MAX_SENSOR, MAX_SENSOR, MAX_SENSOR },
    .speed = { 0, 0 },
    .angle = 0,
    .radius = DEFAULT_RADIUS,
    .color = { 0, 100, 40, 255 }
};

int delayTime = 0;
std::chrono::time_point<std::chrono::steady_clock> startTime;

int main() {
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(800, 600, "Baratinha Simulator");
    SetTargetFPS(TARGET_FPS);

    startTime = std::chrono::steady_clock::now();
    setup();

    while (!WindowShouldClose()) {
        std::thread t1(loop);
        t1.detach();

        updateRobot();
        renderRobot();
    }

    CloseWindow();
}

void updateRobot() {
    float dirSpeed = (robot.speed.x - robot.speed.y) / MAX_SPEED;
    float rotationForce = dirSpeed * ROTATION_CONST;

    robot.angle = fmodf(robot.angle + rotationForce, MAX_ANGLE);
    if (robot.angle < 0) robot.angle += MAX_ANGLE;

    float resultSpeed = (robot.speed.x + robot.speed.y) / MAX_SPEED;
    robot.position.x += resultSpeed * cosf(robot.angle);
    robot.position.y += resultSpeed * sinf(robot.angle);

    updateSensors();
}

void renderRobot() {
    BeginDrawing();

    ClearBackground(BLACK);
    renderSensors();

    DrawCircleV(robot.position, robot.radius, robot.color);
    Rectangle rec = { robot.position.x, robot.position.y, robot.radius, robot.radius };
    DrawRectanglePro(rec, { robot.radius / 2, robot.radius / 2 }, RADIANS_TO_DEGREE(robot.angle), GRAY);
    EndDrawing();
}

void updateSensors() {
}

void renderSensors() {
    for (size_t i = 0; i < sizeof(robot.sensors) / sizeof(int); i++) {
        if (i == 7) continue;

        int dim = robot.sensors[i];
        float angle = DEGREE_TO_RADIANS(sensorAngles[i]) - robot.angle;

        Vector2 start = robot.position;
        Vector2 end = start;
        end.x += dim * sinf(angle);
        end.y += dim * cosf(angle);

        DrawLineV(start, end, RED);
    }
}

// Built in methods
long map(long x, long inMin, long inMax, long outMin, long outMax) {
    return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

void delay(unsigned long millis) {
    delayTime = millis;
}

unsigned long millis() {
    auto end = std::chrono::steady_clock::now();
    auto diff = end - startTime;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
    return ms.count();
}

int readAngle() {
    return RADIANS_TO_DEGREE(robot.angle);
}

int readSensor(int sensor) {
    if (sensor >= 1 && sensor <= 8) {
        return robot.sensors[sensor - 1];
    }
    return 0;
}

void motor(bool leftDirection, uint8_t leftSpeed, bool rightDirection, uint8_t rightSpeed) {
    robot.speed.x = (leftSpeed % (MAX_SPEED + 1)) * (leftDirection ? 1 : -1);
    robot.speed.y = (rightSpeed % (MAX_SPEED + 1)) * (rightDirection ? 1 : -1);
}
