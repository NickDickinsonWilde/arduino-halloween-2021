/*
 * Halloween 2021 NecroDeer script.
 *
 * Set distance on push of button.
 *
 * After initialized, if someone is in distance, start lights.
 *
 */

// the pins connected to the Ultrasonic sensor
int pinEcho = 4;
int pinTrigger = 5;

// Button pin
int pinButton = 2;

// Light pins
int pinLightLeft = 6;
int pinLightRight = 7;

float distanceTolerance = 10;

// -1 means distance hasn't been set.
float distanceBase = -1;

// Get the distance in centimeters.
float getDistance()
{
    int pulseLenMicroseconds;

    // bit-bang a small square wave
    // on the trig pin to start the range
    // finder
    digitalWrite(pinTrigger, LOW);
    delayMicroseconds(20);
    digitalWrite(pinTrigger, HIGH);
    delayMicroseconds(100);
    digitalWrite(pinTrigger, LOW);

    // measure the pulse length from the echo pin
    pulseLenMicroseconds = pulseIn(pinEcho, HIGH);

    // calculate the distance using the speed of sound
    return pulseLenMicroseconds / 29.387 / 2;
}

void setup()
{
    // set up serial
    Serial.begin(9600);

    // set the pinmode on our ultrasonic echo, and tric pins
    pinMode(pinEcho, INPUT);
    pinMode(pinTrigger, OUTPUT);

    pinMode(pinButton, INPUT_PULLUP);

    pinMode(pinLightLeft, OUTPUT);
    pinMode(pinLightRight, OUTPUT);
}

void lightUp() {
  digitalWrite(pinLightLeft, HIGH);
  digitalWrite(pinLightRight, HIGH);
  delay(100);
  flickerBoth();
  flickerRight();
  flickerLeft();
  flickerBoth();
  flickerRight();
  flickerBoth();
  flickerLeft();
  delay(1000);
  flickerBoth();
  flickerRight();
  flickerLeft();
  delay(1000);
  digitalWrite(pinLightLeft, LOW);
  digitalWrite(pinLightRight, LOW);
}

void flickerBoth() {
  digitalWrite(pinLightLeft, LOW);
  digitalWrite(pinLightRight, LOW);
  delay(50);
  digitalWrite(pinLightLeft, HIGH);
  digitalWrite(pinLightRight, HIGH);
  delay(100);
}

void flickerLeft() {
  digitalWrite(pinLightLeft, LOW);
  delay(50);
  digitalWrite(pinLightLeft, HIGH);
  delay(100);
}

void flickerRight() {
  digitalWrite(pinLightRight, LOW);
  delay(50);
  digitalWrite(pinLightRight, HIGH);
  delay(100);
}

void loop()
{
    float distance;

    distance = getDistance();

    // if the button is pressed, set the distance to the last
    // distance read
    if (digitalRead(pinButton) == LOW)
    {
        distanceBase = distance;
    }

    if (distanceTolerance != -1) {
      if (distance < distanceBase - distanceTolerance ) {
        lightUp();
      }
    }
    delay(300);
}
