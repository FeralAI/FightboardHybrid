#include "LUFAConfig.h"
#include <LUFA.h>
#include "XS_HID.h"
#include <EEPROM.h>

#include "Mapping/Fightboard.h"
#include "LEDController.h"

#define EEPROM_INPUT_MODE_OFFSET 0
#define EEPROM_DPAD_MODE_OFFSET 1
#define EEPROM_LED_MODE_OFFSET 3

#define AXIS_MIN 0
#define AXIS_MID 128
#define AXIS_MAX 255

typedef enum {
	DIGITAL,
	LEFT_ANALOG,
	RIGHT_ANALOG,
} DpadMode;

bool xinput = true;                          // Using XInput?
byte dpadStates[4] = { };                    // The dpad input states
LedEffectMode ledMode = LedEffectMode::NONE; // The selected LED mode
byte buttonStates[BUTTON_INDICES] = { };     // The button states
DpadMode dpadMode;                           // Current D-Pad mode
Fightboard board;                            // The board instance

inline void setButton(ButtonMapping mapping, uint8_t portStates[], uint8_t lastButtonStates[]) __attribute__((always_inline));
inline void setDpad(uint8_t portStates[], uint8_t lastDpadStates[]) __attribute__((always_inline));

void setup() {
	EEPROM.get(EEPROM_INPUT_MODE_OFFSET, xinput);
	EEPROM.get(EEPROM_DPAD_MODE_OFFSET, dpadMode);
	EEPROM.get(EEPROM_LED_MODE_OFFSET, ledMode);

	board.setupPins();
	delay(500);
	setInputMode();
	configureLeds();
	setLedMode();

	SetupHardware(xinput);
	GlobalInterruptEnable();
}

void loop() {
	// Read logic
	uint8_t portStates[PORT_COUNT];
	board.getPortStates(portStates);

	// Cache previous states for this loop
	uint8_t lastButtonStates[BUTTON_INDICES];
	memcpy(lastButtonStates, buttonStates, sizeof(lastButtonStates));

	// Button values
	setButton(board.MapButtonP1, portStates, lastButtonStates);
	setButton(board.MapButtonP2, portStates, lastButtonStates);
	setButton(board.MapButtonP3, portStates, lastButtonStates);
	setButton(board.MapButtonP4, portStates, lastButtonStates);
	setButton(board.MapButtonK1, portStates, lastButtonStates);
	setButton(board.MapButtonK2, portStates, lastButtonStates);
	setButton(board.MapButtonK3, portStates, lastButtonStates);
	setButton(board.MapButtonK4, portStates, lastButtonStates);
	setButton(board.MapButtonSelect, portStates, lastButtonStates);
	setButton(board.MapButtonStart, portStates, lastButtonStates);
	setButton(board.MapButtonLogo, portStates, lastButtonStates);
	setButton(board.MapButtonL3, portStates, lastButtonStates);
	setButton(board.MapButtonR3, portStates, lastButtonStates);

	// Dpad values
	setDpad(portStates, lastButtonStates);

	// Send it
	send_pad_state();
}

void setInputMode() {
	bool isSwitch = digitalRead(PIN_SELECT) == LOW;
	bool isXInput = digitalRead(PIN_START) == LOW;
	if (isSwitch && !isXInput) {
		xinput = false;
		EEPROM.put(EEPROM_INPUT_MODE_OFFSET, xinput);
	} else if (isXInput && !isSwitch) {
		xinput = true;
		EEPROM.put(EEPROM_INPUT_MODE_OFFSET, xinput);
	}
}

void setLedMode() {
	if ((byte)ledMode >= LED_EFFECT_COUNT)
		ledMode = LedEffectMode::NONE;

	if (ledMode == LedEffectMode::NONE)
		ledMode = xinput ? LedEffectMode::XBOX : LedEffectMode::SFC;

	if (digitalRead(PIN_R3) == LOW) {
		EEPROM.put(EEPROM_LED_MODE_OFFSET, LedEffectMode::NONE);
	} else {
		bool saveLedMode = true;
		bool buttonStates[] = {
			digitalRead(PIN_P1) == LOW,
			digitalRead(PIN_P2) == LOW,
			digitalRead(PIN_P3) == LOW,
			digitalRead(PIN_P4) == LOW,
			digitalRead(PIN_K1) == LOW,
			digitalRead(PIN_K2) == LOW,
			digitalRead(PIN_K3) == LOW,
			digitalRead(PIN_K4) == LOW,
		};

		if (buttonStates[0] && buttonStates[1] && buttonStates[2] && buttonStates[3]) {
			ledMode = LedEffectMode::STATIC_RAINBOW;
		} else if (buttonStates[0]) {
			ledMode = LedEffectMode::XBOX;
		} else if (buttonStates[1]) {
			ledMode = LedEffectMode::SFC;
		} else if (buttonStates[2]) {
			ledMode = LedEffectMode::SIX_BUTTON;
		} else if (buttonStates[3]) {
			ledMode = LedEffectMode::GG_TYPE_A;
		} else if (buttonStates[4]) {
			ledMode = LedEffectMode::NEOGEO_STRAIGHT;
		} else if (buttonStates[5]) {
			ledMode = LedEffectMode::NEOGEO_CURVED;
		} else if (buttonStates[6]) {
			ledMode = LedEffectMode::NEOGEO_MODERN;
		} else if (buttonStates[7]) {
			ledMode = LedEffectMode::GG_CUSTOM;
		} else {
			saveLedMode = false;
		}

		if (saveLedMode)
			EEPROM.put(EEPROM_LED_MODE_OFFSET, ledMode);
	}

	selectEffect(ledMode);
}

void setButton(ButtonMapping mapping, uint8_t portStates[], uint8_t lastButtonStates[]) {
	buttonStates[mapping.stateIndex] = (portStates[mapping.portIndex] >> mapping.portPin & 1);
	if (buttonStates[mapping.stateIndex] != lastButtonStates[mapping.stateIndex])
		buttonStatus[mapping.stateIndex] = buttonStates[mapping.stateIndex] == 0;
}

void setDpad(uint8_t portStates[], uint8_t lastDpadStates[]) {
	// Gather inputs
	bool up    = !(portStates[board.MapDpadUp.portIndex] >> board.MapDpadUp.portPin & 1);
	bool down  = !(portStates[board.MapDpadDown.portIndex] >> board.MapDpadDown.portPin & 1);
	bool left  = !(portStates[board.MapDpadLeft.portIndex] >> board.MapDpadLeft.portPin & 1);
	bool right = !(portStates[board.MapDpadRight.portIndex] >> board.MapDpadRight.portPin & 1);

	// Check D-Pad mode changed
	if (buttonStatus[BUTTONSTART] && buttonStatus[BUTTONSELECT]) {
		bool update = true;
		if (left)
			dpadMode = LEFT_ANALOG;
		else if (right)
			dpadMode = RIGHT_ANALOG;
		else if (up)
			dpadMode = DIGITAL;
		else
			update = false;

		if (update)
			EEPROM.put(EEPROM_DPAD_MODE_OFFSET, dpadMode);
	}

	// Perform SOCD cleaning
	if (up && down)    { down = false; }
	if (left && right) { left = false; right = false; }

	// Set D-Pad inputs
	switch (dpadMode) {
		case LEFT_ANALOG:
			buttonStatus[AXISRX] = AXIS_MID;
			buttonStatus[AXISRY] = AXIS_MID;
			buttonStatus[BUTTONUP] = 0;
			buttonStatus[BUTTONDOWN] = 0;
			buttonStatus[BUTTONLEFT] = 0;
			buttonStatus[BUTTONRIGHT] = 0;

			if (up && right) { buttonStatus[AXISLY] = AXIS_MIN; buttonStatus[AXISLX] = AXIS_MAX; }
			else if (down && right) { buttonStatus[AXISLY] = AXIS_MAX; buttonStatus[AXISLX] = AXIS_MAX; }
			else if (down && left) { buttonStatus[AXISLY] = AXIS_MAX; buttonStatus[AXISLX] = AXIS_MIN; }
			else if (up && left){ buttonStatus[AXISLY] = AXIS_MIN; buttonStatus[AXISLX] = AXIS_MIN; }
			else if (up) { buttonStatus[AXISLY] = AXIS_MIN; buttonStatus[AXISLX] = AXIS_MID; }
			else if (down) { buttonStatus[AXISLY] = AXIS_MAX; buttonStatus[AXISLX] = AXIS_MID; }
			else if (left) { buttonStatus[AXISLX] = AXIS_MIN; buttonStatus[AXISLY] = AXIS_MID; }
			else if (right) { buttonStatus[AXISLX] = AXIS_MAX; buttonStatus[AXISLY] = AXIS_MID; }
			else { buttonStatus[AXISLX] = AXIS_MID; buttonStatus[AXISLY] = AXIS_MID; }
			break;

		case RIGHT_ANALOG:
			buttonStatus[AXISLX] = AXIS_MID;
			buttonStatus[AXISLY] = AXIS_MID;
			buttonStatus[BUTTONUP] = 0;
			buttonStatus[BUTTONDOWN] = 0;
			buttonStatus[BUTTONLEFT] = 0;
			buttonStatus[BUTTONRIGHT] = 0;

			if (up && right) { buttonStatus[AXISRY] = AXIS_MIN; buttonStatus[AXISRX] = AXIS_MAX; }
			else if (up && left) { buttonStatus[AXISRY] = AXIS_MIN; buttonStatus[AXISRX] = AXIS_MIN; }
			else if (down && right) { buttonStatus[AXISRY] = AXIS_MAX; buttonStatus[AXISRX] = AXIS_MAX; }
			else if (down && left) { buttonStatus[AXISRY] = AXIS_MAX; buttonStatus[AXISRX] = AXIS_MIN; }
			else if (up) { buttonStatus[AXISRY] = AXIS_MIN; buttonStatus[AXISRX] = AXIS_MID; }
			else if (down) { buttonStatus[AXISRY] = AXIS_MAX; buttonStatus[AXISRX] = AXIS_MID; }
			else if (left) { buttonStatus[AXISRX] = AXIS_MIN; buttonStatus[AXISRY] = AXIS_MID; }
			else if (right) { buttonStatus[AXISRX] = AXIS_MAX; buttonStatus[AXISRY] = AXIS_MID; }
			else { buttonStatus[AXISRX] = AXIS_MID; buttonStatus[AXISRY] = AXIS_MID; }
			break;

		case DIGITAL:
		default:
			buttonStatus[AXISLX] = AXIS_MID;
			buttonStatus[AXISLY] = AXIS_MID;
			buttonStatus[AXISRX] = AXIS_MID;
			buttonStatus[AXISRY] = AXIS_MID;
			buttonStatus[BUTTONUP] = up;
			buttonStatus[BUTTONDOWN] = down;
			buttonStatus[BUTTONLEFT] = left;
			buttonStatus[BUTTONRIGHT] = right;
			break;
	}
}
