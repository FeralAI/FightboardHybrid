#ifndef _FIGHTBOARD_
#define _FIGHTBOARD_

#include "Mapping.h"
#include "../XS_HID.h"

#define BUTTON_INDICES 21
#define PORT_COUNT 5

// Pin mappings
#define PORT_PIN_UP      PF4 // A3
#define PORT_PIN_DOWN    PF6 // A1
#define PORT_PIN_LEFT    PF5 // A2
#define PORT_PIN_RIGHT   PF7 // A0
#define PORT_PIN_P1      PD1 // 2/SDA
#define PORT_PIN_P2      PD0 // 3/SCL
#define PORT_PIN_P3      PE6 // 7
#define PORT_PIN_P4      PB5 // 9
#define PORT_PIN_K1      PB6 // 10
#define PORT_PIN_K2      PB7 // 11
#define PORT_PIN_K3      PD6 // 12
#define PORT_PIN_K4      PC7 // 13
#define PORT_PIN_SELECT  PD7 // 6
#define PORT_PIN_START   PF1 // A4
#define PORT_PIN_HOME    PB4 // 8
#define PORT_PIN_CAPTURE PD3 // 1
#define PORT_PIN_L3      PD4 // 4
#define PORT_PIN_R3      PF0 // A5

#define PIN_UP          A3
#define PIN_DOWN        A1
#define PIN_LEFT        A2
#define PIN_RIGHT       A0
#define PIN_P1          2   // XInput X     / Switch Y
#define PIN_P2          3   // XInput Y     / Switch X
#define PIN_P3          7   // XInput RB    / Switch R
#define PIN_P4          9   // XInput LB    / Switch L
#define PIN_K1          10  // XInput A     / Switch B
#define PIN_K2          11  // XInput B     / Switch A
#define PIN_K3          12  // XInput RT    / Switch ZR
#define PIN_K4          13  // XInput LT    / Switch ZL
#define PIN_SELECT      6   // XInput Back  / Switch -
#define PIN_START       A4  // XInput Start / Switch +
#define PIN_HOME        8
#define PIN_CAPTURE     1
#define PIN_L3          4
#define PIN_R3          A5

// Input masks
#define PORTB_INPUT_MASK 0b11110000
#define PORTC_INPUT_MASK 0b10000000
#define PORTD_INPUT_MASK 0b11011011
#define PORTE_INPUT_MASK 0b01000000
#define PORTF_INPUT_MASK 0b11110011

// Index of register state in read results
#define PORTB_INDEX 0
#define PORTC_INDEX 1
#define PORTD_INDEX 2
#define PORTE_INDEX 3
#define PORTF_INDEX 4

class Fightboard: public ControlBoard {
	public:
		void setupPins() {
			// Set to input (invert mask to set to 0)
			DDRB = DDRB & ~PORTB_INPUT_MASK;
			DDRC = DDRC & ~PORTC_INPUT_MASK;
			DDRD = DDRD & ~PORTD_INPUT_MASK;
			DDRE = DDRE & ~PORTE_INPUT_MASK;
			DDRF = DDRF & ~PORTF_INPUT_MASK;

			// Set to high/pullup
			PORTB = PORTB | PORTB_INPUT_MASK;
			PORTC = PORTC | PORTC_INPUT_MASK;
			PORTD = PORTD | PORTD_INPUT_MASK;
			PORTE = PORTE | PORTE_INPUT_MASK;
			PORTF = PORTF | PORTF_INPUT_MASK;
		}

		void getPortStates(uint8_t portStates[]) {
			portStates[PORTB_INDEX] = PINB;
			portStates[PORTC_INDEX] = PINC;
			portStates[PORTD_INDEX] = PIND;
			portStates[PORTE_INDEX] = PINE;
			portStates[PORTF_INDEX] = PINF;
		}
};

ButtonMapping Fightboard::MapDpadUp(PORTF_INDEX, PORT_PIN_UP, BUTTONUP);
ButtonMapping Fightboard::MapDpadDown(PORTF_INDEX, PORT_PIN_DOWN, BUTTONDOWN);
ButtonMapping Fightboard::MapDpadLeft(PORTF_INDEX, PORT_PIN_LEFT, BUTTONLEFT);
ButtonMapping Fightboard::MapDpadRight(PORTF_INDEX, PORT_PIN_RIGHT, BUTTONRIGHT);
ButtonMapping Fightboard::MapButtonP1(PORTD_INDEX, PORT_PIN_P1, BUTTONY);
ButtonMapping Fightboard::MapButtonP2(PORTD_INDEX, PORT_PIN_P2, BUTTONX);
ButtonMapping Fightboard::MapButtonP3(PORTE_INDEX, PORT_PIN_P3, BUTTONRB);
ButtonMapping Fightboard::MapButtonP4(PORTB_INDEX, PORT_PIN_P4, BUTTONLB);
ButtonMapping Fightboard::MapButtonK1(PORTB_INDEX, PORT_PIN_K1, BUTTONB);
ButtonMapping Fightboard::MapButtonK2(PORTB_INDEX, PORT_PIN_K2, BUTTONA);
ButtonMapping Fightboard::MapButtonK3(PORTD_INDEX, PORT_PIN_K3, BUTTONRT);
ButtonMapping Fightboard::MapButtonK4(PORTC_INDEX, PORT_PIN_K4, BUTTONLT);
ButtonMapping Fightboard::MapButtonSelect(PORTD_INDEX, PORT_PIN_SELECT, BUTTONSELECT);
ButtonMapping Fightboard::MapButtonStart(PORTF_INDEX, PORT_PIN_START, BUTTONSTART);
ButtonMapping Fightboard::MapButtonCapture(PORTD_INDEX, PORT_PIN_CAPTURE, BUTTONCAPTURE);
ButtonMapping Fightboard::MapButtonLogo(PORTB_INDEX, PORT_PIN_HOME, BUTTONHOME);
ButtonMapping Fightboard::MapButtonL3(PORTD_INDEX, PORT_PIN_L3, BUTTONL3);
ButtonMapping Fightboard::MapButtonR3(PORTF_INDEX, PORT_PIN_R3, BUTTONR3);

#endif
