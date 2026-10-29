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

// ---------- Event handlers and callbacks ----------

// Event handler for button A – runs once for each real press.
void onButtonAPressed()
{
  pressCountA++;                                // add 1 to the count
  Serial.print("Button A pressed. Count = ");   // print the text...
  Serial.println(pressCountA);                  // ...then the number and a new line
}

// ---------- Interrupt Service Routines (ISRs) ----------


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

  // Touch sensor (interrupt)

  // Timer
}
