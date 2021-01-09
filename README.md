# Fina Midi

An arduino based midi controller, using an Arduino Leonardo, 10x10k pots and a VegaFina cigar box.

## Quickstart

Install [Arduino Cli](https://arduino.github.io/arduino-cli/latest/installation/).

Install your board:

```
arduino-cli core install avr
```

Build and push the code:

```
git clone git@github.com:mrmonkington/fina_midi
source install_requirements.sh
make
```

Connect your Arduino and upload the code:

```
make install
```

## Notes

  - https://github.com/arduino/ArduinoCore-avr/blob/master/variants/leonardo/pins_arduino.h
  - http://www.arduino.cc/en/Tutorial/AnalogReadSerial
  - https://lab.arts.ac.uk/books/physical-computing/page/using-arduino-leonardo-to-send-usb-midi-data
	- https://www.midi.org/specifications-old/item/table-3-control-change-messages-data-bytes-2
	- http://manpages.ubuntu.com/manpages/bionic/man1/midisnoop.1.html for debugging

Undefined MIDI CC List

 - 3
 - 9
 - 14-15
 - 20-31
 - 85-90
 - 102-119
