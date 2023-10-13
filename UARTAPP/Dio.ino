#include "BIT_MATH.h"

void DIO_init();

void DIO_SetPinstate(unsigned char port, int pin, unsigned char state)
{
  if (port == 'd' & pin <= 7 & pin >=0){   // Check if the port is 'd' and the pin is within the valid range (0-7)
  if(state == 'H'){
   SET_BIT(PORTD,pin);  // Set the corresponding bit in the PORTD register
  }else if(state == 'L'){
    CLR_BIT(PORTD,pin);  // Clear the corresponding bit in the PORTD register
  }
  }
}
void DIO_SetPinDirection(unsigned char port, int pin, unsigned char direction) 
{
  if (port == 'd' & pin <= 7 & pin >=0){
  if(direction == 'O'){  // Set the corresponding bit in the DDRD register to configure the pin as output
   SET_BIT(PORTD,pin); 
  }else if(direction == 'l'){
    CLR_BIT(PORTD,pin);
  }
}
}


