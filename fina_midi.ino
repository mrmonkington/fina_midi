/*
  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
  https://lab.arts.ac.uk/books/physical-computing/page/using-arduino-leonardo-to-send-usb-midi-data
  https://arduino.programmingpedia.net/en/tutorial/9406/midi-communication - midi msg reference
*/

#include <MIDIUSB.h>
#include <MIDIUSB_Defs.h>
#include <frequencyToNote.h>
#include <pitchToFrequency.h>
#include <pitchToNote.h>

const int change_threshold = 5;
const int deadzone = 5;
const int sensor_timeout = 5;

// number of sensors
int s_count = 10;

// combined these provide a GPIO pin -> midi channel mapping
int sensors[] =  { A0, A1, A2, A3, A4, A5, A6, A7, A8, A9 };
int channels[] = { 25, 26, 27, 28, 29, 20, 21, 22, 23, 24 };

// used for change detection - you don't want to output constantly
int last_readings[10];

// is this channel being actively controlled (used by debounce)
int active[] =   {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 };

char op[11] = "          ";
int midi_channel = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  // at start shouldn't spam readings so preload last_readings
  for( int i = 0; i < s_count; i ++ ) {
    last_readings[i] = analogRead(sensors[i]);
  }
}

byte inline raw_to_midiCC(int val) {
  return (byte) (val * 128 / 1024);
}

// the loop routine runs over and over again forever:
void loop() {
  int new_readings[10];
  int sensor_value = 0;
  for( int i = 0; i < s_count; i ++ ) {
    sensor_value = analogRead(sensors[i]);
    //new_readings[i] = (byte)(sensor_value * 128 / 1024);
    new_readings[i] = sensor_value;

    // have we moved?
    if (new_readings[i] < last_readings[i] - change_threshold
      || new_readings[i] > last_readings[i] + change_threshold ) {
        // keep resetting the sensor timeout as we're definitely moving
        active[i] = sensor_timeout;
    } else {
      // since the change is very small this *could* be a motionless
      // pot and we're just seeing a bit of jitter, so we count down the active state
      if (active[i] > 0) {
        active[i] --;
      }
    }

    // we only update last reading if the sensor is active, otherwise we can get stuck if pot is
    // only ever moved slowly
    if (active[i] > 0) {
      last_readings[i] = new_readings[i];
    }
  }

  bool changed = false;
  for( int i = 0; i < s_count; i++ ) {
    if( active[i] > 0 ) { 
      controlChange(0, channels[i], raw_to_midiCC(new_readings[i]));
      op[i] = '0' + (int)(new_readings[i] * 10 / 1024);
      changed = true;
    } else {
      op[i] = 'x';
    }
  }

  // write some simple debug
  if( changed ) {
    MidiUSB.flush();
    Serial.println(op);
  }
  // delay 10ms in between reads for stability ~= 100hz
  // todo use a scheduler
  // todo read external midi clock
  delay(10);
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

