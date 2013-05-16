#ifndef _TSWITCH_H_
#define _TSWITCH_H_

#define PULLUP   HIGH
#define PULLDOWN LOW

class TSwitch {

  private:
    enum _state_t { DEBOUNCE, STABLE } _state;

    uint8_t _pin;            // CPU Pin of button
    uint8_t _mode;           // PULLUP or PULLDOWN mode
    boolean _changed;        // change indicator
    boolean _switched;       // button status
    int     _lastPinRead;    // pin status last time the pin was read
    int     _debounceTime;   // Config for number of ms debouncing delay
    unsigned long _toggleAt; // last time the pin changed

  public:
	// Default Constructor 
	TSwitch() { /* empty */ };
	// Constructor with Initialize timer
    TSwitch(int pin, uint8_t mode = PULLUP, int debounceTime=20);
	// Initialize timer
	void init(int pin, uint8_t mode = PULLUP, int debounceTime=20);
	// Run single debounce cycle - returns switch state
    uint8_t run();
	// Returns if the counter changed during the last cycle - destructive read
    uint8_t hasChanged();
	// Returns the counter current counter state
    boolean get()       { return _switched; };    
};

#endif
