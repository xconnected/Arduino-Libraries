#include <Arduino.h>
#include <TSwitch.h>

// ---------------------------------------------------------------------------
// Create a Switch Object on PIN 4 with default settings: PULLUP, 20ms debounce
TSwitch Button = TSwitch(4); 

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

  // Test and debounce switch
  Button.run();  

  if ( Button.hasChanged() ) {
    Serial.print("switch operated ");
	Serial.print("Mode := ");
	Serial.println(Button.get());
  }

}

