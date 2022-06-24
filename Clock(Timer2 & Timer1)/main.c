// Timer2 is set to 1msec
//Timer1 is set to 1sec

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#define btn_start PD7
#define btn_stop PD6
#include "UART.h"
#define tick1 15625
#define tick2 250
int sec=0;
int msec=0;
int countsec=0;
int min;

 void timer02_init(void)
    {
	    TCCR2A |= (1<<WGM21); //Set CTC mode
	    TCCR2B |= (1<<CS22); //64 prescaler
	    OCR2A   =  tick2; // 1ms tick
	    TIMSK2 |= (1<<OCIE2A); //Set the interrupt request		
    }
	
	ISR(TIMER2_COMPA_vect)    //Interrupt service routine for second 8-bit timer
	{
    msec++;
	if (msec == 1000)
	{
		 countsec++;
		 msec=0;
			
	}
	if (countsec == 60) 
	{
		countsec=0;
		min++;
	}
	}
	void timeInit(void)
	{

		TCCR1B |= (1<<WGM12); // CTC mode
		TCCR1B |= (1<<CS12) | (1<<CS10); // set presceler to 1024
		TIMSK1 |= (1<<OCIE1A);  //Overflow Interrupt Enable
		TCNT1 = 0;
		OCR1A = tick1; //1 sec
		sei();
	}
	
	   ISR(TIMER1_COMPA_vect)
	   {
		   sec++;
	   }
	   
int main(void)
{
		timeInit();
		timer02_init();
	  USART_Init(MYUBRR);
	  printf("Hi\n");


    while (1) 
    {
printf("Timer2: %d min %d sec %d ms  Timer1: %d\n",min,countsec, msec, sec);
    }
}

