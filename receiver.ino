#include <SPI.h>

#include "nRF24L01.h"

#include "RF24.h"

int senderId;

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10
//Contacts from the radio to connect NRF24L01 pinamnam -> Arduino

//SCK -> 13
//MISO -> 12
//MOSI -> 11
//CSN -> 10
//CE -> 9

RF24 radio(9, 10);

// this is not the channel address, but the transmitter address
const uint64_t pipe = 0xE8E8F0F0E1LL;

//LEDs connected to these pins
// ENSURE YOU HAVE THE RIGHT DIGITAL PINS HERE
int LEDpins[5] = { 2, 3, 4, 5, 6 };

void setup(void) {
	Serial.begin(9600);

	radio.begin();

	// the following statements improve transmission range
	radio.setPayloadSize(2); // setting the payload size to the needed value
	radio.setDataRate(RF24_250KBPS); // reducing bandwidth

	radio.openReadingPipe(1, pipe); // Open one of the 6 pipes for reception

	radio.startListening(); // begin to listen

	// Enable all the LED pins as output
	for (int i = 0; i < 5; i++) {
		pinMode(LEDpins[i], OUTPUT);
		digitalWrite(LEDpins[i], LOW); // this is unnecessary but good practice nonetheless
	}

}

void loop(void) {

	// Turns off all the LEDs
	for (int i = 0; i < 5; i++) {
		digitalWrite(LEDpins[i], LOW);
	}

	if (radio.available()) {

		// this while is here to throw away all the packets but the last one
		bool done = false;
		while (!done) {

			// read and write expect a reference to the payload (& symbol)
			// second argument is the packet length in bytes (sizeof(int) == 2)
			done = radio.read(&senderId, 2);
		}

		//Light up the correct LED for 50ms
		digitalWrite(LEDpins[senderId], HIGH);
		Serial.print("LED ");
		Serial.print(senderId);
		Serial.println(" On");
		delay(50);
	}
}
