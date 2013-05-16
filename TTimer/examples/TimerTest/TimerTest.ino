#include <Arduino.h>
#include <TTimer.h>

// ---------------------------------------------------------------------------

TTimer timer(1000, &TimerAdapter);

// ---------------------------------------------------------------------------
int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

// ---------------------------------------------------------------------------

void TimerAdapter() {
  Serial.print("Timer expired after ");
  Serial.print(timer.getTime());
  Serial.println("ms ");  
}

// ---------------------------------------------------------------------------
void setup() {
  
  delay(500);
  Serial.begin(38400);
  Serial.print("Start with free RAM of ");
  Serial.println(freeRam());
}

// ---------------------------------------------------------------------------

void loop() { 

  timer.run();
}

