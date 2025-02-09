
// //RECEIVER CODE

// #define HELTEC_POWER_BUTTON
// #include "heltec_edited.h"

// #define HELTEC_V3FIX

// void setup() {

//   heltec_ve(true);
//   display.init();
//   display.setContrast(255);
//   display.flipScreenVertically();

//   heltec_setup();

//   display.println("Initializing LoRa...");
//   int state = radio.begin();
//   if (state == RADIOLIB_ERR_NONE) {
//     display.println("LoRa Initialized");
//   } else {
//     display.printf("LoRa Failed, code: %d\n", state);
//   }
//   display.display();
//   delay(1000);
// }

// void loop() {


//   heltec_loop();

//   String receivedMessage;
//   int state = radio.receive(receivedMessage, 3000); // Timeout set to 3 seconds

//   display.clear();

//   if (state == RADIOLIB_ERR_NONE) {
//     display.println("Data Received!");
//     display.printf("Distance: %s cm\n", receivedMessage.c_str());
//     display.display();

//     // Send acknowledgment
//     int ackState = radio.transmit("ACK");
//     if (ackState == RADIOLIB_ERR_NONE) {
//       display.println("ACK Sent");
//     } else {
//       display.println("ACK Send Failed");
//     }
//     display.display();
//   } else if (state == RADIOLIB_ERR_RX_TIMEOUT) {
//     display.println("No Data Received");
//     display.display();
//   }

//   delay(500); // Small delay to allow system readiness
// }



// //v2

// #define HELTEC_POWER_BUTTON
// #include "heltec_edited.h"
// #include "display_manager.h"  // Include the display manager
// #define HELTEC_V3FIX

// // Joystick Configuration
// #define JOYSTICK_X 6
// const int LEFT_THRESHOLD = 1000;
// const int RIGHT_THRESHOLD = 3000;
// const int DEBOUNCE_DELAY = 200;  // ms

// // Tank Display Management
// enum TankTab {MAIN, DEEPWELL, RAINWATER, LIVESTOCK};
// TankTab currentTab = MAIN;
// unsigned long lastTabChange = 0;

// // LoRa Configuration
// #define LORA_TIMEOUT 3000  // 3 seconds
// String receivedMessage = "";
// unsigned long lastLoRaUpdate = 0;

// void setup() {
//   heltec_ve(true);
//   initDisplay();  // Call the display setup

//   // Initialize LoRa
//   heltec_setup();
//   int state = radio.begin(915.0);
//   if (state != RADIOLIB_ERR_NONE) {
//     displayError("LoRa error: " + String(state));
//     while (1);
//   }

//   displayMessage("System Ready", 1000);
// }

// void handleJoystick() {
//   int xValue = analogRead(JOYSTICK_X);
//   static int lastXValue = xValue;

//   if ((millis() - lastTabChange) > DEBOUNCE_DELAY && abs(xValue - lastXValue) > 100) {
//     lastXValue = xValue;
//     if (xValue < LEFT_THRESHOLD) {
//       currentTab = (TankTab)((currentTab + 1) % 4);
//     } else if (xValue > RIGHT_THRESHOLD) {
//       currentTab = (TankTab)((currentTab - 1 + 4) % 4);
//     }
//     lastTabChange = millis();
//   }
// }

// void handleLoRa() {
//   int state = radio.receive(receivedMessage, LORA_TIMEOUT);
//   if (state == RADIOLIB_ERR_NONE) {
//     lastLoRaUpdate = millis();
//     int commaPos = receivedMessage.indexOf(',');
//     if (commaPos != -1) {
//       int tankID = receivedMessage.substring(0, commaPos).toInt();
//       float level = receivedMessage.substring(commaPos + 1).toFloat();
//       updateTankData(tankID, level);
//     }
//     radio.transmit("ACK");
//   }
// }

// void loop() {
//   heltec_loop();
//   handleJoystick();
//   handleLoRa();
//   updateDisplay(currentTab, lastLoRaUpdate);
//   delay(100);
// }



