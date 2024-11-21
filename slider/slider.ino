String speed = "0";
bool isForward = true;

#define IN1 10
#define IN2 9
#define IN3 8
#define IN4 7
int Steps = 0;
boolean Direction = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  speed.reserve(5);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    speed = Serial.readString();
    int speedInt = speed.toInt();
    // Serial.println(speedInt);
    if (speedInt >= 150) {
      isForward = true;
      // Serial.println(potpos);
      while (isForward) {
        // if (Serial.available()) {
        //   speed = Serial.readString();
        // }
        int potpos = analogRead(A0);
        if (potpos > 950) {
          // Serial.println("Forward_end");
          while (analogRead(A0) >= 950) {
            analogWrite(A2, speedInt);
            analogWrite(A3, 0);
          }
          isForward = false;
        }
        else {
          // Serial.println("Forward");
          int touch = digitalRead(2);
          // Serial.println(touch);
          if (touch == 0) {
            analogWrite(A3, speedInt);
            analogWrite(A2, 0);
          } else {
            analogWrite(A3, 0);
            analogWrite(A2, 0);
          }
          
        }
        
      } 
      while(!isForward) {
        // if (Serial.available()) {
        //   speed = Serial.readString();
        // }
        int potpos = analogRead(A0);
        if (potpos < 90) {
          // Serial.println("Backward_end");
          while (analogRead(A0) <= 90) {
            analogWrite(A3, speedInt);
            analogWrite(A2, 0);
          }
          isForward = true;
          analogWrite(A3, 0);
          analogWrite(A2, 0);
          Serial.println("done");
        }
        else {
          // Serial.println("Backward");
          int touch = digitalRead(2);
          // Serial.println(touch);
          if (touch == 0) {
            analogWrite(A2, speedInt);
            analogWrite(A3, 0);
          } else {
            analogWrite(A3, 0);
            analogWrite(A2, 0);
          }
        }
      }
      for(int i=0; i<1250*speedInt/250+2500; i++){
        stepper(1);
        delayMicroseconds(1000);
      }
      speed = "0";
    }
  }
  
}

void stepper(int xw) {
for (int x = 0; x < xw; x++) {
switch (Steps) {
case 0:
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
break;
case 1:
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, HIGH);
break;
case 2:
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
break;
case 3:
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
break;
case 4:
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
break;
case 5:
digitalWrite(IN1, HIGH);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
break;
case 6:
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
break;
case 7:
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
break;
default:
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
break;
}
SetDirection();
}
}
void SetDirection() {
if (Direction == 1) {
Steps++;
}
if (Direction == 0) {
Steps--;
}
if (Steps > 7) {
Steps = 0;
}
if (Steps < 0) {
Steps = 7;
}
}
