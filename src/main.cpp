#include <Arduino.h>
#include "invetaris.h"

void setup() {
    Serial.begin(9600); 
    CekSound();
}

void loop() {
    mainmenu();
}
