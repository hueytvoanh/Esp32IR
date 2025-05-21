//our library

#include "irremote.h"

void setup() {

  //small delay for proper power up

  delay(150);

  Serial.begin(115200);//debug

  IR_setup();

}

void loop() {

  IR_loop();

}
