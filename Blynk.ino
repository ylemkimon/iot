#define BLYNK_PRINT Serial

#include "blynk.h"

char auth[] = "(Token)";

int mainLight = D1;
int auxLight = D0;

void setup()
{
    Serial.begin(9600);
    pinMode(mainLight, OUTPUT);
    pinMode(auxLight, OUTPUT);
    delay(5000);

    Blynk.begin(auth);
}

// all lights
BLYNK_WRITE(V0) {
    int state = 1 - param.asInt();
    digitalWrite(mainLight, state);
    digitalWrite(auxLight, state);
    Blynk.virtualWrite(V1, state);
    Blynk.virtualWrite(V2, state);
}

// morning
BLYNK_WRITE(V3) {
    if (param.asInt() == HIGH) {
        digitalWrite(mainLight, LOW);
        digitalWrite(auxLight, LOW);
        Blynk.virtualWrite(V1, LOW);
        Blynk.virtualWrite(V2, LOW);
        Blynk.virtualWrite(V0, HIGH);
    }
}

// main light
BLYNK_WRITE(V1) {
    digitalWrite(mainLight, param.asInt());
    Blynk.virtualWrite(V0, digitalRead(mainLight) + digitalRead(auxLight) < 2);
}

// aux light
BLYNK_WRITE(V2) {
    digitalWrite(auxLight, param.asInt());
    Blynk.virtualWrite(V0, digitalRead(mainLight) + digitalRead(auxLight) < 2);
}

// ZeRGBa
BLYNK_WRITE(V4) {
    int r = param[0].asInt();
    int g = param[1].asInt();
    int b = param[2].asInt();
    if (r < 255 || g < 255 || b < 255) {
        RGB.control(true);
        RGB.color(r, g, b);
    } else {
        RGB.control(false);
    }
}

void loop() {
    Blynk.run();
}
