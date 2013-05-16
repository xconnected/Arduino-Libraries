#include <Arduino.h>
#include <TCounter.h>

// ---------------------------------------------------------------------------

TCounter Counter(10, 1, 0, 100, TCounter::UPDOWN);

// ---------------------------------------------------------------------------
int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
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
  delay(200);
  Counter.increment();
  Serial.print("Counter Value ");
  Serial.print(Counter.getValue());
  Serial.print(" Signal: ");  
  Serial.print(Counter.getSignal());
  Serial.println();  
}

