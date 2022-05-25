/*
 * LED blink at specific freacuancy
 *
 * 
 * 
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>   
#define LED PB0 // 
#define freacuancy 250 //2 Hz by default (1000=1sec)
#define LED_on PORTB |= (1<<LED);  //set led bit to PORTB
#define LED_off PORTB &= ~(1<<LED); //clear led bit from PORTB

int main(void)
{
	DDRB |= (1<<LED); // set PB0 as output
    /* Replace with your application code */
    while (1) 
    {
		LED_on
		_delay_ms(freacuancy);
		LED_off;
		_delay_ms(freacuancy);
    }
}

