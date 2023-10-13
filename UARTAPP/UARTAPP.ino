#include <avr/io.h> //This header file contains definitions for I/O registers
#include <util/delay.h> //This header file provides delay functions for creating time delays in the code
#include "uart.h"
#include "BIT_MATH.h"
#include "Dio.h"
// define some macros
#define BAUD 9600  // define baud

#define MAX_LENGTH 8
const int LED_PIN = 7;
const int PUSH_PIN = 2;
void initInterrupt() {
  // Set interrupt sense control to trigger on falling edge
  EICRA |= (1 << ISC01);
  EICRA &= ~(1 << ISC00);

  // Enable external interrupt INT0
  EIMSK |= (1 << INT0);

  // Enable global interrupts
  sei();
}
void initIO() {
    // Set button pin as input with pull-up resistor
    DDRD &= ~(1 << PUSH_PIN);
    PORTD |= (1 << PUSH_PIN);
}


int main(void) {
  initInterrupt();
  initIO();
  SET_BIT(DDRD, LED_PIN); /*TO ST THE LED PIN HIGH USING THE SET BIT FUNCTION SO THE LED LIGHT UP*/
  //CLR_BIT(DDRD, PUSH_BUTTON);
  pinMode(PUSH_PIN, INPUT);
  init();
  char receivedString[MAX_LENGTH];
  
  while (1) {                          // THE WHILE (1) IS TO REPEAT THE FUNCTION EVERYTIME
    UART_receiveString(receivedString, MAX_LENGTH);     // 
    if (strcmp(receivedString, "LED_ON") == 0) {
      SET_BIT(PORTD, LED_PIN);
    }
    if (strcmp(receivedString, "LED_OFF") == 0) {  //the strcmp function returns zero when the two strings being compared are equal. So, by comparing the result of strcmp with zero (== 0), the code checks if the strings are equal.
      CLR_BIT(PORTD, LED_PIN);  /*TO ST THE LED PIN LOW USING THE SET BIT FUNCTION SO THE LED LIGHT IS OFF*/
    }
    _delay_ms(1000);
  }

  return 0;
}

void init() {
  uart_init(BAUD);
}
// Interrupt service routine for external interrupt INT0
ISR(INT0_vect) {
  char* message = "PUSH BUTTON is pressed \n";
  if ((PIND & (1 << PUSH_PIN)) == 0) {
    uart_transmitstr(message);
     
    _delay_ms(1000);
  }
}
