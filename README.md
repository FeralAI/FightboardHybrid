# Fightboard Hybrid Firmware

Custom firmware for the Fightboard and Fightboard MX by thnikk.

## Introduction

The stock Fightboard firmware supports XInput and a bunch of extra features like profiles, remapping buttons, setting LEDs, etc. Well...this firmware has none of that and is instead focused on performance and enhancing system compatibility. It currently supports XInput (PC, Android, Raspberry Pi) and Nintendo Switch modes.

## Features

> NOTE: Any persistent configuration will be cleared when reflashing the controller!

### Input Modes

To change the input mode, hold one of the following buttons as the controller is plugged in:

* `SELECT` - Nintendo Switch
* `START` - XInput

Input mode is persistent across power cycles.

### D-Pad Modes

You can switch between the 3 stick modes while the controller is in use by pressing `START + SELECT +` one of the following:

* `UP` - D-Pad
* `LEFT` - Emulate Left Analog stick
* `RIGHT` - Emulate Right Analog stick

D-Pad mode is persistent across power cycles.

## TODO List

* [x] XInput support
* [x] Switch support
* [ ] Add LED support
* [ ] Review button state logic
* [ ] Optimize HID report construction
* [ ] Break apart XInput and Switch USB code
* [ ] Document development setup

## Acknowledgments

I'd like to thank [Jack Reitano, a.k.a. thnikk on Etsy](https://www.etsy.com/people/thnikk), the creator of the Fightboard controllers. It's great he used common Arduino parts, and he was also kind enough to provide me some support while making this.

As for code, the base of this project was adapted from [CrazyRedMachine's LUFAHybridFightstick](https://github.com/CrazyRedMachine/LUFAHybridFightstick), which was based on [fluffymadness' ATMega32U4-Switch-Fightstick](https://github.com/fluffymadness/ATMega32U4-Switch-Fightstick) and [bootsector's XInputPadMicro](https://github.com/bootsector/XInputPadMicro). There's not a whole lot of the original sketch left, but a lot of the glue is still here and it was a great starting off point.
