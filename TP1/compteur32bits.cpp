#define F_CPU 8000000UL
#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>



// CONTROLE DEL
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

int mainControleDEL()
{
  DDRB = 0xff; // PORT B est en mode sortie

  for(;;)  // boucle sans fin
  {
	setColorDelay(0x1, 1000U);
	setColorDelay(0x2, 1000U);
	setColorDelay(0x3, 1000U);
  }
  return 0; 
}



int mainInterrupt(){
	DDRD = 0x00;
	DDRB = 0xFF;

	bool lastBtn = 0;
	bool btn = 0;
	while(1){
		btn = PIND & 0x04;

		if(btn){
			if(PORTB & 0x01){
				PORTB = (PORTB & 0xFC) | 0x02;
			}else if(PORTB & 0x02){
				PORTB = (PORTB & 0xFC) | 0x01;
			}else{
				PORTB = (PORTB & 0xFC) | 0x01;
			}
		}

		if(lastBtn && !btn){		
			PORTB = 0x00;
		}

		lastBtn = btn;
	}
	
	return 0;
}




int main(){
	return mainInterrupt();

}






