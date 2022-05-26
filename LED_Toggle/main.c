/*
 * Toggle an LED with a button
 * We'll be reading I/O to toggle an LED
 * 
 * 
 */ 
#define F_CPU 16000000UL  // run our crystal at 16 MHz
#include <avr/io.h>
 
#define LED PB0 // connect an LED to PINB0 (pin 8 on an Arduino board)
#define Btn PD3 // connect a button to PIND3  (pin 3 on an Arduino board)
//add some macros for readability 
#define LED_on PORTB |= (1<<LED);  //set led bit to PORTB
#define LED_off PORTB &= ~(1<<LED); //clear led bit from PORTB

int main(void)
{
	DDRB |= (1<<LED); // set PB0 as output
    DDRD &= ~(1<<Btn); // not necessarily but make sure this bit is set as an output
	PORTD |=(1<<Btn); // turn on an internal pull-up resistor
    while (1) 
    {
		if (bit_is_clear(PIND,Btn)) //if button is pressed LED on
		{
			LED_on;
		} 
		else  // button isn't plessed LED off 
		{
			LED_off;
		} 
    }
}















