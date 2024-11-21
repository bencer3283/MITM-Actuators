void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(D0, OUTPUT);
}

int sample = 0;
bool touch = false;
void loop() {
  // put your main code here, to run repeatedly:
  int output = analogRead(A0);
  // Serial.println(reading / 50);
  if (output > 23) {
    touch = true;
  }
  sample++;
  if ( sample == 10 ) {
    sample = 0;
    Serial.println(touch);
    if (touch) {
      digitalWrite(D0, 1);
    } else {
      digitalWrite(D0, 0);
    }
    touch = false;
  }
  delay(10);
}
