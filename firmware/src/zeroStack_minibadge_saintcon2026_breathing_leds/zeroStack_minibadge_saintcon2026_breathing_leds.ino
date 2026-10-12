/*
  ZeroStack Labs - SAINTCON 2026 MiniBadge Firmware

  Author:
    Robby Wideman / TH3R0BH0G
    Email: kj6gcs@gmail.com

  Project:
    ZeroStack Labs SAINTCON 2026 MiniBadge
  
  Repository:
    https://github.com/ZeroStack-Labs/saintcon-2026-minibadge

  Websites:
    https://zerostacklabs.dev
    https://www.youtube.com/@zerostacklabs10

  Development Note:
    This firmware and the associated hardware project were developed as a
    hands-on learning project with the assistance of AI tools, specifically
    ChatGPT. AI was used to help explain concepts, review design decisions,
    troubleshoot issues, and assist with code development while the project
    was being built and tested.

    This project is provided for educational and experimental purposes.
    Although reasonable effort has been made to test and validate the design,
    neither the firmware nor the hardware is guaranteed to be free of errors
    or suitable for any particular application.

    The overall license included with the above-mentioned GitHub repo must
    be followed regarding both the overall project and including this
    specific code.  Please reach out to me with any questions, tips,
    tricks, etc.

    Build, modify, and use this project at your own risk.

  Build | Break | Learn | Repeat
*/

#include <Arduino.h>
#include <math.h>

// Associate LED1 with PA1 and LED2 with PA2.
const int LED1 = PIN_PA1;
const int LED2 = PIN_PA2;

// Set PWM brightness range.
const int MIN_BRIGHTNESS = 80;
const int MAX_BRIGHTNESS = 255;

// Track our current position in the breathing waveform.
float angle = 0.0;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
// Generate two sine waves 180 degrees out of phase from one another.
// This way the LED's will seem to breathe side-to-side during the cycle.
  float wave1 = (sin(angle) + 1.0) / 2.0;
  float wave2 = (sin(angle + PI) + 1.0) / 2.0;

// Convert wave1 from 0.0-1.0 into our LED brightness range
  int brightness1 =
    MIN_BRIGHTNESS +
    wave1 * (MAX_BRIGHTNESS - MIN_BRIGHTNESS);

// Convert wave2 from 0.0-1.0 into the LED brightness range.  
  int brightness2 =
    MIN_BRIGHTNESS +
    wave2 * (MAX_BRIGHTNESS - MIN_BRIGHTNESS);

// Apply the calculated PWM brightness to each LED.
  analogWrite(LED1, brightness1);
  analogWrite(LED2, brightness2);

// Move breathing animation forward.
// 0.03 is our starting speed and can be adjusted later if needed.
  angle += 0.03;

// Wrap the angle after one full sine-wave cycle.
  if (angle >= TWO_PI) {
    angle -= TWO_PI;
  }

// Pause loop for 15 milliseconds, then loop again.
  delay(15);
}