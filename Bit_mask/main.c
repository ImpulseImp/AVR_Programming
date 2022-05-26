/*
 * This program test every bit of DDRD register
 * and prints its state
 * 
 * 
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

char bit_mask=1; // We start from the lowest bit 0 and keep shifting it to bit 7
char count; // PORT has a bank of 8 bits. It goes from 0-7. We're going to check every bit in DDRD register
//USART configuration
void USART_Init( unsigned int);
void USART_Transmit( unsigned char);
unsigned char USART_Receive( void );
static int uart_putchar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL,
_FDEV_SETUP_WRITE);
static int uart_putchar(char c, FILE *stream);

int main(void)
{
	DDRD =0b10101011; // set these bits and see a pattern in serial monitor
	USART_Init(MYUBRR);
	stdout = &mystdout;
    /* Replace with your application code */
    while (1) 
    {
		for (count=0; count<8; count++)
		{
			//test port bits and print the result		
			if(DDRD & bit_mask) printf("bit %d in DDRD is set(1)\n\r",count);
			else printf("bit %d in DDRD isn't set(0)\n\r",count);
			 bit_mask <<=1; //shift bit to be tested
		}
		while(1); //sit here, stop our test
    }
}


void USART_Init( unsigned int ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	//Enable receiver and transmitter
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}

static int
uart_putchar(char c, FILE *stream)
{
	if (c == '\n')
	uart_putchar('\r', stream);
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
	return 0;
}