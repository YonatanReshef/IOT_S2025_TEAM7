// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Constants
#define PIN        27
#define NUMPIXELS 256
#define BRIGHTNESS 20 
#define DELAYVAL 50 // Time (in milliseconds) to pause between pixels

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);





void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(BRIGHTNESS);
  pixels.clear();
  pixels.show();
}

int loop_num = 0;

void loop() {
  /*
  The following loop test each pixel with white.
  The goal is to make sure that color of every pixels is working properly
  */
  for(int i=0; i<NUMPIXELS; i++) {

    pixels.clear(); // Set all pixel colors to 'off'
    if ( loop_num % 3 == 0) {
        pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    }
    if( loop_num % 3 == 1){
        pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    }
    if(loop_num % 3 == 2){
        pixels.setPixelColor(i, pixels.Color(0, 0, 255));
    }

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }

  loop_num += 1;
  if(loop_num == 3){
      loop_num = 0;
  }
}
