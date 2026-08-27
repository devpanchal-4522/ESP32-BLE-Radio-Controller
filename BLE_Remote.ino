#include <NimBLEDevice.h>
#include <BleGamepad.h>

// ================= PIN DEFINITIONS =================
#define JOYSTICK1_X     35
#define JOYSTICK1_Y     34
#define JOYSTICK1_SW    17

#define JOYSTICK2_X     32
#define JOYSTICK2_Y     33
#define JOYSTICK2_SW    25   // NEW joystick button

#define TOGGLE_SWITCH1  26   // SPDT toggle
#define TOGGLE_SWITCH2  16   // SPDT toggle

#define LIMIT_SWITCH1   27
#define LIMIT_SWITCH2   18

#define STATUS_LED      4    // ✅ ADDED (External LED on GPIO 4)

// ================= BLE GAMEPAD =================
BleGamepad bleGamepad("ESP32 Gamepad", "YourBrand", 100);

bool ledTriggered = false;   // ✅ ADDED

// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  pinMode(JOYSTICK1_SW, INPUT_PULLUP);
  pinMode(JOYSTICK2_SW, INPUT_PULLUP);

  pinMode(TOGGLE_SWITCH1, INPUT);
  pinMode(TOGGLE_SWITCH2, INPUT);

  pinMode(LIMIT_SWITCH1, INPUT_PULLUP);
  pinMode(LIMIT_SWITCH2, INPUT_PULLUP);

  pinMode(STATUS_LED, OUTPUT);        // ✅ ADDED
  digitalWrite(STATUS_LED, LOW);      // ✅ ADDED

  digitalWrite(STATUS_LED, 1);
  delay(3000);
  digitalWrite(STATUS_LED, 0);

  bleGamepad.begin();
}

// ================= LOOP =================
void loop() {

  // ✅ LED ON for 3 seconds when connected (only once)
  if (bleGamepad.isConnected() && !ledTriggered) {
    digitalWrite(STATUS_LED, HIGH);
    delay(3000);
    digitalWrite(STATUS_LED, LOW);
    ledTriggered = true;
  }

  if (!bleGamepad.isConnected()) {
    ledTriggered = false;   // reset when disconnected
  }

  if (bleGamepad.isConnected()) {

    // -------- Joysticks --------
    int joy1X = analogRead(JOYSTICK1_X);
    int joy1Y = analogRead(JOYSTICK1_Y);
    int joy2X = analogRead(JOYSTICK2_X);
    int joy2Y = analogRead(JOYSTICK2_Y);

    bleGamepad.setLeftThumb(
      map(joy1X, 0, 4095, 32767, 0),
      map(joy1Y, 0, 4095, 0, 32767)
    );

    bleGamepad.setRightThumb(
      map(joy2X, 0, 4095, 32767, 0),
      map(joy2Y, 0, 4095, 32767, 0)
    );

    // -------- Buttons --------
    !digitalRead(JOYSTICK1_SW) ? bleGamepad.press(BUTTON_1) : bleGamepad.release(BUTTON_1);
    !digitalRead(JOYSTICK2_SW) ? bleGamepad.press(BUTTON_9) : bleGamepad.release(BUTTON_9);

    // -------- Toggle Switch 1 --------
    if (digitalRead(TOGGLE_SWITCH1) == LOW) {
      bleGamepad.press(BUTTON_5);
      bleGamepad.release(BUTTON_6);
    } else {
      bleGamepad.release(BUTTON_5);
      bleGamepad.press(BUTTON_6);
    }

    // -------- Toggle Switch 2 --------
    if (digitalRead(TOGGLE_SWITCH2) == LOW) {
      bleGamepad.press(BUTTON_7);
      bleGamepad.release(BUTTON_8);
    } else {
      bleGamepad.release(BUTTON_7);
      bleGamepad.press(BUTTON_8);
    }

    // -------- Limit Switches --------
    !digitalRead(LIMIT_SWITCH1) ? bleGamepad.press(BUTTON_10) : bleGamepad.release(BUTTON_10);
    !digitalRead(LIMIT_SWITCH2) ? bleGamepad.press(BUTTON_11) : bleGamepad.release(BUTTON_11);

    bleGamepad.sendReport();
  }

  delay(10);
}