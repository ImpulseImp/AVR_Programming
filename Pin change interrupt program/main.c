/*
 * Pin change interrupt program
 * In this program we have 2 LEDSs. One of them toggles constantly every 3 seconds using delay() function.
 * 
 * 
 */ 
#define F_CPU 16000000UL  // run our crystal at 16 MHz
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define LED_interrupt PB0 // connect an LED to PINB0 (pin 8 on an Arduino board)
#define LED_delay PD7
#define Btn PB1 // connect a button to PINB1  (pin 9 on an Arduino board)
//add some macros for readability 
#define LED_on PORTB |= (1<<LED_interrupt);  //set led bit to PORTB
#define LED_off PORTB &= ~(1<<LED_interrupt); //clear led bit from PORTB

  ISR (PCINT0_vect) //interrupt service routine. It trigers every time when you press the button
{
	if (bit_is_clear(PINB,Btn)) //if button is pressed LED on
	{
		LED_on;
		
	}
	else  // button isn't plessed LED off
	{
		LED_off;
		} 
}

int main(void)
{
	DDRB |= (1<<LED_interrupt); // set PB0 as output
        DDRB &= ~(1<<Btn); // not necessarily but make sure this bit is set as an output
	PORTB |=(1<<Btn); // turn on an internal pull-up resistor
	PCMSK0 |=(1<<PCINT1); //we set this bit to PCMSK0 due to the datasheet (PB1 is PCINT1)
	PCICR |=(1<<PCIE0); // there is 3 Pin-change interrupts (PCIE0 for PB0 .. PB7, PCIE1 for PC0 .. PC6, PCIE2 for PD0 .. PD7)
	DDRD |= (1<<LED_delay);// set this bit as an output
	sei(); // set interrupt enable bit 
	
    while (1) 
    {
		/*here is one of our Leds keeps toggling every 3 secs freezing the CPU with a delay function
		but we can toggle our seconds Led at any moment we want using interrupt service routine*/
		PORTD |=(1<<LED_delay);
		_delay_ms(3000);
		PORTD &=~(1<<LED_delay);
		_delay_ms(3000);
    }
}


