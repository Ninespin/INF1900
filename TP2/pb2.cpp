#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


enum State {EA, EB, EC, ED};



int main(){
	DDRB = 0xff;
	DDRD = 0x0;
	bool lstBtn = 0;
	bool btnPressed = 0;

	State state = EA;

	for(;;) {
		_delay_ms(1);

		if(PIND & 0x04){
			btnPressed = 1;
		} else {
			btnPressed = 0;
		}

		switch(state) {
			case EA :
				PORTB = 0x1;
				if(btnPressed != lstBtn && btnPressed) {
					state = EB;
				} else if(btnPressed != lstBtn && !btnPressed) {
					state = ED;
				}
				break;
			case EB :
				while(PIND & 0x04) {
					if(PORTB == 0x1){
						PORTB = 0x2;
					} else{
						PORTB = 0x1;
					}
				}

				if(btnPressed != lstBtn && !btnPressed) {
					state = EC;
				}
				break;
			case EC :

				PORTB = 0x2;
				if(btnPressed != lstBtn) {
					state = EA;
				}
				break;
			case ED :
				PORTB = 0x0;
				if(btnPressed != lstBtn && btnPressed) {
					state = EC;
				}
				break;
			default :
				break;
		}

		lstBtn = btnPressed;
	}

	return 0;
}
