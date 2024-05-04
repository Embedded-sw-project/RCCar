// Core library for code-sense
#if defined(ENERGIA) // LaunchPad MSP430, Stellaris and Tiva, Experimeter Board
                     // FR5739 specific
#include "Energia.h"
#else // error
#error Platform not defined
#endif

#include <RF24.h>
#include <nRF24L01.h>

#define CE_PIN 25
#define CSN_PIN 28

RF24 radio(CE_PIN, CSN_PIN);  
const uint8_t address[][6] = {"1Node"};
const byte sampleText[6] = "hello";

void transmitData(const byte data[]);

// Add setup code
void setup() {
    Serial.begin(9600); // for LCD debug output

    radio.begin();    

    // opens a pipe for writing byte arrays
    radio.openWritingPipe(address[0]);

    // power level for range. Keep at MIN to avoid issues
    // high power levels give too much power to near antennas
    // and communications do not finish successfully
    radio.setPALevel(RF24_PA_MIN); 
    
    /* this should be used if we want to receive and not transmit */
    // radio.startListening(); 
    
}

// Add loop code
void loop()
{
    transmitData(sampleText);
}


void transmitData(const byte* data) {
    radio.stopListening(); // always enforce closure to be sure
    radio.write(&data, sizeof(data));
}