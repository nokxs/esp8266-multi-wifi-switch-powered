# Multi Wifi Switch - Powered

The multi wifi switch is based on an ESP 8266 Node MCU Board and the [Homie ESP Library](https://github.com/homieiot/homie-esp8266), which uses MQTT. It has *4 Buttons* and *3 LEDs* and therefore uses most of the usable ESP 8266 pins. The pin of a button can easily be used for a LED and vice versa. Any combination ranging from 7 buttons to 7 LEDs is conceivable.

The box itself is relativly "dumb". It relies on an external controller (like [Home Assistant](https://www.home-assistant.io/), [IoBroker](https://www.iobroker.net/), ...) for controlling the switch.

## Buttons

Three different button presses are supported:

- Short single press
- Long single press
- Double press

## LEDs

A LED can be in one of five states:

- `OFF`: The LED is off
- `ON`: The LED is on
- `SHORT_PULSE`: The LED is blinking fast
- `LONG_PULSE`: The LED is blinking slow
- `TRIPPLE_PULSE`: The LED is blinking three times fast, makes a break and is blinking fast again

## Circuit schematic

![Schematic](doc/MultiWifiSwitchPowered_Circuit.png)

## Final box

![Final box](doc/final_box.jpg)