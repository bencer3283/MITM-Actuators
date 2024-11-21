String speed = "0";
bool isForward = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  speed.reserve(5);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    speed = Serial.readString();
    if (speed.toInt() >= 150) {
      isForward = true;
      // Serial.println(potpos);
      while (isForward) {
        // if (Serial.available()) {
        //   speed = Serial.readString();
        // }
        int potpos = analogRead(A0);
        if (potpos > 980) {
          // Serial.println("Forward_end");
          while (analogRead(A0) >= 980) {
            analogWrite(A2, speed.toInt());
            analogWrite(A3, 0);
          }
          isForward = false;
        }
        else {
          // Serial.println("Forward");
          analogWrite(A3, speed.toInt());
          analogWrite(A2, 0);
        }
        
      } 
      while(!isForward) {
        // if (Serial.available()) {
        //   speed = Serial.readString();
        // }
        int potpos = analogRead(A0);
        if (potpos < 50) {
          // Serial.println("Backward_end");
          while (analogRead(A0) <= 50) {
            analogWrite(A3, speed.toInt());
            analogWrite(A2, 0);
          }
          isForward = true;
          analogWrite(A3, 0);
          analogWrite(A2, 0);
          Serial.println("done");
        }
        else {
          // Serial.println("Backward");
          analogWrite(A2, speed.toInt());
          analogWrite(A3, 0);
        }
      }
      speed = "0";
    }
  }
  
}
