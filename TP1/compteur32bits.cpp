/*
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme 
 * Version: 1.1
 */

#define F_CPU 8000000UL
#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>


void setColorDelay(uint8_t color, uint16_t ms){
	uint8_t currentColor = color;
	uint8_t offset = 0;
	while(ms > 0){
		PORTB = (currentColor & 0x1) << offset;
		currentColor >>= 1;
		offset++;
		if(currentColor == 0x0){
			currentColor = color;
			offset = 0;
		}		
		_delay_ms(1);
		ms--;
	}
}

int main()
{
  DDRB = 0xff; // PORT B est en mode sortie
  uint8_t compteur = 0;

  for(;;)  // boucle sans fin
  {
	setColorDelay(0x1, 1000U);
	setColorDelay(0x2, 1000U);
	setColorDelay(0x3, 1000U);
  }
  return 0; 
}

