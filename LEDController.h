#ifndef _LED_MAPPER_
#define _LED_MAPPER_

#include <Adafruit_NeoPixel.h>

#define LED_PIN 5
#define LED_COUNT 12
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
	ButtonColorMap(uint8_t bi, uint32_t bc)
		: buttonIndex(bi), buttonColor(bc) { }
	uint8_t buttonIndex;
	uint32_t buttonColor;
};

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

uint32_t wheel(byte pos) {
	pos = 255 - pos;
	if (pos < 85) {
		return strip.Color(255 - pos * 3, 0, pos * 3);
	}
	if (pos < 170) {
		pos -= 85;
		return strip.Color(0, pos * 3, 255 - pos * 3);
	}
	pos -= 170;
	return strip.Color(pos * 3, 255 - pos * 3, 0);
}

static const uint32_t ColorBlack     = strip.Color(  0,   0,   0,   0);
static const uint32_t ColorWhite     = strip.Color(  0,   0,   0, 255);

static const uint32_t ColorRed       = strip.Color(255,   0,   0,   0);
static const uint32_t ColorOrange    = strip.Color(255, 128,   0,   0);
static const uint32_t ColorYellow    = strip.Color(255, 255,   0,   0);
static const uint32_t ColorLimeGreen = strip.Color(128, 255,   0,   0);
static const uint32_t ColorGreen     = strip.Color(  0, 255,   0,   0);
static const uint32_t ColorSeafoam   = strip.Color(  0, 255, 128,   0);
static const uint32_t ColorAqua      = strip.Color(  0, 255, 255,   0);
static const uint32_t ColorSkyBlue   = strip.Color(  0, 128, 255,   0);
static const uint32_t ColorBlue      = strip.Color(  0,   0, 255,   0);
static const uint32_t ColorPurple    = strip.Color(128,   0, 255,   0);
static const uint32_t ColorPink      = strip.Color(255,   0, 255,   0);
static const uint32_t ColorMagenta   = strip.Color(255,   0, 128,   0);

const ButtonColorMap GuiltyGearTypeAColorMapping[LED_COUNT] = {
	ButtonColorMap(LED_INDEX_P1, ColorBlue),     // K
	ButtonColorMap(LED_INDEX_P2, ColorGreen),    // S
	ButtonColorMap(LED_INDEX_P3, ColorRed),      // HS
	ButtonColorMap(LED_INDEX_P4, ColorBlack),
	ButtonColorMap(LED_INDEX_K1, ColorPurple),   // P
	ButtonColorMap(LED_INDEX_K2, ColorBlack),
	ButtonColorMap(LED_INDEX_K3, ColorOrange),   // D
	ButtonColorMap(LED_INDEX_K4, ColorBlack),
	ButtonColorMap(LED_INDEX_RIGHT, ColorWhite),
	ButtonColorMap(LED_INDEX_DOWN, ColorWhite),
	ButtonColorMap(LED_INDEX_LEFT, ColorWhite),
	ButtonColorMap(LED_INDEX_UP, ColorWhite),
};

const ButtonColorMap NeoGeoCurvedColorMapping[LED_COUNT] = {
	ButtonColorMap(LED_INDEX_P1, ColorYellow),   // B
	ButtonColorMap(LED_INDEX_P2, ColorGreen),    // C
	ButtonColorMap(LED_INDEX_P3, ColorBlue),     // D
	ButtonColorMap(LED_INDEX_P4, ColorBlack),
	ButtonColorMap(LED_INDEX_K1, ColorRed),      // A
	ButtonColorMap(LED_INDEX_K2, ColorBlack),
	ButtonColorMap(LED_INDEX_K3, ColorBlack),
	ButtonColorMap(LED_INDEX_K4, ColorBlack),
	ButtonColorMap(LED_INDEX_RIGHT, ColorWhite),
	ButtonColorMap(LED_INDEX_DOWN, ColorWhite),
	ButtonColorMap(LED_INDEX_LEFT, ColorWhite),
	ButtonColorMap(LED_INDEX_UP, ColorWhite),
};

const ButtonColorMap NeoGeoModernColorMapping[LED_COUNT] = {
	ButtonColorMap(LED_INDEX_P1, ColorRed),      // A
	ButtonColorMap(LED_INDEX_P2, ColorGreen),    // C
	ButtonColorMap(LED_INDEX_P3, ColorBlack),
	ButtonColorMap(LED_INDEX_P4, ColorBlack),
	ButtonColorMap(LED_INDEX_K1, ColorYellow),   // B
	ButtonColorMap(LED_INDEX_K2, ColorBlue),     // D
	ButtonColorMap(LED_INDEX_K3, ColorBlack),
	ButtonColorMap(LED_INDEX_K4, ColorBlack),
	ButtonColorMap(LED_INDEX_RIGHT, ColorWhite),
	ButtonColorMap(LED_INDEX_DOWN, ColorWhite),
	ButtonColorMap(LED_INDEX_LEFT, ColorWhite),
	ButtonColorMap(LED_INDEX_UP, ColorWhite),
};

const ButtonColorMap NeoGeoStraightColorMapping[LED_COUNT] = {
	ButtonColorMap(LED_INDEX_P1, ColorRed),      // A
	ButtonColorMap(LED_INDEX_P2, ColorYellow),   // B
	ButtonColorMap(LED_INDEX_P3, ColorGreen),    // C
	ButtonColorMap(LED_INDEX_P4, ColorBlue),     // D
	ButtonColorMap(LED_INDEX_K1, ColorBlack),
	ButtonColorMap(LED_INDEX_K2, ColorBlack),
	ButtonColorMap(LED_INDEX_K3, ColorBlack),
	ButtonColorMap(LED_INDEX_K4, ColorBlack),
	ButtonColorMap(LED_INDEX_RIGHT, ColorWhite),
	ButtonColorMap(LED_INDEX_DOWN, ColorWhite),
	ButtonColorMap(LED_INDEX_LEFT, ColorWhite),
	ButtonColorMap(LED_INDEX_UP, ColorWhite),
};

const ButtonColorMap SixButtonFighterColorMapping[LED_COUNT] = {
	ButtonColorMap(LED_INDEX_P1, ColorBlue),     // LP
	ButtonColorMap(LED_INDEX_P2, ColorYellow),   // MP
	ButtonColorMap(LED_INDEX_P3, ColorRed),      // HP
	ButtonColorMap(LED_INDEX_P4, ColorBlack),
	ButtonColorMap(LED_INDEX_K1, ColorBlue),     // LK
	ButtonColorMap(LED_INDEX_K2, ColorYellow),   // MK
	ButtonColorMap(LED_INDEX_K3, ColorRed),      // HK
	ButtonColorMap(LED_INDEX_K4, ColorBlack),
	ButtonColorMap(LED_INDEX_RIGHT, ColorWhite),
	ButtonColorMap(LED_INDEX_DOWN, ColorWhite),
	ButtonColorMap(LED_INDEX_LEFT, ColorWhite),
	ButtonColorMap(LED_INDEX_UP, ColorWhite),
};

const ButtonColorMap SuperFamicomColorMapping[LED_COUNT] = {
	ButtonColorMap(LED_INDEX_P1, ColorGreen),     // Y
	ButtonColorMap(LED_INDEX_P2, ColorBlue),      // X
	ButtonColorMap(LED_INDEX_P3, ColorOrange),    // R
	ButtonColorMap(LED_INDEX_P4, ColorMagenta),   // L
	ButtonColorMap(LED_INDEX_K4, ColorAqua),      // ZL
	ButtonColorMap(LED_INDEX_K3, ColorPurple),    // ZR
	ButtonColorMap(LED_INDEX_K2, ColorRed),       // A
	ButtonColorMap(LED_INDEX_K1, ColorYellow),    // B
	ButtonColorMap(LED_INDEX_RIGHT, ColorWhite),
	ButtonColorMap(LED_INDEX_DOWN, ColorWhite),
	ButtonColorMap(LED_INDEX_LEFT, ColorWhite),
	ButtonColorMap(LED_INDEX_UP, ColorWhite),
};

const ButtonColorMap XboxColorMapping[LED_COUNT] = {
	ButtonColorMap(LED_INDEX_P1, ColorBlue),      // X
	ButtonColorMap(LED_INDEX_P2, ColorYellow),    // Y
	ButtonColorMap(LED_INDEX_P3, ColorOrange),    // RB
	ButtonColorMap(LED_INDEX_P4, ColorMagenta),   // LB
	ButtonColorMap(LED_INDEX_K4, ColorAqua),      // LT
	ButtonColorMap(LED_INDEX_K3, ColorPurple),    // RT
	ButtonColorMap(LED_INDEX_K2, ColorRed),       // B
	ButtonColorMap(LED_INDEX_K1, ColorGreen),     // A
	ButtonColorMap(LED_INDEX_RIGHT, ColorWhite),
	ButtonColorMap(LED_INDEX_DOWN, ColorWhite),
	ButtonColorMap(LED_INDEX_LEFT, ColorWhite),
	ButtonColorMap(LED_INDEX_UP, ColorWhite),
};

const uint8_t ColorMapCount = 7;

inline uint8_t configureLeds(bool isXInput) __attribute__((always_inline));
inline void applyColorMapping(const ButtonColorMap colorMapping[LED_COUNT]) __attribute__((always_inline));
inline void showLeds() __attribute__((always_inline));

uint8_t configureLeds(bool isXInput) {
	strip.begin();
	strip.setBrightness(64); // 25% Brightness

	if (isXInput) {
		applyColorMapping(XboxColorMapping);
		return 0;
	} else {
		applyColorMapping(SuperFamicomColorMapping);
		return 1;
	}
}

void applyColorMapping(const ButtonColorMap colorMapping[LED_COUNT]) {
	for (uint8_t i = 0; i < LED_COUNT; i++)
		strip.setPixelColor(colorMapping[i].buttonIndex, colorMapping[i].buttonColor);

	showLeds();
}

void selectColorMapping(uint8_t index) {
	if (index > ColorMapCount)
		index = 0;

	switch (index) {
		case 0: applyColorMapping(XboxColorMapping); break;
		case 1: applyColorMapping(SuperFamicomColorMapping); break;
		case 2: applyColorMapping(SixButtonFighterColorMapping); break;
		case 3: applyColorMapping(GuiltyGearTypeAColorMapping); break;
		case 4: applyColorMapping(NeoGeoStraightColorMapping); break;
		case 5: applyColorMapping(NeoGeoCurvedColorMapping); break;
		case 6: applyColorMapping(NeoGeoModernColorMapping); break;
	}
}

void showLeds() {
	strip.show();
}

#endif
