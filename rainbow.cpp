#include "rainbow.h"

Color colors[] = {
    {255, 0, 0},        // red
    {255, 128, 0},      // orange
    {255, 255, 0},      // yellow
    {128, 255, 0},      // light green
    {0, 255, 0},        // green
    {255, 128, 0},      // teal
    {0, 255, 255},      // marine
    {0, 0, 255},        // blue
    {127, 0, 255},      // purple
    {255, 0, 255},      // magenta
    {255, 0, 127},      // pink
};

void rainbow(Adafruit_NeoPixel& pixels) {
  pixels.setBrightness(64);
  
  int colorIndex = random(0, NUM_COLORS - 1);

  Color c = colors[colorIndex];

  uint32_t color = pixels.Color(
      c.r,
      c.g,
      c.b
  );

  pixels.fill(color, 0, pixels.numPixels());

  pixels.show();

  delay(500);
}