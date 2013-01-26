/* Copyright (C) 2011-2013 by Jacob Alexander
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

// ----- Includes -----

// Compiler Includes
#include <Lib/MainLib.h>

// Project Includes
#include <macro.h>
#include <scan_loop.h>
#include <usb_com.h>

#include <led.h>
#include <print.h>



// ----- Defines -----

// Verified Keypress Defines
#define USB_TRANSFER_DIVIDER 10 // 1024 == 1 Send of keypresses per second, 1 == 1 Send of keypresses per ~1 millisecond



// ----- Macros -----
#if defined(_at90usb162_) || defined(_atmega32u4_) || defined(_at90usb646_) || defined(_at90usb1286_)
#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n))
#endif



// ----- Variables -----

// Timer Interrupt for flagging a send of the sampled key detection data to the USB host
uint16_t sendKeypressCounter = 0;

// Flag generated by the timer interrupt
volatile uint8_t sendKeypresses = 0;



// ----- Functions -----

// Initial Pin Setup, make sure they are sane
inline void pinSetup(void)
{

// AVR
#if defined(_at90usb162_) || defined(_atmega32u4_) || defined(_at90usb646_) || defined(_at90usb1286_)

	// For each pin, 0=input, 1=output
#if defined(__AVR_AT90USB1286__)
	DDRA = 0x00;
#endif
	DDRB = 0x00;
	DDRC = 0x00;
	DDRD = 0x00;
	DDRE = 0x00;
	DDRF = 0x00;


	// Setting pins to either high or pull-up resistor
#if defined(__AVR_AT90USB1286__)
	PORTA = 0x00;
#endif
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	PORTE = 0x00;
	PORTF = 0x00;

// ARM
#elif defined(_mk20dx128_)
	// TODO
#endif
}


inline void usbTimerSetup(void)
{
// AVR
#if defined(_at90usb162_) || defined(_atmega32u4_) || defined(_at90usb646_) || defined(_at90usb1286_)

	// Setup with 16 MHz clock
	CPU_PRESCALE( 0 );

	// Setup ISR Timer for flagging a kepress send to USB
	// Set to 256 * 1024 (8 bit timer with Clock/1024 prescalar) timer
	TCCR0A = 0x00;
	TCCR0B = 0x03;
	TIMSK0 = (1 << TOIE0);

// ARM
#elif defined(_mk20dx128_)
	// TODO
#endif
}


int main(void)
{
	// Configuring Pins
	pinSetup();
	init_errorLED();

	// Setup USB Module
	usb_setup();

	// Setup ISR Timer for flagging a kepress send to USB
	usbTimerSetup();

	// Main Detection Loop
	uint8_t ledTimer = 15; // Enable LED for a short time
	while ( 1 )
	{
		// Setup the scanning module
		scan_setup();

		while ( 1 )
		{
			// Acquire Key Indices
			// Loop continuously until scan_loop returns 0
			cli();
			while ( scan_loop() );
			sei();

			// Run Macros over Key Indices and convert to USB Keys
			process_macros();

			// Send keypresses over USB if the ISR has signalled that it's time
			if ( !sendKeypresses )
				continue;

			// Send USB Data
			usb_send();

			// Clear sendKeypresses Flag
			sendKeypresses = 0;

			// Indicate Error, if valid
			errorLED( ledTimer );

			if ( ledTimer > 0 )
				ledTimer--;
		}

		// Loop should never get here (indicate error)
		ledTimer = 255;

		// HID Debug Error message
		erro_print("Detection loop error, this is very bad...bug report!");
	}
}


// ----- Interrupts -----

// AVR - USB Keyboard Data Send Counter Interrupt
#if defined(_at90usb162_) || defined(_atmega32u4_) || defined(_at90usb646_) || defined(_at90usb1286_)

ISR( TIMER0_OVF_vect )
{
	sendKeypressCounter++;
	if ( sendKeypressCounter > USB_TRANSFER_DIVIDER ) {
		sendKeypressCounter = 0;
		sendKeypresses = 1;
	}
}

// ARM - USB Keyboard Data Send Counter Interrupt
#elif defined(_mk20dx128_)
	// TODO
#endif

