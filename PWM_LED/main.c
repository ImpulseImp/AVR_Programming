#define F_CPU 16000000
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define LED PB0
#define toggle PINB |= (1<<PB0)
#define LED_on PORTB |=(1<<LED)
#define LED_off PORTB &= ~(1<<LED)

ISR(TIMER1_COMPA_vect)
{
	LED_on;
	
}

ISR(TIMER1_COMPB_vect)
{
	LED_off;
	
}

void PWM_LED(int A, int B)
{
	TCCR1B |= (1<<CS10)| (1<<WGM12);  //no prescaler , CTC mode
	TIMSK1 |= (1<<OCIE1A) | (1<<OCIE1B); //Output Compare A and B Match Interrupt Enable
	OCR1A = A;   //led on
	OCR1B = B;  //led off
}


int main(void)
{
	/* Set the baudrate to 9600 bps using 16MHz internal RC oscillator */
	DDRB |= (1<<LED); //set led pin as an output
	PWM_LED(800, 50); //duty cycle
	sei(); //global interrupt enable
	
	while (1)
	{

	}
	
}





