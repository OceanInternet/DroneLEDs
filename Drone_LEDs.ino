#include "FastLED.h"

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few
// of the kinds of animation patterns you can quickly and easily
// compose using FastLED.
//
// This example also shows one easy way to define multiple
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define MOTOR1_DATA_PIN    2
#define MOTOR2_DATA_PIN    3
#define MOTOR3_DATA_PIN    6
#define MOTOR4_DATA_PIN    5

#define LED_TYPE         WS2811
#define COLOR_ORDER      BRG
#define LEDS_PER_STRIP   2
#define NUMBER_OF_STRIPS 4

CRGB leds[LEDS_PER_STRIP * NUMBER_OF_STRIPS];

#define BRIGHTNESS         255
//#define FRAMES_PER_SECOND  120

#define prt CRGB::Red
#define sbd CRGB::Green
#define aft CRGB::White
#define collisionFlashes 4

#define pause 600


void setup() {
  delay(3000); // 3 second delay for recovery

    FastLED.addLeds<LED_TYPE,MOTOR1_DATA_PIN,COLOR_ORDER>(leds, 0 * LEDS_PER_STRIP, LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<LED_TYPE,MOTOR2_DATA_PIN,COLOR_ORDER>(leds, 1 * LEDS_PER_STRIP, LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<LED_TYPE,MOTOR3_DATA_PIN,COLOR_ORDER>(leds, 3 * LEDS_PER_STRIP, LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<LED_TYPE,MOTOR4_DATA_PIN,COLOR_ORDER>(leds, 2 * LEDS_PER_STRIP, LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.clear();
  FastLED.setBrightness(BRIGHTNESS);
}

void loop()
{
  doNavLights();

  FastLED.delay(pause);

  doCollisionLights();

  FastLED.delay(pause);
}

void doNavLights() {
  int lastLedIndex = (LEDS_PER_STRIP * NUMBER_OF_STRIPS) - 1;

    for (int i=0; i < LEDS_PER_STRIP; i++) {
      leds[i]                = aft;
      leds[lastLedIndex - i] = aft;
      
      leds[LEDS_PER_STRIP + i]                = prt;
      leds[lastLedIndex - LEDS_PER_STRIP - i] = sbd;

      FastLED.show();
      FastLED.delay(100);

      leds[i]                  = CRGB::Black;
      leds[i + LEDS_PER_STRIP] = CRGB::Black;

      leds[lastLedIndex - i]                  = CRGB::Black;
      leds[lastLedIndex - LEDS_PER_STRIP - i] = CRGB::Black;

      FastLED.show();
    }
}

void doCollisionLights() {

  for (int count = 0; count < collisionFlashes; count++) {

    for (int i = 0; i < LEDS_PER_STRIP * NUMBER_OF_STRIPS; i++) {
      leds[i] = CRGB::White;
    }
    FastLED.show();
    FastLED.delay(1);

    for (int i = 0; i < LEDS_PER_STRIP * NUMBER_OF_STRIPS; i++) {
      leds[i] = CRGB::Black;
    }
    FastLED.show();
    FastLED.delay(49);
  }
}

