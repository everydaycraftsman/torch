// Torch sketch for driving 12 LED NeoPixel ring with various animations
// 2020 Benton Mize

// Built on:
// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define NEO_PIN   6
#define NUMPIXELS 12

Adafruit_NeoPixel pixels(NUMPIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800);

#define NUM_COLORS 11

uint32_t colors[] = {
  pixels.Color(255, 0, 0),    // red
  pixels.Color(255, 128, 0),   // orange
  pixels.Color(255, 255, 0),   // yellow
  pixels.Color(128, 255, 0),   // light green
  pixels.Color(0, 255, 0),     // green
  pixels.Color(255, 128, 0),   // teal
  pixels.Color(0, 255, 255),   // marine
  pixels.Color(0, 0, 255),      // blue
  pixels.Color(127, 0, 255),   // purple
  pixels.Color(255, 0, 255),   // magenta
  pixels.Color(255, 0, 127),   // pink
};

#define ARC_BRIGHT_INT 5
#define ARC_MAX_BRIGHT 255
#define ARC_MIN_BRIGHT_INT ARC_MAX_BRIGHT / 16
#define ARC_INIT_LOOPS 15
uint8_t arcCount = 0;
uint16_t arcDelay = ARC_INIT_LOOPS;
int arcBrightness = 0;
int arcMinBrightness = 0;
boolean arcBrightnessRising = true;
boolean arcComplete = false;

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels.begin(); // init NeoPixel ring object (REQUIRED)
}

void randomRainbow() {
  pixels.setBrightness(64);
  
  int colorIndex = random(0, NUM_COLORS - 1);

  pixels.fill(colors[colorIndex], 0, NUMPIXELS);

  pixels.show();   // Send the updated pixel colors to the hardware.

  delay(250); // Pause before next pass through loop
}

void arcReactor() {
  uint32_t reactorColor = pixels.Color(0, 255, 255);
  
  pixels.fill(reactorColor, 0, NUMPIXELS); 

  pixels.setBrightness(arcBrightness);

  if(!arcComplete) {
    if(arcBrightnessRising) {
      arcBrightness += ARC_BRIGHT_INT;
    } else {
      arcBrightness -= ARC_BRIGHT_INT;
    }
  
    if(arcBrightness > ARC_MAX_BRIGHT) {
      arcBrightnessRising = false;
      arcBrightness = ARC_MAX_BRIGHT;
      if(arcCount >= ARC_INIT_LOOPS) {
        arcComplete = true;
      } else {
        arcDelay -= 1;
      }
    } else if(arcBrightness < arcMinBrightness) {
      arcBrightnessRising = true;
      arcMinBrightness += ARC_MIN_BRIGHT_INT;
      arcBrightness = arcMinBrightness;
      arcCount++;
    }

    delay(arcDelay);
  }

  pixels.show();
}

void loop() {
//  randomRainbow();  
  arcReactor();
}
