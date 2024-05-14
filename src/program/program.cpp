#include "arduino.h"
#include <cmath>

void setup() {
}

long lastTime = 0;
void loop() {
    if (millis() - lastTime <= 1300) motor(GO_FORWARD, 100, GO_BACK, 100);
    else if (millis() - lastTime <= 3300) motor(GO_FORWARD, 100, GO_FORWARD, 100);
    else if (millis() - lastTime <= 4600) motor(GO_BACK, 100, GO_FORWARD, 100);
    else if (millis() - lastTime <= 7600) motor(GO_FORWARD, 100, GO_FORWARD, 100);
    else if (millis() - lastTime <= 8900) motor(GO_BACK, 100, GO_FORWARD, 100);
    else if (millis() - lastTime <= 10900) motor(GO_FORWARD, 100, GO_FORWARD, 100);
    else if (millis() - lastTime <= 12200) motor(GO_BACK, 100, GO_FORWARD, 100);
    else if (millis() - lastTime <= 15200) motor(GO_FORWARD, 100, GO_FORWARD, 100);
    //else if (millis() - lastTime <= 16500) motor(GO_BACK, 100, GO_FORWARD, 100);
    else motor(GO_FORWARD, 0, GO_FORWARD, 0);
}
