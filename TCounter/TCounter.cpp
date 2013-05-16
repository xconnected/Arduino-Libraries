#include "TCounter.h"

// ---------------------------------------------------------------------------
TCounter::TCounter(int value, int step, int minVal, int maxVal, Mode_t mode) {
	init(value, step, minVal, maxVal, mode);
}

// ---------------------------------------------------------------------------
void TCounter::init(int value, int step, int minVal, int maxVal, Mode_t mode) {
  _value    = value;
  _step     = step;
  _min      = minVal;
  _max      = maxVal;
  _mode     = mode;
  _signal   = 0;
};

// ---------------------------------------------------------------------------
int  TCounter::getValue() {
  return _value; 
};

// ---------------------------------------------------------------------------
char TCounter::getSignal() {
  return _signal; 
};
// ---------------------------------------------------------------------------
void TCounter::setValue(int value) { 
  _value = value; 
};

// ---------------------------------------------------------------------------
void TCounter::setStep(int value) { 
  _step = value;
}

// ---------------------------------------------------------------------------
void TCounter::setMin(int value) { 
  _min = value; 
}

// ---------------------------------------------------------------------------
void TCounter::setMax(int value) { 
  _max = value; 
}

// ---------------------------------------------------------------------------
char TCounter::increment() {
  doUpdate();
  return _signal;
}

// ---------------------------------------------------------------------------
char TCounter::decrement() {
  _step  = -_step;
  doUpdate();
  _step  = -_step;
  return _signal;
};

// ---------------------------------------------------------------------------
void TCounter::doUpdate() {

  _signal = 0;

  switch(_mode) {
    case TCounter::UPDOWN:
      doUpDown();
      break;

    case TCounter::CYCLER:
      doCycler();
      break;
      
    default:
      break;
  }
};

// ---------------------------------------------------------------------------
void TCounter::doUpDown() {
           
  _value += _step;      
      
  if ( _value > _max ) {
    _value   = _max;
    _step = -_step;
    _signal = 1;
  }
  else if ( _value < _min ) {
    _value   = _min;
    _step = -_step;
    _signal = 1;
  }
};

// ---------------------------------------------------------------------------
void TCounter::doCycler() {
           
  _value += _step;      

  if ( _value > _max ) {
    _value  = _min;
    _signal = 1;  
  }
  else if ( _value < _min ) {
    _value  = _max;
    _signal = 1;  
  }
};

