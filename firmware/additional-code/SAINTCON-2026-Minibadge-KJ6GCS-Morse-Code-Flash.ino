
/*
  ZeroStack Labs - SAINTCON 2026 MiniBadge
  Callsign: KJ6GCS
  Morse: -.- .--- -.... --. -.-. ...

  Phase 1: Both LEDs transmit slowly together
  Phase 2: 4-second pause
  Phase 3: D2 and D3 alternate flashing same
            callsign, but *faster*

  AI Advisement: This code was written with
  the assistance of Artificial Intelligence (AI),
  specifically OpenAI's ChatGPT.

  D2 = PA1
  D3 = PA2

  Build | Break | Learn | Repeat
*/

// =======================================
// LED PINS
// =======================================

const uint8_t LED_D2 = PIN_PA1;
const uint8_t LED_D3 = PIN_PA2;

// =======================================
// USER SETTINGS
// =======================================

// Original slow Morse settings
const uint16_t SLOW_DOT_MS = 50;
const uint8_t SLOW_DASH_MULT = 4;
const uint8_t SLOW_LETTER_GAP = 8;

// Fast Morse settings (~35 WPM)
const uint16_t FAST_DOT_MS = 17;
const uint8_t FAST_DASH_MULT = 3;
const uint8_t FAST_LETTER_GAP = 1.5;

// Number of rounds:
// D2 once + D3 once = 1 round
const uint8_t FAST_ROUNDS = 5;

// Pause between slow and fast sequences
const uint32_t PHASE_PAUSE_MS = 250;

// Gap between rapid transmissions
const uint16_t FAST_REPEAT_GAP_MS = 240;

// Callsign
const char MORSE[] =
  "-.- .--- -.... --. -.-. ...";

// =======================================
// ANIMATION STATES
// =======================================

enum Mode {
  SLOW_MORSE,
  PAUSE_BEFORE_FAST,
  FAST_MORSE,
  FAST_GAP,
  PAUSE_BEFORE_RESTART
};

Mode currentMode = SLOW_MORSE;

unsigned long phaseStart = 0;

// Morse engine state
uint8_t morseIndex = 0;
bool morseOn = false;
unsigned long morseStart = 0;
unsigned long morseDuration = 0;

// Fast sequence counter
uint8_t fastCount = 0;

// Current Morse settings
uint16_t activeDot = SLOW_DOT_MS;
uint8_t activeDash = SLOW_DASH_MULT;
uint8_t activeLetterGap = SLOW_LETTER_GAP;

// Which LED(s) should transmit
uint8_t activeLED = 0;

// =======================================
// LED CONTROL
// =======================================

void allOff() {
  digitalWrite(LED_D2, LOW);
  digitalWrite(LED_D3, LOW);
}

void setMorseLED(bool on) {
  digitalWrite(
    LED_D2,
    on && (activeLED == 0 || activeLED == 1)
      ? HIGH : LOW
  );

  digitalWrite(
    LED_D3,
    on && (activeLED == 0 || activeLED == 2)
      ? HIGH : LOW
  );
}

// =======================================
// MORSE ENGINE
// =======================================

unsigned long symbolDuration(char symbol) {
  return (symbol == '-')
    ? (unsigned long)activeDot * activeDash
    : activeDot;
}

void startMorse(
  unsigned long now,
  uint8_t led,
  uint16_t dot,
  uint8_t dash,
  uint8_t letterGap
) {
  allOff();

  activeLED = led;
  activeDot = dot;
  activeDash = dash;
  activeLetterGap = letterGap;

  morseIndex = 0;
  morseOn = true;
  morseStart = now;
  morseDuration = symbolDuration(MORSE[0]);

  setMorseLED(true);
}

// Returns true once the whole callsign finishes
bool updateMorse(unsigned long now) {
  if (now - morseStart < morseDuration) {
    return false;
  }

  morseStart = now;

  if (morseOn) {
    // A dot or dash just finished
    setMorseLED(false);
    morseOn = false;
    morseIndex++;

    char next = MORSE[morseIndex];

    if (next == '\0') {
      return true;
    }

    if (next == ' ') {
      // Gap between Morse letters
      morseIndex++;
      morseDuration =
        (unsigned long)activeDot *
        activeLetterGap;
    }
    else {
      // Gap between symbols within a letter
      morseDuration = activeDot;
    }
  }
  else {
    // Begin the next dot or dash
    morseOn = true;

    morseDuration =
      symbolDuration(MORSE[morseIndex]);

    setMorseLED(true);
  }

  return false;
}

// =======================================
// START SLOW TRANSMISSION
// =======================================

void startSlow(unsigned long now) {
  currentMode = SLOW_MORSE;

  startMorse(
    now,
    0, // 0 = both LEDs
    SLOW_DOT_MS,
    SLOW_DASH_MULT,
    SLOW_LETTER_GAP
  );
}

// =======================================
// START FAST TRANSMISSION
// =======================================

void startFast(unsigned long now) {
  currentMode = FAST_MORSE;

  // Alternate D2, D3, D2, D3...
  uint8_t led = (fastCount % 2 == 0)
    ? 1 : 2;

  startMorse(
    now,
    led,
    FAST_DOT_MS,
    FAST_DASH_MULT,
    FAST_LETTER_GAP
  );
}

// =======================================
// SETUP
// =======================================

void setup() {
  pinMode(LED_D2, OUTPUT);
  pinMode(LED_D3, OUTPUT);

  allOff();

  startSlow(millis());
}

// =======================================
// MAIN LOOP
// =======================================

void loop() {
  unsigned long now = millis();

  switch (currentMode) {

    case SLOW_MORSE:
      if (updateMorse(now)) {
        allOff();
        currentMode = PAUSE_BEFORE_FAST;
        phaseStart = now;
      }
      break;

    case PAUSE_BEFORE_FAST:
      if (now - phaseStart >= PHASE_PAUSE_MS) {
        fastCount = 0;
        startFast(now);
      }
      break;

    case FAST_MORSE:
      if (updateMorse(now)) {
        allOff();

        fastCount++;

        if (fastCount >= FAST_ROUNDS * 2) {
          currentMode = PAUSE_BEFORE_RESTART;
          phaseStart = now;
        }
        else {
          currentMode = FAST_GAP;
          phaseStart = now;
        }
      }
      break;

    case FAST_GAP:
      if (now - phaseStart >=
          FAST_REPEAT_GAP_MS) {
        startFast(now);
      }
      break;

    case PAUSE_BEFORE_RESTART:
      if (now - phaseStart >= PHASE_PAUSE_MS) {
        startSlow(now);
      }
      break;
  }
}
