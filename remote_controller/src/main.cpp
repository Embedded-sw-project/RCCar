// Core library for code-sense
#if defined(ENERGIA) // LaunchPad MSP430, Stellaris and Tiva, Experimeter Board
                     // FR5739 specific
#include "Energia.h"
#else // error
#error Platform not defined
#endif

#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(25, 28);

// Add setup code
void setup() {
    Serial.begin(9600); // for LCD debug output
}

// Add loop code
void loop()
{

}
