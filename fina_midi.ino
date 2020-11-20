// MIDIUSB - Version: 1.0.4


/*
  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
  https://lab.arts.ac.uk/books/physical-computing/page/using-arduino-leonardo-to-send-usb-midi-data
*/

#include <MIDIUSB.h>
#include <MIDIUSB_Defs.h>
#include <frequencyToNote.h>
#include <pitchToFrequency.h>
#include <pitchToNote.h>

int sensors[] = { A0, A1, A2, A3, A4, A5, A6, A7, A8, A9 };
byte last_readings[10];
int s_count = 10;
char op[11] = "          ";
int midi_channel = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
}



// the loop routine runs over and over again forever:
void loop() {
  byte new_readings[10];
  int sensor_value = 0;
  for( int i = 0; i < s_count; i ++ ) {
    sensor_value = analogRead(sensors[i]);
    new_readings[i] = (byte)(sensor_value * 128 / 1024);
    
  }
  bool changed = false;
  for( int i = 0; i < s_count; i++ ) {
    if( new_readings[i] != last_readings[i] ) { 
      controlChange(0, (byte)i + 20, new_readings[i]);
      op[i] = '0' + (int)(new_readings[i] * 10 / 128);
      changed = true;
    } else {
      op[i] = 'x';
    }
    last_readings[i] = new_readings[i];
  }
  if( changed ) {
    MidiUSB.flush();
  }
  // send debug
  //Serial.println(op);
  delay(10); // delay in between reads for stability
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

