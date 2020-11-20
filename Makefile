all: fina_midi.ino
	arduino-cli --fqbn arduino:avr:leonardo compile fina_midi.ino

install:
	arduino-cli  -p /dev/ttyACM0 --fqbn arduino:avr:leonardo upload fina_midi.ino

