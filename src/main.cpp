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

void onStart() {
}

void onUpdate() {
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
}
