#include "entities/robot.h"
#include <cstdio>
#include <raylib.h>

const int screenWidth = 960;
const int screenHeight = 720;

const int targetFPS = 60;
const int traceLogLevel = LOG_WARNING;

void onStart();
void onUpdate();

int main() {
    SetTraceLogLevel(traceLogLevel);

    InitWindow(screenWidth, screenHeight, "BaratinhaSimulator");
    SetTargetFPS(targetFPS);

    onStart();
    while (!WindowShouldClose()) onUpdate();

    CloseWindow();
}

Robot* robot;
void onStart() {
    robot = new Robot(Vector2 { 100.0f, 100.0f });
    robot->motor(GO_FORWARD, 100, GO_FORWARD, 100);
}

void onUpdate() {
    robot->update();
    BeginDrawing();
    ClearBackground(BLACK);
    robot->render();
    EndDrawing();
}
