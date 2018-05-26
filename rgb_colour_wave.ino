#define FORCE_SOFTWARE_SPI
#define FORCE_SOFTWARE_PINS
#include "FastSPI_LED2.h"

// Data pin that led data will be written out over
#define DATA_PIN 11

// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define CLOCK_PIN 13

// First and Last leds to illuminate
#define FIRST_LED 0
#define LAST_LED 24

// Cycle delay
#define DELAY 40

// Step size per cycle
#define STEP 18

// LED RGB value for each led in your strip.
CRGB leds[LAST_LED+1];

/******************************************************************************************/
void setup() {

  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, LAST_LED+1);

  Serial.begin(19200);
}

/******************************************************************************************/
void loop() {

   int red, green, blue;
   int i, j;

   while(true)
   {
      for (int i=0; i<768; i=i+STEP)
      {
         j = (i+256) % 768;
         
         // Yellow sector
         if ((i<256) && (i>=0))
         {
            red = 255-i;  // Ramping down
            green = j-0;  // Ramping up
            blue = 0;     // Off
         }
         
         // Cyan sector
         if ((i<512) && (i>=256))
         {
            red = 0;       // Off
            green = 511-i; // Ramping down
            blue = j-255;  // Ramping up
         }
         
         // Magenta sector
         if ((i<768) && (i>=512))
         {
            red = j-511;   // Ramping up
            green = 0;     // Off
            blue = 767-i;  // Ramping down
         }
         
         // Shuffle all the colours along by one
         for (int led=LAST_LED; led > FIRST_LED; led--)
         {
            leds[led].r = leds[led-1].r;
            leds[led].g = leds[led-1].g;
            leds[led].b = leds[led-1].b;
         }
           
         // Add the new colour
         leds[FIRST_LED].r = red;
         leds[FIRST_LED].g = green;
         leds[FIRST_LED].b = blue;

         // Show the leds
         FastLED.show();
         
         // Wait a little bit
         delay(DELAY);
      }
   }
}
   

