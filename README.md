# BaratinhaSimulator

Simulador do robô "Baratinha", para fins de criar algorítimos para resolução de labirinto de uma forma mais rápida.

![image](https://github.com/Fillipe143/BaratinhaSimulator/assets/69363580/44854ecb-4671-4b86-b9a4-89e8a6f71d90)

## Avisos
- Atualmente o simulador só tem suporte, para os métodos ``millis()``, ``delay()``, ``Serial::print()`` e ``Serial::println()`` do Arduíno.
- Para este simulador funcionar corretamente é necessario que você tenha o SDL2 instalado em seu computador.

## Comandos
### Controlar motores
```cpp
motor(leftDirection, leftMotorSpeed, rightDirection, rightMotorSpeed);
```
A direção pode ser ``GO_FORWARD``, para ir para frente ou ``GO_BACK``, para ir para trás.
A velocidade é um inteiro que varia de 0 a 100, sendo 100 a velocidade máxima.

### Ler sensores
```cpp
int distance = readSensor(sensor);
```
O sensor pode ser, ``SENSOR_FRONT``, ``SENSOR_LEFT``, ``SENSOR_RIGHT``, ``SENSOR_FRONT_LEFT`` ou ``SENSOR_FRONT_RIGHT``.
O método retorna um inteiro de que varia de 0 a 100, sendo 0 o mais próximo possível de uma parede.

## Exemplo
```cpp
#include "arduino/baratinha.h"
#include "arduino/core.h"

void setup() { }

int startTime = 0;
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
```
