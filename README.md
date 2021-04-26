# Fightboard Hybrid Firmware

Custom firmware for the Fightboard and Fightboard MX by thnikk.

## Introduction

The stock Fightboard firmware supports XInput and a bunch of extra features like profiles, remapping buttons, setting LEDs, etc. Well...this firmware has none of that and is instead focused on performance and enhancing system compatibility. It currently supports XInput (PC, Android, Raspberry Pi) and Nintendo Switch modes.

## Button Layout

The Fightboard uses a standard 8-button fightstick layout. To make things easy, any references to these buttons will use the `Generic` labels in this documentation.

**Generic:**

```text
P1 P2 P3 P4
K1 K2 K3 K4
```

**XInput**:

```text
X Y RB LB
A B RT LT
```

**Switch**:

```text
Y X  R  L
B A ZR ZL
```

## Features

> NOTE: Any saved configuration will be cleared when reflashing the controller!

### Input Modes

To change the input mode, **hold one of the following buttons as the controller is plugged in:**

* **`SELECT`** for Nintendo Switch
* **`START`** for XInput

Input mode is saved across power cycles.

### D-Pad Modes

You can switch between the 3 modes for the D-Pad **while the controller is in use by pressing one of the following combinations:**

* **`SELECT + START + UP`** - D-Pad
* **`SELECT + START + LEFT`** - Emulate Left Analog stick
* **`SELECT + START + RIGHT`** - Emulate Right Analog stick

D-Pad mode is saved across power cycles.

### LED Modes

By default, the controller will use an Xbox color scheme for XInput and a Super Famicom color scheme for Switch mode. You can also override the color scheme by **holding the following button(s) as the controller is plugged in:**

| LED Effect/Layout | Button(s) | Preview |
| :---------------- | :----: | :----: | :-------------------: | :-----: |
| Xbox | P1 | ![Xbox](.assets/images/XBOX.jpg) |
| Super Famicom | P2 | ![Super Famicom](.assets/images/SFC.jpg) |
| Six Button Fighter (SF and KI) | P3 | ![Six Button Fighter](.assets/images/SIX_BUTTON.jpg) |
| Guilty Gear Type-A | P4 | ![Guilty Gear Type-A](.assets/images/GG_TYPE_A.jpg) |
| Neo-Geo Straight | K1 | ![Neo-Geo Straight](.assets/images/NEOGEO_STRAIGHT.jpg) |
| Neo-Geo Curved | K2 | ![Neo-Geo Curved](.assets/images/NEOGEO_CURVED.jpg) |
| Neo-Geo Modern (2x2 layout) | K3 | ![Neo-Geo Modern](.assets/images/NEOGEO_MODERN.jpg) |
| Guilty Gear Custom (my layout) | K4 | ![Guilty Gear Custom](.assets/images/GG_CUSTOM.jpg) |
| Static Rainbow | P1 + P2 + P3 + P4 | ![Static Rainbow](.assets/images/STATIC_RAINBOW.jpg) |

The overridden LED mode will be saved across power cycles, and **can be cleared by holding `R3` when plugging the controller in.**

## TODO List

* [x] XInput support
* [x] Switch support
* [x] Add LED support
* [ ] Review button state logic
* [ ] Optimize HID report construction
* [ ] Break apart XInput and Switch USB code
* [ ] Document development setup

## Acknowledgments

I'd like to thank [Jack Reitano, a.k.a. thnikk on Etsy](https://www.etsy.com/people/thnikk), the creator of the Fightboard controllers. It's great he used common Arduino parts, and he was also kind enough to provide me some support while making this.

As for code, the base of this project was adapted from [CrazyRedMachine's LUFAHybridFightstick](https://github.com/CrazyRedMachine/LUFAHybridFightstick), which was based on [fluffymadness' ATMega32U4-Switch-Fightstick](https://github.com/fluffymadness/ATMega32U4-Switch-Fightstick) and [bootsector's XInputPadMicro](https://github.com/bootsector/XInputPadMicro). There's not a whole lot of the original sketch left, but a lot of the glue is still here and it was a great starting off point.
