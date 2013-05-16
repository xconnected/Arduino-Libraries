#ifndef _TTIMER_H_
#define _TTIMER_H_

#define _TIMER_COLLECTION_SIZE_ 1

class TTimer {
  public:
    enum Mode_t {STOP, RUN, HALT, CLEAR}; 
    
  private:
    unsigned char _signal;  
    unsigned long _lastTime;
    unsigned long _trig;    
    unsigned long _time;
    int           _cycl;    
    Mode_t        _mode;    
    void          (*_callback)();

  public:
    
    TTimer();
	// Constructor with setup - limited cycles/repetitions
	TTimer(unsigned long time, int rept, void (*callback)());
	// Constructor with setup - unlimited cycles/repetitions
	TTimer(unsigned long time, void (*callback)());	
	// Init timer with limited cycles/repetitions
    void init(unsigned long time, int rept, void (*callback)());
	// Init timer with unlimited cycles/repetitions
    void init(unsigned long time, void (*callback)());    
	// Set time 
    void setTime(unsigned long time);
	// Set cycles/repetitions
	unsigned long getTime() { return _time; };
	// Set cycles/repetitions
    void setCycles(int cycles);
	// Clear the timer
    void clear();
	// Reset a running timer
    void reset();
	// Enable timer
    void enable();
	// Disable but not clear timer
    void disable();
	// Process timer 
    int  run();
	// Process timer at a given time - returns signal !=0 means timer expired
    int  run(unsigned long now);
	// Returns current timer mode
    Mode_t getMode();    
};

// ---------------------------------------------------------------------------

class TTimerCollection {

  public:
    TTimerCollection();
    void enableAll();
    void disableAll(); 
    void runAll();
    void remove(unsigned char ix);		
    TTimer* set(unsigned char ix, TTimer* pTimer);
    TTimer* get(unsigned char ix);	
	
  private:
    unsigned char timerNum;
    TTimer *pTimers[_TIMER_COLLECTION_SIZE_]	;	
};
#endif
