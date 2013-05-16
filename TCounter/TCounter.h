#ifndef _TCOUNTER_H_
#define _TCOUNTER_H_

class TCounter {
  
  public:
    // Counter types
    enum Mode_t {FIXED, UPDOWN, CYCLER}; 
    
  private:
    char   _signal;
    int    _value;
    int    _step;
    int    _min;
    int    _max;
    Mode_t _mode;
    
	// Internal helper functions
    void doUpdate();
    void doUpDown();
    void doCycler();
    
  public:  
    TCounter() { /* empty default constructor */ };
	// Constructor with setup 
	TCounter(int value, int step, int min, int max, Mode_t mode);
	// Setup the counter
    void init(int value, int step, int min, int max, Mode_t mode);
	// Get actual counter value
    int getValue();
	// Read signal - counter reached one limit
    char getSignal();
	// Override current counter value
    void setValue(int value);
	// Adjust counter steps
    void setStep(int value);
	// Adjust counter min
    void setMin(int value);
	// Adjust counter max
    void setMax(int value);
	// Increment counter
    char increment();
	// Decrement counter
    char decrement();
};

#endif
