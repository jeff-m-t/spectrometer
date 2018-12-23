#define encoder0PinA  2
#define encoder0PinB  3

volatile int encoder0Pos = 0;
int previousEncoder0Pos = 0;
int smallGearTeeth = 30;
int bigGearTeeth = 180;
float anglePerStep = 360.0/2400 * smallGearTeeth / bigGearTeeth;
int incomingByte = 0;

void setup() {
  pinMode(encoder0PinA, INPUT);
  pinMode(encoder0PinB, INPUT);

  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderA, CHANGE);

  // encoder pin on interrupt 1 (pin 3)
  attachInterrupt(1, doEncoderB, CHANGE);

  Serial.begin (9600);
}

void loop() {
  if(encoder0Pos != previousEncoder0Pos) {
    // Serial.println (encoder0Pos * anglePerStep);
    previousEncoder0Pos = encoder0Pos;
  }

  if (Serial.available() > 0) {
    incomingByte = Serial.read();

    if (incomingByte == 122) {
      encoder0Pos = 0;
    }

    if (incomingByte == 97) {
      Serial.println(encoder0Pos * anglePerStep);
    }
  }
  delay(100);
}

void doEncoderA() {
  // look for a low-to-high on channel A
  if (digitalRead(encoder0PinA) == HIGH) {

    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos = encoder0Pos + 1;         // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  else {   // must be a high-to-low edge on channel A
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == HIGH) {
      encoder0Pos = encoder0Pos + 1;          // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
}

void doEncoderB() {
  // look for a low-to-high on channel B
    if (digitalRead(encoder0PinB) == HIGH) {

    // check channel A to see which way encoder is turning
    if (digitalRead(encoder0PinA) == HIGH) {
      encoder0Pos = encoder0Pos + 1;         // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinA) == LOW) {
      encoder0Pos = encoder0Pos + 1;          // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
}
				    