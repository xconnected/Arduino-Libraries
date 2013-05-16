#include <Arduino.h>
#include <limits.h>
#include <TTimer.h>

// ---------------------------------------------------------------------------
TTimer::TTimer() {
  clear();
}

// ---------------------------------------------------------------------------
TTimer::TTimer(unsigned long time, void (*callback)()) {
  init(time, callback);
}

// ---------------------------------------------------------------------------
TTimer::TTimer(unsigned long time, int cycl, void (*callback)()) {
  init(time, cycl, callback);
}

// ---------------------------------------------------------------------------
void TTimer::init(unsigned long time, int cycl, void (*callback)()) {
  clear();
  _callback = callback;  
  _time = time;
  _cycl = cycl;
  _trig = millis();    
  _mode = RUN;
} 

// ---------------------------------------------------------------------------
void TTimer::init(unsigned long time, void (*callback)()) {
  init(time, -1, callback);
}

// ---------------------------------------------------------------------------
void TTimer::reset() {
  if (_mode == RUN) _trig = millis();
}

// ---------------------------------------------------------------------------
void TTimer::clear(){
  _callback = NULL;  
  _mode     = CLEAR;
}

// ---------------------------------------------------------------------------
void TTimer::enable() {
  if (_mode != CLEAR) {
    _trig = millis();
    _mode = RUN;
  }
}

// ---------------------------------------------------------------------------
void TTimer::disable() {
  if (_mode != CLEAR) _mode = STOP;
}

// ---------------------------------------------------------------------------     
void TTimer::setTime(unsigned long time) {
  _time = time; 
}

// ---------------------------------------------------------------------------
void TTimer::setCycles(int cycles) { 
  _cycl = cycles;
}

// ---------------------------------------------------------------------------
TTimer::Mode_t TTimer::getMode() { 
  return _mode;
}

// ---------------------------------------------------------------------------
int TTimer::run() {
  return run(millis());
}

// ---------------------------------------------------------------------------
int TTimer::run(unsigned long now) {
 
  _signal = 0;

  // If current timer is inactive proceed to the next
  if (_mode != RUN) return _signal;

  // Determine the elapsed time since trigger
  long elapsed = now - _trig;
  
  // if there was an overrun in the time - recover the calculation 
  if ( elapsed < 0 ) elapsed = ULONG_MAX + elapsed;
  
  // if timer is not expired proceed to the next
  if (( (unsigned long)(elapsed)) < _time) return _signal;
  
  // the timer expired, set a flag 
  _signal = 1;
  
  // trigger call back function if defined
  if (_callback != NULL) _callback();
  
  // Restart timer if required
  if ( _cycl < 0 ) {
    _trig = now;
  } 
  // Repeat timer    
  else if ( _cycl >  0 ) {
    _cycl--;
    _trig = now;
  }  
  // Halt timer    
  else if ( _cycl == 0 ) {
    _mode = HALT;
  }
      
  return _signal;
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

TTimerCollection::TTimerCollection() {
  for (int i=0; i < _TIMER_COLLECTION_SIZE_; i++) remove(i);
}

// ---------------------------------------------------------------------------
void TTimerCollection::remove(unsigned char ix) {
  ix = constrain(ix, 0, _TIMER_COLLECTION_SIZE_ - 1);
  pTimers[ix] = NULL;
}

// ---------------------------------------------------------------------------
TTimer* TTimerCollection::set(unsigned char ix, TTimer* pTimer) {
  ix = constrain(ix, 0, _TIMER_COLLECTION_SIZE_ - 1);
  pTimers[ix] = pTimer;
  return pTimers[ix];
}

// ---------------------------------------------------------------------------
TTimer* TTimerCollection::get(unsigned char ix) {
  ix = constrain(ix, 0, _TIMER_COLLECTION_SIZE_ - 1);
  return pTimers[ix];
}

// ---------------------------------------------------------------------------
void TTimerCollection::disableAll() {
  for (int i=0; i < _TIMER_COLLECTION_SIZE_; i++) {
    if (pTimers[i] != NULL) pTimers[i]->disable();
  }
}

// ---------------------------------------------------------------------------
void TTimerCollection::enableAll() {
  for (int i=0; i < _TIMER_COLLECTION_SIZE_; i++) {
    if (pTimers[i] != NULL) pTimers[i]->enable();
  }
}

// ---------------------------------------------------------------------------
void TTimerCollection::runAll() {
  for (int i=0; i < _TIMER_COLLECTION_SIZE_; i++) {
    if (pTimers[i] != NULL) pTimers[i]->run();
  }
}

// ------------------------------------