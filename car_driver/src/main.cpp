/*
 * nRF24L01+ Receiver code written by drselim
 * https://www.youtube.com/c/drselim
 *
 */
#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h>
RF24          radio(8, 7); // CE, CSN
const uint8_t address[] = {0xCC, 0xCE, 0xCC, 0xCE, 0xCC};

void setup() {
    Serial.begin(9600);
    auto result = radio.begin();
    radio.openReadingPipe(5, address);
    radio.setPALevel(RF24_PA_MIN);
    radio.startListening();

    Serial.println("Ciao mondo");
    if (result) {
        Serial.println("begin successful");
    }

    if (radio.isChipConnected()) {
        Serial.println("Chip connected");
    }

    char buffer[870] = {'\0'};
    radio.sprintfPrettyDetails(buffer);
    Serial.println(buffer);
}
void loop() {

    if (radio.available()) {
        int dataToReceive[8];

        radio.read(&dataToReceive, sizeof(dataToReceive));

        String bosluk = " ";
        String String_to_Print = dataToReceive[0] + bosluk + dataToReceive[1] +
                                 bosluk + dataToReceive[2] + bosluk +
                                 dataToReceive[3] + bosluk + dataToReceive[4] +
                                 bosluk + dataToReceive[5] + bosluk +
                                 dataToReceive[6] + bosluk + dataToReceive[7];

        Serial.println(String_to_Print);
    }
}
