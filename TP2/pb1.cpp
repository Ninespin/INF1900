#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "button.h"

enum class STATES{
	INIT,
	BTN_PRESSED,
	BTN_RELEASED,
	LIGHT_ON
};


enum class LED_COLORS {
	OFF = 0x00;
	RED = 0x01;
	GREEN = 0x02;
};


// GLOBALS
unsigned int pressCounter = 0;

// BUTTON PRESS EVENT
int bPressed(){
	
	return 0;
}

// BUTTON RELEASED EVENT
int bReleased(){
	PORTB = LED_COLORS::OFF;
	return 0;
}

int init(){
	
}



// MAIN
int main(){
	DDRB = 0xFF;
	DDRD = 0x00;
	PORTB = LED_COLORS::OFF;


	Button btn = Button(0x04, 100);
	btn.btnPressed = &bPressed;
	btn.btnReleased = &bReleased;
	
	while(1){
		btn.debounce();

		
		_delay_ms(10);
	}	

	return 0;
}
