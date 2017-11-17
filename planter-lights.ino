// NeoPixel Planter Lights (c) 2017 John Griffiths
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

// Include necessary libraries
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Set which digital pin we will use for the fan
const int FANPIN       10

// Which pin on the arduino is connected to the neopixel grid?
#define PIN            6

// How many neopixels are on the grid?
#define NUMPIXELS      40

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Setup light sensor
  pinMode(0, INPUT);
  
  // Activate serial console for debug output
  Serial.begin(9600);

  // Initialize neopixel library
  pixels.begin();
  
  // Setup pin for external fan
  pinMode(FANPIN, OUTPUT);
}

void lightOn() {
  // Turn on FAN
  digitalWrite(FANPIN, HIGH);
  
  // Setup grid
  int i;
  int pixelPoint[] = {0,0,0,0,0,0,0,0,
                  1,1,1,1,1,1,1,1,
                  0,0,0,0,0,0,0,0,
                  1,1,1,1,1,1,1,1,
                  0,0,0,0,0,0,0,0,
                  1,1,1,1,1,1,1,1};

  // Turn on each neopixel based on the pixelPoint integer, 1 = Red, 0 = Blue
  for (i = 0; i < 40; i++) {
    
    // Set color
    if (pixelPoint[i] == 1) {
      pixels.setPixelColor(i, pixels.Color(255,0,0));
    } else {
      pixels.setPixelColor(i, pixels.Color(0,0,255));
    }

    // Turn on neopixel
    pixels.show();
  }
}

void lightOff() {
  // Turn off FAN
  digitalWrite(FANPIN, LOW);
  
  // Turn off all neopixels
  int i;
  for (i = 0; i < 40; i++) {
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    pixels.show();
  }
}

void loop() {
  // Read light sensor value
  int v = analogRead(0);
  
  // Send light sensor value to console
  Serial.println(v);

  // If lightsensor > 300, turn on lights, otherwise keep them off
  if (v > 300) {
    Serial.println("dark");
    lightOn();
  } else {
    Serial.println("light");
    lightOff();
  }

  // Loop interval
  delay(2000);
}

