/*
  MIDI note player

  This sketch shows how to use the serial transmit pin (pin 1) to send MIDI note data.
  If this circuit is connected to a MIDI synth, it will play the notes
  F#-0 (0x1E) to F#-5 (0x5A) in sequence.

  The circuit:
  - digital in 1 connected to MIDI jack pin 5
  - MIDI jack pin 2 connected to ground
  - MIDI jack pin 4 connected to +5V through 220 ohm resistor
  - Attach a MIDI cable to the jack, then to a MIDI synth, and play music.

  created 13 Jun 2006
  modified 13 Aug 2012
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Midi
*/
int noteOff = 0x81;
int noteOn = 0x91;
int sensorPin = A0;
int sensorValue = 0;

void setup() {
  // Set MIDI baud rate:
  Serial.begin(19200);
}

void loop() {
    //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
    sensorValue = analogRead(sensorPin);
    MIDIMessage(noteOn, sensorValue, 0x45);
    MIDIMessage(noteOn, sensorValue + 3, 0x45);
    MIDIMessage(noteOn, sensorValue + 5, 0x45);
    MIDIMessage(noteOn, sensorValue + 7, 0x45);
    delay(1000);
    MIDIMessage(noteOff, sensorValue, 0x00);
    MIDIMessage(noteOff, sensorValue + 3, 0x00);
    MIDIMessage(noteOff, sensorValue + 5, 0x00);
    MIDIMessage(noteOff, sensorValue + 7, 0x00);
    delay(1000);
}

// plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that
// data values are less than 127:
void MIDIMessage(int cmd, int pitch, int velocity) {
  if(pitch >= 128)
  {
    pitch = 127;
  }
  if(pitch == 0)
  {
    pitch = 0;
  }
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}
