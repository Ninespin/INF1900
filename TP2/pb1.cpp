#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "button.h"

// ENUMS
enum class STATES{
	INIT = 0,
	BTN_PRESSED,
	BTN_RELEASED,
	LIGHT_ON
};
<<<<<<< HEAD


enum class LED_COLORS {
=======
enum LED_COLORSW{
>>>>>>> 173f2f90149436ead0edcf48109893b20700ded0
	OFF = 0x00,
	RED = 0x01,
	GREEN = 0x02
};


// GLOBALS
unsigned int pressCounter = 0;
STATES currentState = STATES::INIT;

// BUTTON PRESS EVENT (ALSO A STATE)
int bPressed(){
	currentState = STATES::BTN_PRESSED;	
	return 0;
}

// BUTTON RELEASED EVENT (ALSO A STATE)
int bReleased(){
	pressCounter++;
	currentState = STATES::BTN_RELEASED;
	return 0;
}

int init(){
	PORTB = OFF;
	pressCounter = 0;
	return 0;
}



// MAIN
int main(){
	DDRB = 0xFF;
	DDRD = 0x00;
	PORTB = OFF;
	currentState = STATES::INIT;

	Button btn = Button(0x04, 100);
	btn.btnPressed = &bPressed;
	btn.btnReleased = &bReleased;
	
	while(1){
		btn.debounce();
		switch(currentState){
			case STATES::INIT:
				init();
				break;
			case STATES::BTN_PRESSED:
				break;
			case STATES::BTN_RELEASED:
				if(pressCounter >= 5){
					currentState = STATES::LIGHT_ON;
				}
				break;
			case STATES::LIGHT_ON:
				PORTB = RED;
				_delay_ms(1000); // 1000 - dt
				currentState = STATES::INIT;
				break;			
		}

		
		_delay_ms(10); // dt
\
	}	

	return 0;
}
