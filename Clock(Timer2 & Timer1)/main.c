

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#define btn_start PD7
#define btn_stop PD6
#include "UART.h"

#define led_toggle PORTB^=(1<<PB0)
volatile uint16_t time1;
#define tick1 15624
#define tick2 249
int sec=0;
int msec=0;
int countsec=0;
int min;

 void timer02_init(void)
    {
	    TCCR2A |= (1<<WGM21); //Set CTC mode
	    TCCR2B |= (1<<CS22); //64 prescaler
		TIMSK2 |= (1<<OCIE2A); //Set the interrupt request
		TCNT2 = 0;
	    OCR2A=tick2; // 1ms tick
	    sei();	
    }
	
	ISR(TIMER2_COMPA_vect)    //Interrupt service routine for second 8-bit timer
	{
    msec++;
	if (msec == 1000)  //1 sec
	{
		countsec++;
   PORTB^=(1<<PB1);
		msec=0;


TCNT2 = 0;

}
if (countsec == 60)  // 1 min
{
	countsec=0;
	min++;
	TCNT2 = 0;
}
	}
	void timeInit(void)
	{

		TCCR1B |= (1<<WGM12); // CTC mode
		TCCR1B |= (1<<CS12) | (1<<CS10); // set presceler to 1024
		TIMSK1 |= (1<<OCIE1A);  //Overflow Interrupt Enable
		TCNT1 = 0;
		OCR1A = tick1; //1 sec tick
		sei();
	}
	
	   ISR(TIMER1_COMPA_vect)
	   {
		   led_toggle;
		   sec++;
	   }
	   
int main(void)
{
	DDRB |= (1<<PB0) | (1 << PB1);
	DDRD &= ~( 1<< btn_start);
	DDRD &= ~( 1<< btn_stop);
	PORTD |= (1 << btn_start) | (1 << btn_stop);
		timeInit();
		timer02_init();
	USART_Init(MYUBRR);
	printf("Hi\n");


    while (1) 
    {
		
 printf("Timer2: %d min %d sec %d ms  Timer1: %d sec\n",min,countsec, msec, sec);


    }
}


