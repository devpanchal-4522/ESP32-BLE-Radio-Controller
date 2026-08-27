#include <NimBLEDevice.h>
#include <BleGamepad.h>

// ================= PIN DEFINITIONS =================
#define JOYSTICK1_X     35
#define JOYSTICK1_Y     34
#define JOYSTICK1_SW    17

#define JOYSTICK2_X     32
#define JOYSTICK2_Y     33
#define JOYSTICK2_SW    25

#define TOGGLE_SWITCH1  26
#define TOGGLE_SWITCH2  16

#define LIMIT_SWITCH1   27
#define LIMIT_SWITCH2   18

#define STATUS_LED      4
#define BATTERY_ADC     12

// ================= BLE GAMEPAD =================
BleGamepad bleGamepad("ESP32 Gamepad", "YourBrand", 100);

bool ledTriggered = false;

// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  pinMode(JOYSTICK1_SW, INPUT_PULLUP);
  pinMode(JOYSTICK2_SW, INPUT_PULLUP);

  pinMode(TOGGLE_SWITCH1, INPUT);
  pinMode(TOGGLE_SWITCH2, INPUT);

  pinMode(LIMIT_SWITCH1, INPUT_PULLUP);
  pinMode(LIMIT_SWITCH2, INPUT_PULLUP);

  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(STATUS_LED, HIGH);
  delay(3000);
  digitalWrite(STATUS_LED, LOW);

  pinMode(BATTERY_ADC, INPUT);
  analogSetPinAttenuation(BATTERY_ADC, ADC_11db);

  bleGamepad.begin();
}

// ================= LOOP =================
void loop() {

  // ================= BATTERY MONITOR =================
  int adcValue = analogRead(BATTERY_ADC);

  float adcVoltage = ((adcValue / 4095.0) * 3.6) * 1.16;
  float batteryVoltage = adcVoltage * 1.5;        // 10k top, 20k bottom

  Serial.print("Battery Voltage: ");
  Serial.println(batteryVoltage);

  if (batteryVoltage < 3.5) {
    for (int i = 0; i < 3; i++) {
      digitalWrite(STATUS_LED, HIGH);
      delay(500);
      digitalWrite(STATUS_LED, LOW);
      delay(500);
    }
  }

  // ================= BLE CONNECT LED =================
  if (bleGamepad.isConnected() && !ledTriggered) {
    digitalWrite(STATUS_LED, HIGH);
    delay(3000);
    digitalWrite(STATUS_LED, LOW);
    ledTriggered = true;
  }

  if (!bleGamepad.isConnected()) {
    ledTriggered = false;
  }

  if (bleGamepad.isConnected()) {

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

    !digitalRead(JOYSTICK1_SW) ? bleGamepad.press(BUTTON_1) : bleGamepad.release(BUTTON_1);
    !digitalRead(JOYSTICK2_SW) ? bleGamepad.press(BUTTON_9) : bleGamepad.release(BUTTON_9);

    if (digitalRead(TOGGLE_SWITCH1) == LOW) {
      bleGamepad.press(BUTTON_5);
      bleGamepad.release(BUTTON_6);
    } else {
      bleGamepad.release(BUTTON_5);
      bleGamepad.press(BUTTON_6);
    }

    if (digitalRead(TOGGLE_SWITCH2) == LOW) {
      bleGamepad.press(BUTTON_7);
      bleGamepad.release(BUTTON_8);
    } else {
      bleGamepad.release(BUTTON_7);
      bleGamepad.press(BUTTON_8);
    }

    !digitalRead(LIMIT_SWITCH1) ? bleGamepad.press(BUTTON_10) : bleGamepad.release(BUTTON_10);
    !digitalRead(LIMIT_SWITCH2) ? bleGamepad.press(BUTTON_11) : bleGamepad.release(BUTTON_11);

    bleGamepad.sendReport();
  }

  delay(10);
}
