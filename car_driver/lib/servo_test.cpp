#include <Arduino.h>
#include <Servo.h>

Servo servo;

int const potPin{A0};
int       potVal{0};
int       angle{0};

void setup() {
    servo.attach(9);

    Serial.begin(9600);
}

void loop() {
    potVal = analogRead(potPin);
    Serial.print("pot val: ");
    Serial.print(potVal);

    angle = map(potVal, 0, 1023, 0, 179);
    Serial.print(",  angle: ");
    Serial.println(angle);

    servo.write(angle);
    delay(15);
}
