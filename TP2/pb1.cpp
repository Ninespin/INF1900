#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>





//INT BTNPRESS


class Btn{
public:
	Btn()
		: state(false)
		, lastState(false)
		, debounceCounter(0)
		, pin(0x04)
		, debounceCounterThreshold(10)
	{
	}

	inline bool isPressed(){
		return true;//((lastState = state), (state = PIND & pin), state); 
	}	

	int debounce(){
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
			PORTB = 0x01;
		}
		return 0;	
	}	


private:
	const unsigned int pin;
	const unsigned int debounceCounterThreshold;
	unsigned int debounceCounter;
	
public:
	int (*btnPressed)();
	int (*btnReleased)();
	bool state;
	bool lastState;
 
	
};


int bPressed(){
	PORTB = 0x02; // TODO set proper bit
	return 0;
}
int bReleased(){
	PORTB - 0x00;
	return 0;
}

int main(){
	DDRB = 0xFF;
	DDRD = 0x00;
	PORTB= 0x01;

	Btn btn = Btn();
	btn.btnPressed = &bPressed;
	btn.btnReleased = &bReleased;
	
	while(1){
		btn.debounce();
		_delay_ms(10);
	}	

	return 0;
}
