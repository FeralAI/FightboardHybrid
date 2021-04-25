#ifndef _LED_MAPPER_
#define _LED_MAPPER_

#include <FastLED.h>

#define LED_PIN 5
#define LED_BUTTON_COUNT 16
#define LEDS_PER_BUTTON 1
#define LED_COUNT (LED_BUTTON_COUNT * LEDS_PER_BUTTON)
#define COLUMN_COUNT 7
#define COLUMN_HEIGHT 2

// Button defines
#define LED_INDEX_P1      0
#define LED_INDEX_P2      1
#define LED_INDEX_P3      2
#define LED_INDEX_P4      3
#define LED_INDEX_K4      4
#define LED_INDEX_K3      5
#define LED_INDEX_K2      6
#define LED_INDEX_K1      7
#define LED_INDEX_RIGHT   8
#define LED_INDEX_DOWN    9
#define LED_INDEX_LEFT   10
#define LED_INDEX_UP     11
#define LED_INDEX_NONE   255

// Define mappings for HitBox button layout
const int ColumnMatrix[COLUMN_COUNT][COLUMN_HEIGHT] = {
	{ LED_INDEX_LEFT,  LED_INDEX_NONE },
	{ LED_INDEX_DOWN,  LED_INDEX_UP },
	{ LED_INDEX_RIGHT, LED_INDEX_NONE },
	{ LED_INDEX_P1,    LED_INDEX_K1 },
	{ LED_INDEX_P2,    LED_INDEX_K2 },
	{ LED_INDEX_P3,    LED_INDEX_K3 },
	{ LED_INDEX_P4,    LED_INDEX_K4 },
};

struct ButtonColorMap {
	ButtonColorMap(uint8_t bi, CRGB bc)
		: buttonIndex(bi), buttonColor(bc) { }
	uint8_t buttonIndex;
	CRGB buttonColor;
};

// const ButtonColorMap XboxColorMapping[LED_BUTTON_COUNT] = {
// 	ButtonColorMap(LED_INDEX_P1, CRGB::Blue),      // X
// 	ButtonColorMap(LED_INDEX_P2, CRGB::Yellow),    // Y
// 	ButtonColorMap(LED_INDEX_P3, CRGB::LightBlue), // RB
// 	ButtonColorMap(LED_INDEX_P4, CRGB::Purple),    // LB
// 	ButtonColorMap(LED_INDEX_K4, CRGB::Orange),    // LT
// 	ButtonColorMap(LED_INDEX_K3, CRGB::Magenta),   // RT
// 	ButtonColorMap(LED_INDEX_K2, CRGB::Red),       // B
// 	ButtonColorMap(LED_INDEX_K1, CRGB::Green),     // A
// 	ButtonColorMap(LED_INDEX_RIGHT, CRGB::White),
// 	ButtonColorMap(LED_INDEX_DOWN, CRGB::White),
// 	ButtonColorMap(LED_INDEX_LEFT, CRGB::White),
// 	ButtonColorMap(LED_INDEX_UP, CRGB::White),
// };

inline void configureLeds(CRGB leds[LED_COUNT]) __attribute__((always_inline));
inline void applyColorMapping(CRGB leds[LED_COUNT], const ButtonColorMap colorMapping[LED_BUTTON_COUNT]) __attribute__((always_inline));
inline void showLeds() __attribute__((always_inline));

void configureLeds(CRGB leds[LED_COUNT], bool isXInput) {
	FastLED.addLeds<SK6812, LED_PIN>(leds, LED_COUNT);
	FastLED.setMaxPowerInVoltsAndMilliamps(5, 250);
	FastLED.setBrightness(50);
	for (int i = 0; i < 16; i++)
		leds[i] = isXInput ? CRGB::White : CRGB::Red;

	showLeds();
}

void applyColorMapping(CRGB leds[LED_COUNT], const ButtonColorMap colorMapping[LED_BUTTON_COUNT]) {
	for (uint8_t b = 0; b < LED_BUTTON_COUNT; b++) {
		for (uint8_t i = 0; i < LEDS_PER_BUTTON; i++)
			leds[(colorMapping[b].buttonIndex * LEDS_PER_BUTTON) + i] = colorMapping[b].buttonColor;
	}

	FastLED.show();
}

void showLeds() {
	FastLED.show();
}

#endif
