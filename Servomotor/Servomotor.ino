 
 
#include <Servo.h>
 
Servo servo1;
 
void setup() {
  servo1.attach(4);
}

void loop() {
  servo1.write(90);    //ubicacion de los grados 
  delay(5000);
  servo1.write(0);    //ubicacion de los grados 
  delay(5000);
}
