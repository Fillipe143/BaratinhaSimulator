#include "arduino/baratinha.h"
#include "arduino/core.h"

void setup() {
}

long startTime = 0;
bool isWalking = false;

void loop() {
    // Anda por 1 segundo depois para espera um segundo e volta a andar
    if (millis() - startTime >= 1000) {
        isWalking = !isWalking;
        startTime = millis();
    }

    if (isWalking) {
        motor(GO_FORWARD, 100, GO_FORWARD, 100);
    } else {
        motor(GO_FORWARD, 100, GO_BACK, 100);
    }
}
