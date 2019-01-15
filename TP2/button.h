#ifndef BUTTON_H
#define BUTTON_H

class Button{
	bool isPressed();
	  

public:
	Button(const unsigned int t_pin = 0x04, const unsigned int t_debThres = 100 );
	int debounce();
	inline bool getState() const;
	inline bool getLastState() const;


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

#endif
