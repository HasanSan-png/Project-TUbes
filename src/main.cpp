#include <Arduino.h>
#include "invetaris.h"

void setup() {
    Serial.begin(9600); // <-- Tambahkan ini agar Serial Monitor berfungsi
    CekSound();
}

void loop() {
    mainmenu();
}
