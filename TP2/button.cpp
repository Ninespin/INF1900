#include "button.h"
#include <avr/io.h>

bool Button::isPressed(){
	lastState = state;
	state = PIND & pin;
	return state;
}

Button::Button(const unsigned int t_pin, const unsigned int t_debThres )
	: state(false)
	, lastState(false)
	, debounceCounter(0)
	, pin(t_pin)
	, debounceCounterThreshold(t_debThres)
{
}

int Button::debounce(){
	if(isPressed() != lastState){
		// Rising edge			
		if(state){
			debounceCounter = 0;
		}else{ // Falling edge
			btnReleased();	
		}
	}
	
	if(state){
		debounceCounter++;
		if(debounceCounter >= debounceCounterThreshold){
			btnPressed();
		}
	}
	return 0;	
}	

inline bool Button::getState() const{
	return state;
}

inline bool Button::getLastState() const{
	return lastState;
}





