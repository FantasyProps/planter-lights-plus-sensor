// NeoPixel Planter Lights (c) 2017 John Griffiths
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      40

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // setup light sensor and serial
  pinMode(0, INPUT);
  Serial.begin(9600);

  // setup and run neopixel lights
  pixels.begin(); // This initializes the NeoPixel library.
}

void lightOn() {
  int i;
  int pixelPoint[] = {0,0,0,0,0,0,0,0,
                  1,1,1,1,1,1,1,1,
                  0,0,0,0,0,0,0,0,
                  1,1,1,1,1,1,1,1,
                  0,0,0,0,0,0,0,0,
                  1,1,1,1,1,1,1,1};

  for (i = 0; i < 40; i++) {

    if (pixelPoint[i] == 1) {
      pixels.setPixelColor(i, pixels.Color(255,0,0));
    } else {
      pixels.setPixelColor(i, pixels.Color(0,0,255));
    }

    pixels.show();
  }
}

void lightOff() {
  int i;

  for (i = 0; i < 40; i++) {
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    pixels.show();
  }
}

void loop() {
  int v = analogRead(0);
  Serial.println(v);

  if (v > 300) {
    Serial.println("dark");
    lightOn();
  } else {
    Serial.println("light");
    lightOff();
  }

  delay(1000);
}

