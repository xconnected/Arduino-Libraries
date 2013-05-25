#ifndef _TSWITCH_H_
#define _TSWITCH_H_

#define PULLUP   HIGH
#define PULLDOWN LOW

#define _SWITCH_OFF_       0
#define _SWITCH_ON_        1
#define _SWITCH_SHORT_     2
#define _SWITCH_LONG_      4
#define _SWITCH_CHANGE_    8
#define _SWITCH_STABLE_    16

#define _SWITCH_MS_LONG_   3000
#define _SWITCH_MS_SHORT_  250

class TSwitch {

  private:
    uint8_t 	  _pin;            	// CPU Pin of button
    uint8_t 	  _mode;           	// PULLUP or PULLDOWN mode
	uint8_t 	  _state;          	// State
	unsigned int  _debounceTime;   	// Config for number of ms debouncing delay
    int     	  _lastPinRead; 	// pin status last time the pin was read
	unsigned long _toggledAt;	  	// last time the pin changed
    unsigned long _elapsedA;	 	// last time the switch was stable
	unsigned long _elapsedB;	 	// prior last time the switch was stable	

  public:
	// Constructor with Initialize timer
    TSwitch(uint8_t pin, uint8_t mode = PULLUP, unsigned int debounceTime=20);

	// Run single debounce cycle - returns full state
    uint8_t poll();
	
	// Signals if there was a change since last read - destructive read
    uint8_t hasChanged();
	
	// Signals if the last transition was long
    uint8_t wasLong();

	// Signals if the last transition was fast
    uint8_t wasShort();
	
	// Returns the current state with all flags
    uint8_t getState();
	
	// Returns the switch state
    uint8_t get();
};

#endif
