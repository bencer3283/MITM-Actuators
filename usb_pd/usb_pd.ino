#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
  Serial.println("Serial begin");
  Wire.begin();
  Wire.requestFrom(0x28+0x06, 1);
  while(Wire.available()) {
    Serial.println("Something to read");
    u_int c = Wire.read();    // Receive a byte as character
    Serial.print(c);         // Print the character
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  Serial.println("Serial in loop");
}
