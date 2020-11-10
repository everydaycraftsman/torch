#include "arc.h"

uint8_t arcCount = 0;
uint16_t arcDelay = ARC_INIT_LOOPS;
int arcBrightness = 0;
int arcMinBrightness = 0;
boolean arcBrightnessRising = true;
boolean arcComplete = false;

void arcReactor(Adafruit_NeoPixel& pixels) {
  uint32_t reactorColor = pixels.Color(0, 255, 255);
  
  pixels.fill(reactorColor, 0, pixels.numPixels()); 

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
