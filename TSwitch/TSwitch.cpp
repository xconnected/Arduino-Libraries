#include <Arduino.h>
#include <limits.h>
#include <TSwitch.h>
// ---------------------------------------------------------------------------
TSwitch::TSwitch(uint8_t pin, uint8_t mode, unsigned int debounceTime) {
  
  _pin            = pin;
  _mode           = mode;
  _debounceTime   = debounceTime;

  _state          = (_lastPinRead != _mode) ? _SWITCH_ON_:_SWITCH_OFF_;
  _lastPinRead    = digitalRead(_pin);
  _toggledAt	  = millis();
  
  if (_mode == PULLUP) {
    digitalWrite(_pin, HIGH);
  }
  else {
    digitalWrite(_pin, LOW);
  }
}

// ---------------------------------------------------------------------------
boolean TSwitch::hasChanged() {

  boolean changeFlag = _state & _SWITCH_CHANGE_;
  
  // Delete change flag as it has been read
  _state &= ~_SWITCH_CHANGE_;
  
  return changeFlag;
}
// ---------------------------------------------------------------------------  
uint8_t TSwitch::getState() { 
	return _state; 
}; 

// ---------------------------------------------------------------------------  
uint8_t TSwitch::get() { 
	return _state & _SWITCH_ON_; 
}; 

// ---------------------------------------------------------------------------  
uint8_t TSwitch::wasLong() { 
	return (_state & _SWITCH_LONG_)?1:0; 
}; 

// ---------------------------------------------------------------------------  
uint8_t TSwitch::wasShort() { 
	return (_state & _SWITCH_SHORT_)?1:0; 	
}; 
// ---------------------------------------------------------------------------  
uint8_t TSwitch::poll() {
  
  unsigned long now = millis();
  
  // read pin
  int pinRead = digitalRead(_pin);  
  
  // If a change occurred start debouncing 
  if ( pinRead != _lastPinRead ) {
    // Delete change and stable flag
	_state       &= ~(_SWITCH_CHANGE_ | _SWITCH_STABLE_);
	
	// Maintain current state to handle debouncing
	_lastPinRead  = pinRead;	
	_toggledAt	  = now;
  }
  else if ( (_state & _SWITCH_STABLE_) == 0 ) {
    // If debounce time passed without a change the switch is stable
    if ( (now - _toggledAt) >= _debounceTime ) {

	  // Identify state
      _state  =  (_lastPinRead != _mode) ? _SWITCH_ON_:_SWITCH_OFF_; 
	  _state |=  _SWITCH_CHANGE_ | _SWITCH_STABLE_ ;

	  // Identify double and long presses
	  if (now - _elapsedA > _SWITCH_MS_LONG_  ) _state |= _SWITCH_LONG_;
	  if (now - _elapsedB <  _SWITCH_MS_SHORT_) _state |= _SWITCH_SHORT_;
	  
	  // Shift elapsed time 
	  _elapsedB = _elapsedA;
	  _elapsedA = now;
	  	  
	  // Save current time to later determine the stable duration 
	  _toggledAt = now;
    }
  }
  
  return _state;
}
