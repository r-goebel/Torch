# LED torch
On the EH18 I got the idea to put an LED strip on a cardboard tube to use the full 5m without having to unwind and wind it all the time. The connections for 5V will be installed permanently and can easily be plugged in later. For the effects an ESP is installed, which is also powered via the 5V connection. 

## Material
  * cardboard shipping roll (D=80mm; L=600mm(?))
  * 5m LED Strip (WS2812b; Amazon)
  * Wemos D1 mini (ESP8266)
  * Capacitor (1000 µF)
  * Resistance (470 Ohm)
  * Cable (For power and data)
  * Power supply 5V (up to now max. 2A --> Maximum brightness not higher than 10)
  * XT30 for connection between power supply and torch

## Effects
I found most of the ideas for effects [here](https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/#LEDStripEffectBlinkingHalloweenEyes) and [here](https://repos.ctdo.de/starcalc/ESP8266-RGB5m). The remaining effects have a corresponding note for the reference.

* FadeInOut: Show and hide all pixels in default color
* Cylon: An "eye" in a given color moving along the strip and back
* Twinkle: Twinkle a given number of pixels in a given or random color
* Sparkle: sparkle in given or random color
* ColorWipe: Pixels are switched on one after the other in the specified color.
* RainbowCycle: Rainbow moving along the strips
* TheaterChase: including Rainbow option
* Fire: based on [Fire2012 by Mark Kriegsman](https://github.com/FastLED/FastLED/blob/master/examples/Fire2012/Fire2012.ino)
* MeteorRain
* Rain

New Ideas:
* AirBubbles




