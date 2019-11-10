# LED-Fackel
Ich bin auf dem EH18 auf die Idee gestoßen worden, eine LED-Streifen auf ein Papprohr aufzubringen, um so die vollen 5m bespielen zu können ohne ständig ab- und aufwickeln zu müssen. Die Anschlüsse für 5V werden fest verbaut und später mittels Stecker einfach an Strom anzuschließen sein. Für die "Leuchtprogramme" wird ein ESP verbaut, der ebenfalls über den 5V Anschluss bestromt wird. 

## Material
  * Versandrolle aus Pappe (D=80mm; L=600mm(?); von Staples)
  * 5m LED-Strip (WS2812b; Amazon)
  * Wemos D1 mini (ESP8266)
  * Kondensator (1000 µF)
  * Widerstand (470 Ohm)
  * Kabel (Für Strom und Daten)
  * Netzteil 5V (bisher max. 2A --> Maximale Hellifkeit nicht höher als 10)
  * XT30 für Verbindung Netzteil-Fackel

## Aufbau
folgt

## Code
* "Fakel_old" enthält Skript mit diversen Effekten, die nicht alle laufen. Anschließend wurde alles noch einmal neu überarbeitet. Daher ist dieses Skript nicht aktuell, soll nur als "Effekt-Archiv" dienen
* Aktuelle, lauffähige Version liegt in "Torch" auf Branch master

Noch nicht eingebaut: Sinnvolle Programmwahl über Taster oder anders Interface

## Effekte
Die meisten Effekte habe ich [hier](https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/#LEDStripEffectBlinkingHalloweenEyes) gefunden. Die übrigen Effekte haben einen entsprechenden Vermerk für die Quelle oder sind selbst entwickelt.

* FadeInOut: Ein- und Ausblenden aller Pixel in vorgegebener Farbe
* CyclonBounce: Ein "Auge" in vorgegebener Farbe wanderd entlang des Strips und zurück
* Twinkle: Zwinkern vorgegebener Pixelanzahl in vorgegebener Farbe
* TwinkleRandom: Zwinkern vorgegebener Pixelanzahl in beliebiger Farbe
* Sparkle: Funkeln vorgegebener zufälliger Pixelanzahl in vorgegebener Farbe
* ColorWipe: Pixel werden der Reihen nach in vorgegebener Farbe eingeschaltet
* RainbowCycle: Regenbogen wanderd entlang des strips
* TheaterChase
* TheaterChaseRainbow
* Fire: Entspricht dem eigentlichen Fackel-Vorhaben und basiert auf [Fire2012 by Mark Kriegsman](https://github.com/FastLED/FastLED/blob/master/examples/Fire2012/Fire2012.ino)
* MeteorRain: umgeschrieben entsprechend der LED- Anordnung
* Rain: Regentropfen
* Plasma: [Neopixelplasma by John Ericksen](https://github.com/johncarl81/neopixelplasma) 

Weitere Ideen:
* Meteor Rain mit mehr als einem Meteor
* AirBubbles




