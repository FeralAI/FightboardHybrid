#ifndef _MAPPING_
#define _MAPPING_

struct ButtonMapping {
	constexpr ButtonMapping(uint8_t i, uint8_t p, uint8_t s)
		: portIndex(i), portPin(p), stateIndex(s) { }
	uint8_t portIndex;  // The index of the port in the cached inputs array
	uint8_t portPin;    // The port pin/index
	uint8_t stateIndex; // The index in the related state array
};

class ControlBoard {
	public:
		/**
		 * Performs pin setup
		 */
		virtual void setupPins();

		/**
		 * Retrieves the input states from all ports
		 */
		virtual inline void getPortStates(uint8_t portStates[]) __attribute__((always_inline));

		/**
		 * Button mappings
		 */
		static ButtonMapping MapDpadUp;
		static ButtonMapping MapDpadDown;
		static ButtonMapping MapDpadLeft;
		static ButtonMapping MapDpadRight;
		static ButtonMapping MapButtonP1;      // XInput X     / Switch Y
		static ButtonMapping MapButtonP2;      // XInput Y     / Switch X
		static ButtonMapping MapButtonP3;      // XInput RB    / Switch R
		static ButtonMapping MapButtonP4;      // XInput LB    / Switch L
		static ButtonMapping MapButtonK1;      // XInput A     / Switch B
		static ButtonMapping MapButtonK2;      // XInput B     / Switch A
		static ButtonMapping MapButtonK3;      // XInput RT    / Switch ZR
		static ButtonMapping MapButtonK4;      // XInput LT    / Switch ZL
		static ButtonMapping MapButtonL3;
		static ButtonMapping MapButtonR3;
		static ButtonMapping MapButtonSelect;
		static ButtonMapping MapButtonStart;
		static ButtonMapping MapButtonLogo;
		static ButtonMapping MapButtonCapture;
};

#endif
