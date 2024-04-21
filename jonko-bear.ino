/*
Jonko Bear

Rotates colors of two sets of WS2812 LEDs and creates smoldering effect on one LED. Uses 
the FastLED library only.

2024 by knokkelpronk
*/

#include "FastLED.h"

uint8_t hue;

// defines pins for led groups
#define DATA_PIN1    12
#define DATA_PIN2    11
#define DATA_PIN3    10

#define LED_TYPE    WS2812

// to accomplish shifting the color cycle between groups 1 and 2
#define COLOR_ORDER GRB
#define COLOR_ORDER2 RGB

#define NUM_LEDS    8
#define NUM_LEDS2    8
#define NUM_LEDS3    1
#define BRIGHTNESS  2000
 
CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS2];
CRGB leds3[NUM_LEDS3];

 
void setup() {
  Serial.begin(9600); // open the serial port at 9600 bps:

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN1,COLOR_ORDER>(leds1, NUM_LEDS)
      .setCorrection(TypicalLEDStrip)
    .setDither(BRIGHTNESS < 255);
  FastLED.addLeds<LED_TYPE,DATA_PIN2,COLOR_ORDER2>(leds2, NUM_LEDS2)
    .setCorrection(TypicalLEDStrip)
    .setDither(BRIGHTNESS < 255);
      FastLED.addLeds<LED_TYPE,DATA_PIN3,GRB>(leds3, NUM_LEDS3)
    .setCorrection(TypicalLEDStrip)
    .setDither(BRIGHTNESS < 255);
 
  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);



}
 
 
void loop()
{
  pride1();
  pride2();
  jonko();
  
  FastLED.show();  
}
 
 
// This function draws rainbows with an ever-changing,
// widely-varying set of parameters.
void pride1() 
{
  static uint16_t sPseudotime = 20;
  static uint16_t sLastMillis = 500;
  static uint16_t sHue16 = 300;
 
  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(50, 23, 60);
 
  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);
  
  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5,9);
  uint16_t brightnesstheta16 = sPseudotime;
  
  for( uint16_t i = 0 ; i < NUM_LEDS; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;
 
    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;
 
    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);
    
    CRGB newcolor = CHSV( hue8, sat8, bri8);
    
    uint16_t pixelnumber = i;
    pixelnumber = (NUM_LEDS-1) - pixelnumber;
    
    nblend( leds1[pixelnumber], newcolor, 64);
  }
}

void pride2() 
{
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;
 
  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);
 
  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);
  
  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5,9);
  uint16_t brightnesstheta16 = sPseudotime;
  
  for( uint16_t i = 0 ; i < NUM_LEDS-1; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;
 
    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;
 
    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);
    
    CRGB newcolor = CHSV( hue8, sat8, bri8);
    
    uint16_t pixelnumber = i;
    pixelnumber = (NUM_LEDS-2) - pixelnumber;
    
    nblend( leds2[pixelnumber], newcolor, 64);
    
  }
}

void jonko() 
{
  if ()
    hue++;
    fill_solid(leds3, NUM_LEDS3, CHSV(0, 255, hue));
    Serial.print(hue);
      Serial.println();        // carriage return after the last label


  FastLED.show();
  

}
