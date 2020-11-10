#ifndef ARC_H
#define ARC_H

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#define ARC_BRIGHT_INT 5
#define ARC_MAX_BRIGHT 128
#define ARC_MIN_BRIGHT_INT ARC_MAX_BRIGHT / 16
#define ARC_INIT_LOOPS 15

void arcReactor(Adafruit_NeoPixel& pixels);

#endif