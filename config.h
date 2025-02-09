#ifndef CONFIG_H
#define CONFIG_H

// Joystick Configuration
#define JOYSTICK_X 6
const int LEFT_THRESHOLD = 1000;
const int RIGHT_THRESHOLD = 3000;
const int DEBOUNCE_DELAY = 200;  // ms

// Tank Display Management
enum TankTab {MAIN, DEEPWELL, RAINWATER, LIVESTOCK};
extern TankTab currentTab;
extern unsigned long lastTabChange;

// LoRa Configuration
#define LORA_TIMEOUT 3000  // 3 seconds
extern String receivedMessage;
extern unsigned long lastLoRaUpdate;

#endif
