#include <SoftwareSerial.h>
#include <MIDI.h>
#include <Adafruit_NeoPixel.h>
#include <RGBConverter.h>


#define NUMPIXELS 45

SoftwareSerial midiSerial(2, 3);  // RX, TX
MIDI_CREATE_INSTANCE(SoftwareSerial, midiSerial, MIDI);

Adafruit_NeoPixel pixels(NUMPIXELS, 12, NEO_GRB + NEO_KHZ800);
RGBConverter rgbconv;

float hue;
byte rgb[] = { 0, 0, 0 };

int offset1 = 0;
int offset2 = 0;

void setup() {
  pixels.begin();
  pixels.clear();

  pixels.fill(pixels.Color(20, 20, 20));
  pixels.show();
  delay(10);
  
  pixels.fill(pixels.Color(0, 0, 0));
  pixels.show();
  MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop() {
  if (MIDI.read()) {
    byte type = MIDI.getType();
    byte channel = MIDI.getChannel();
    byte number = MIDI.getData1();

    // type == 250: start
    // type == 252: stop
    if (channel == 10) {
      if (type == 144) {
        if (number == 36) {
          hue = ((float)random(0, 100)) / 100.0;
          rgbconv.hsvToRgb(hue, 1, 0.01, rgb);
          pixels.fill(pixels.Color(rgb[0], rgb[1], rgb[2]));
          pixels.show();
        } else if (number == 37) {
          hue = ((float)random(0, 100)) / 100.0;
          rgbconv.hsvToRgb(hue, 1, 0.01, rgb);
          offset1 += 1;
          offset1 %= 5;
          for (int i = offset1; i < 45+offset1; i+= 5) {
            pixels.setPixelColor(i, pixels.Color(rgb[0], rgb[1], rgb[2]));
          } 
          pixels.show();
        } else if (number == 38) {
          hue = ((float)random(0, 100)) / 100.0;
          rgbconv.hsvToRgb(hue, 1, 0.01, rgb);
          offset2 += 1;
          offset2 %= 9;
          for (int i = offset2; i < 45+offset2; i+= 9) {
            pixels.setPixelColor(i, pixels.Color(rgb[0], rgb[1], rgb[2]));
          } 
          pixels.show();
        }
      } else if (type == 128) {
        pixels.fill(pixels.Color(0, 0, 0));
        pixels.show();
      }
    }
  }
}