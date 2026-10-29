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


// ---------- Event handlers and callbacks ----------


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

  // Read button A on every pass of loop() – this is polling.
  // Use the command that gives HIGH or LOW (Common Commands: "Read a Pin").
  if (digitalRead(BUTTON_A) == LOW)      // LOW = the button is pressed
  {
    Serial.println("Button A is pressed");
  }

  // Button B (interrupt)

  // Touch sensor (interrupt)

  // Timer
}
