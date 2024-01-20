#include <SoftwareSerial.h>
#include <MIDI.h>

SoftwareSerial midiSerial(2, 3);  // RX, TX
MIDI_CREATE_INSTANCE(SoftwareSerial, midiSerial, MIDI);


void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(115200);
  Serial.println("INIT");
}

void loop() {
  if (MIDI.read()) {
    byte type = MIDI.getType();
    byte channel = MIDI.getChannel();
    byte number = MIDI.getData1();

    // type == 250: start
    // type == 252: stop
    if (type != 160 && type != 248) { // ignore aftertouch & timing
      Serial.print(type);
      Serial.print("\t");
      Serial.print(channel);
      Serial.print("\t");
      Serial.println(number);
      delay(1);
    }
  }
}