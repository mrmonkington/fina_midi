all: build/arduino.avr.leonardo/fina_midi.ino.elf

build/arduino.avr.leonardo/fina_midi.ino.elf: fina_midi.ino
	arduino-cli --fqbn arduino:avr:leonardo compile fina_midi.ino

install: build/arduino.avr.leonardo/fina_midi.ino.elf
	arduino-cli  -p /dev/ttyACM0 --fqbn arduino:avr:leonardo upload fina_midi.ino

