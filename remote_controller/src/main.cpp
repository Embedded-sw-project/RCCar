// Core library for code-sense
#include "msp432p401r.h"
#include "rom_map.h"
#include "uart.h"
#if defined(ENERGIA) // LaunchPad MSP430, Stellaris and Tiva, Experimeter Board
                     // FR5739 specific
#include "Energia.h"
#else // error
#error Platform not defined
#endif

#include "printf.h"
#include "stdbool.h"
#include "stdint.h"
#include <RF24.h>
#include <driverlib.h>
#include <nRF24L01.h>

#define CE_PIN 25
#define CSN_PIN 28
#define OUT EUSCI_A0_BASE

RF24       radio(CE_PIN, CSN_PIN);
const byte sampleText[6] = "hello";

/* UART Configuration Parameter. These are the configuration parameters to
 * make the eUSCI A UART module to operate with a 2400 baud rate. These
 * values were calculated using the online calculator that TI provides
 * at:
 *http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html
 */
const eUSCI_UART_Config uartConfig = {
    EUSCI_A_UART_CLOCKSOURCE_SMCLK,               // SMCLK Clock Source
    78,                                           // BRDIV = 78
    2,                                            // UCxBRF = 2
    0,                                            // UCxBRS = 0
    EUSCI_A_UART_NO_PARITY,                       // No Parity
    EUSCI_A_UART_LSB_FIRST,                       // MSB First
    EUSCI_A_UART_ONE_STOP_BIT,                    // One stop bit
    EUSCI_A_UART_MODE,                            // UART mode
    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION // Oversampling
};

void setupUART();
void setupRF24();
void transmitData(const byte data[]);

// Add setup code
void setup() {
    setupUART();
    setupRF24();
}

void setupRF24() {
    if (!radio.begin()) {
        printf(OUT, "The radio hardware is not responding!");
        while (1) {
        }
    }

    // opens a pipe for writing byte arrays
    uint8_t address[] = {0xCC, 0xCE, 0xCC, 0xCE, 0xCC};
    radio.openWritingPipe(address);

    // power level for range. Keep at MIN to avoid issues
    // high power levels give too much power to near antennas
    // and communications do not finish successfully
    radio.setPALevel(RF24_PA_MIN);

    /* this should be used if we want to receive and not transmit */
    // radio.startListening();

    if (!radio.isChipConnected()) {
        printf(OUT, "The chip is not connected to the SPI!");
        while (1) {
        }
    }
}

void setupUART() {
    /* Halting WDT  */
    MAP_WDT_A_holdTimer();

    /* Selecting P1.2 and P1.3 in UART mode */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P1, GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3,
        GPIO_PRIMARY_MODULE_FUNCTION);

    /* Setting DCO to 12MHz */
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);

    MAP_UART_initModule(OUT, &uartConfig);
    MAP_UART_enableModule(OUT);

    UART_initModule(OUT, &uartConfig);
    UART_enableModule(OUT);
}

// Add loop code
void loop() {
    // print debugging info. For now leave it here to know it's working.
    char     buffer[870] = {'\0'};
    uint16_t used_chars = radio.sprintfPrettyDetails(buffer);
    printf(OUT, "%s\n\n", buffer);

    transmitData(sampleText);
}

void transmitData(const byte *data) {
    radio.stopListening(); // always enforce closure just to be sure
    radio.write(&data, sizeof(data));
}
