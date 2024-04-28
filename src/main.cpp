#include <cstdio>
#include <raylib.h>

const int screenWidth = 960;
const int screenHeight = 720;

const int targetFPS = 60;
const int traceLogLevel = LOG_WARNING;

void onUpdate() {
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
}

int main() {
    SetTraceLogLevel(traceLogLevel);

    InitWindow(screenWidth, screenHeight, "BaratinhaSimulator");
    SetTargetFPS(targetFPS);

    while (!WindowShouldClose()) onUpdate();
    CloseWindow();
}
