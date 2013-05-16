#include <Arduino.h>
#include <limits.h>
#include <TSwitch.h>
// ---------------------------------------------------------------------------
TSwitch::TSwitch(int pin, uint8_t mode, int debounceTime) {
  init(pin, mode, debounceTime);
}

// ---------------------------------------------------------------------------
void TSwitch::init(int pin, uint8_t mode, int debounceTime) {

  _pin            = pin;
  _mode           = mode;  
  _state          = DEBOUNCE;
  _changed        = false;
  _switched       = false;
  _lastPinRead    = digitalRead(_pin);
  _debounceTime   = debounceTime;
  
  if (_mode == PULLUP) {
    digitalWrite(_pin, HIGH);
  }
  else {
    digitalWrite(_pin, LOW);
  }
}
// ---------------------------------------------------------------------------
boolean TSwitch::hasChanged() {

  boolean last = _changed;
  _changed = false;
  
  return last;
}
// ---------------------------------------------------------------------------  
boolean TSwitch::run() {

  // read time
  unsigned long now = millis();
  
  // read pin
  int pinRead = digitalRead(_pin);  

  if (pinRead != _lastPinRead) {
    // pin changed since last check
    _toggleAt = now;
    _state    = DEBOUNCE;
    _changed  = false;    
  }
  else if ( _state == DEBOUNCE ) {
    // Determine time left to go
    long stableSince = now - _toggleAt;
    
    // If time left is negative, the wrap around on millis() must be handled
    if ( stableSince < 0 ) stableSince = ULONG_MAX + stableSince;

    // If time has elapsed with no change the switch is stable
    if ( stableSince >= _debounceTime ) {
      _state    = STABLE;
      _changed  = true;
      _switched = (pinRead != _mode);      
    }
   }

  // Save current pin read
  _lastPinRead = pinRead;
  
  return _switched;
}
