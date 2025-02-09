#include "config.h"  // Include the config file
#include "heltec_edited.h"
#include "display_manager.h"


TankTab currentTab = MAIN;
unsigned long lastTabChange = 0;
String receivedMessage = "";
unsigned long lastLoRaUpdate = 0;

void setup() {
  heltec_ve(true);
  initDisplay();  // Call the display setup

  // Initialize LoRa
  heltec_setup();
  int state = radio.begin(915.0);
  if (state != RADIOLIB_ERR_NONE) {
    displayError("LoRa error: " + String(state));
    while (1);
  }

  displayMessage("System Ready", 1000);
}

void handleJoystick() {
  int xValue = analogRead(JOYSTICK_X);
  static int lastXValue = xValue;

  if ((millis() - lastTabChange) > DEBOUNCE_DELAY && abs(xValue - lastXValue) > 100) {
    lastXValue = xValue;
    if (xValue < LEFT_THRESHOLD) {
      currentTab = (TankTab)((currentTab + 1) % 4);
    } else if (xValue > RIGHT_THRESHOLD) {
      currentTab = (TankTab)((currentTab - 1 + 4) % 4);
    }
    lastTabChange = millis();
  }
}

void handleLoRa() {
  int state = radio.receive(receivedMessage, LORA_TIMEOUT);
  if (state == RADIOLIB_ERR_NONE) {
    lastLoRaUpdate = millis();
    int commaPos = receivedMessage.indexOf(',');
    if (commaPos != -1) {
      int tankID = receivedMessage.substring(0, commaPos).toInt();
      float level = receivedMessage.substring(commaPos + 1).toFloat();
      updateTankData(tankID, level);
    }
    radio.transmit("ACK");
  }
}

void loop() {
  heltec_loop();
  handleJoystick();
  handleLoRa();
  updateDisplay(currentTab, lastLoRaUpdate);
  delay(100);
}
