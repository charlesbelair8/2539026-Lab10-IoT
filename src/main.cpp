// Lab 10 – Event-Driven Programming with Push Buttons and a Touch Sensor
// STARTER FILE – follow the lab procedure and add your code under each comment.
#include <Arduino.h>

// ---------- Pin numbers ----------
#define BUTTON_A   32   // polled button
#define BUTTON_B   33   // interrupt button
#define TOUCH_PIN  27   // touch sensor wire
#define GREEN_LED  25
#define RED_LED    26
#define BUZZER     13

// ---------- Global variables ----------

// The state of button A on the last pass of loop(). It starts released (HIGH).
int lastStateA = HIGH;
int pressCountA = 0;                          // How many presses have been counted.
unsigned long lastChangeA = 0; // The time (in ms) of the last change that was accepted.
// Changes closer together than 50 ms are bounce, so they are ignored.
const unsigned long DEBOUNCE_TIME = 50;

// These two variables are changed inside the ISR, so they need the keyword
// for a shared ISR variable (Common Commands: "Shared ISR Variable").
// buttonBFlag: raised (true) by the ISR when button B is pressed.
volatile bool buttonBFlag = false;
// lastInterruptB: the time of the last accepted press (used to debounce).
volatile unsigned long lastInterruptB = 0;
// pressCountB is only used in loop(), so it needs no keyword.
int pressCountB = 0;

// ---------- Event handlers and callbacks ----------

// Event handler for button B – called from loop(), never from the ISR,
// so Serial.print() is allowed here.
void onButtonBPressed()
{
  pressCountB++;                                            // add 1 to the count
  Serial.print("Button B pressed (interrupt). Count = ");   // print the text...
  Serial.println(pressCountB);                              // ...then the number
}


// Event handler for button A – runs once for each real press.
void onButtonAPressed()
{
  pressCountA++;                                // add 1 to the count
  Serial.print("Button A pressed. Count = ");   // print the text...
  Serial.println(pressCountA);                  // ...then the number and a new line
}

// ---------- Interrupt Service Routines (ISRs) ----------
// ISR for button B – runs the instant the pin falls, even if loop() is busy.
// Blank before the name: the keyword that keeps an ISR in fast memory
// (Common Commands: "ISR Function"). Keep an ISR short: no Serial, no delay().
void IRAM_ATTR buttonB_ISR()
{
  // Ignore presses less than 200 ms apart (debounce inside the ISR).
  if (millis() - lastInterruptB > 200)
  {
    lastInterruptB = millis();   // remember when this press happened
    buttonBFlag = true;        // raise the flag for loop(): true or false?
  }
}


void setup()
{
  Serial.begin(115200);
  delay(500);
  Serial.println("Lab 10: Event-Driven Programming");

  // Inputs and outputs

  // Buttons: inputs with the internal pull-up resistor turned on
  // (Common Commands: "Input with Pull-up"). Pressed = LOW, released = HIGH.

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);

  // LEDs and buzzer: the ESP32 drives them, so they are outputs
  // (Common Commands: "Output").

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Interrupts
  // Run buttonB_ISR() when the pin of button B changes (Common Commands:
  // "Attach an Interrupt").
  // 1st blank: the command that turns a pin number into an interrupt number.
  // 2nd blank: the mode. Button B goes HIGH → LOW when pressed:
  //            RISING, FALLING or CHANGE?
  attachInterrupt(digitalPinToInterrupt(BUTTON_B), buttonB_ISR, FALLING);

  // Callbacks
}

void loop()
{
  // Button A (polling)

  // 1. Read button A now (Common Commands: "Read a Pin").
  int stateA =digitalRead(BUTTON_A);

  // 2. Did the state change, AND has more than DEBOUNCE_TIME passed
  //    since the last change? (Common Commands: "Time Since Start")
    if (stateA != lastStateA && millis() - lastChangeA > DEBOUNCE_TIME)
    {
      // 3. Accept the change: save the time now, and remember the new state.
      lastChangeA = millis();
      lastStateA = stateA;

    // 4. Only a change to "pressed" is a press event.
    //    Is a pressed button HIGH or LOW?
      if (stateA == LOW)
      {
        onButtonAPressed();   // call the event handler
      }
    }


  // Button B (interrupt)
  // Flag pattern: did the ISR raise the flag?
  if (buttonBFlag == true)
  {
    buttonBFlag = false;   // lower the flag first, so the press is handled once
    onButtonBPressed();    // then call the handler
  }

  // Touch sensor (interrupt)
  // Print the touch value twice a second. Use the command that reads the
  // touch sensor (Common Commands: "Read the Touch Sensor").
  Serial.println(analogRead(TOUCH_PIN));   // calibration – remove after Step 1
    delay(500);                                // calibration – remove after Step 1

  // Timer
}
