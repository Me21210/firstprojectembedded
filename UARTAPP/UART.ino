#include <avr/io.h>
#include "BIT_MATH.h"

void uart_SetBaudRate(int baud) {
  int ubrr = ((F_CPU) / (baud * 16UL) - 1);
  UBRR0H = (ubrr >> 8);  // shift the register right by 8 bits
  UBRR0L = ubrr;         // set baud rate bits [7 : 0]
}

void uart_init(int baud) {
  uart_SetBaudRate(baud);

  // enable receiver and transmitter
  SET_BIT(UCSR0B, TXEN0);
  SET_BIT(UCSR0B, RXEN0);

  // 8bit data format and 1 stop bit
  SET_BIT(UCSR0C, UCSZ00);
  SET_BIT(UCSR0C, UCSZ01);
}

// function to send data
/*void uart_transmit(unsigned char data) {
  int udr_empty;
  do {
    udr_empty = (GET_BIT(UCSR0A, UDRE0)) != 0;
  } while (!udr_empty);  // wait while register is free

  UDR0 = data;  // load data in the register
}*/
void uart_transmitchar (char data)
{
	int udr_empty;
	do
	{
		udr_empty = (UCSR0A & (1<<UDRE0)) != 0;
	}while(!udr_empty);                            // wait while register is free

	UDR0 = data;                                  // load data in the register
}
void uart_transmitstr (char *str)
{
	for(size_t i =0; i<strlen(str); i++)
	{
		uart_transmitchar(str[i]);
	}
}

/* function to receive data
unsigned char uart_recieve (void)
{
  while(!uart_recieve_ready ());                   // wait while data is being received
  return UDR0;                                   // return 8-bit data
}*/
void UART_receiveString(char *str, unsigned char maxLength) {
	unsigned char i = 0;
	while (i < (maxLength - 1)) {
		while (GET_BIT(UCSR0A, RXC0) == 0); // Wait for data to be received
		unsigned char receivedByte = UDR0; // Read the received byte
		
		// Check for end of string
		if (receivedByte == '\0' || receivedByte == '\n' || receivedByte == '\r') {
			break;
		}
		
		str[i++] = receivedByte;
	}
	str[i] = '\0'; // Null-terminate the string
}

int uart_recieve_ready(void) {
  int flag = (GET_BIT(UCSR0A, RXC0)) != 0;  // check if data is receiving is complete
  return flag;
}
