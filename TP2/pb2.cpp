#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "button.h"

enum State {RED, AMBER, GREEN, OFF};



int main(){
	DDRB = 0xff;
	DDRD = 0x0;

	bool lstBtn = 0;
	bool btnPressed = 0;

	State state = RED;

	for(;;) {
		_delay_ms(10);

		if(PIND & 0x04){
			btnPressed = 1;
		} else {
			btnPressed = 0;
		}

		switch(state) {
			case RED :
				PORTB = 0x1;
				if(btnPressed != lstBtn && btnPressed) {
					state = AMBER;
				} else if(btnPressed != lstBtn && !btnPressed) {
					state = OFF;
				}
				break;
			case AMBER :
				while(PIND & 0x04) {
					if(PORTB == 0x1){
						PORTB = 0x2;
					} else{
						PORTB = 0x1;
					}
				}

				if(btnPressed != lstBtn && !btnPressed) {
					state = GREEN;
				}
				break;
			case GREEN :

				PORTB = 0x2;
				if(btnPressed != lstBtn) {
					state = RED;
				}
				break;
			case OFF :
				PORTB = 0x0;
				if(btnPressed != lstBtn && btnPressed) {
					state = GREEN;
				}
				break;
			default :
				break;
		}

		lstBtn = btnPressed;
	}

	return 0;
}
