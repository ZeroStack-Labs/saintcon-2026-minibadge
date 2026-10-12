#include <math.h>

const int LED1 = 9;
const int LED2 = 10;

const int MIN_BRIGHTNESS = 80;
const int MAX_BRIGHTNESS = 255;

float angle = 0.0;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  float wave1 = (sin(angle) + 1.0) / 2.0;
  float wave2 = (sin(angle + PI) + 1.0) / 2.0;

  int brightness1 =
      MIN_BRIGHTNESS +
      wave1 * (MAX_BRIGHTNESS - MIN_BRIGHTNESS);

  int brightness2 =
      MIN_BRIGHTNESS +
      wave2 * (MAX_BRIGHTNESS - MIN_BRIGHTNESS);

  analogWrite(LED1, brightness1);
  analogWrite(LED2, brightness2);

  angle += 0.03;

  if (angle >= TWO_PI) {
    angle -= TWO_PI;
  }

  delay(15);
}