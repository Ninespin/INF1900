/* Table des états
 * État | btn | lstBtn | État suiv. | DEL (sortie)
 * -----------------------------------------------
 *   A  |  0  |    0   |      A     |    rouge
 *   A  |  1  |    0   |      B     |    ambre
 *   A  |  1  |    1   |      A     |    rouge
 *   A  |  0  |    1   |      D     |  	 éteint
 *   B  |  1  |    1   |      B     |    ambre
 *   B  |  0  |    1   |      C     |    vert
 *   C  |  0  |    0   |      C     |    vert
 *   C  |  1  |    0   |      A     |    rouge
 *   C  |  1  |    1   |      C     |    vert
 *   C  |  0  |    1   |      A     |    rouge
 *   D  |  0  |    0   |      D     |    éteint
 *   D  |  0  |    1   |      A     |    rouge
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "button.h"

enum State {RED, AMBER, GREEN, OFF};



int main(){
	DDRB = 0xff;
	DDRD = 0x0;

	Button btn = Button(0x04, 100);

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
