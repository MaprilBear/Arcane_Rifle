// /// @file    Fire2012WithPalette.ino
// /// @brief   Simple one-dimensional fire animation with a programmable color palette
// /// @example Fire2012WithPalette.ino

// #include <FastLED.h>

// #define LED_PIN     5
// #define COLOR_ORDER GRB
// #define CHIPSET     WS2811
// #define NUM_LEDS    200

// #define BRIGHTNESS  50
// #define FRAMES_PER_SECOND 60

// bool gReverseDirection = false;

// CRGB leds[NUM_LEDS];

// CRGBPalette16 gPal;

// // Fire2012 by Mark Kriegsman, July 2012
// // as part of "Five Elements" shown here: http://youtu.be/knWiGsmgycY
// //// 
// // This basic one-dimensional 'fire' simulation works roughly as follows:
// // There's a underlying array of 'heat' cells, that model the temperature
// // at each point along the line.  Every cycle through the simulation, 
// // four steps are performed:
// //  1) All cells cool down a little bit, losing heat to the air
// //  2) The heat from each cell drifts 'up' and diffuses a little
// //  3) Sometimes randomly new 'sparks' of heat are added at the bottom
// //  4) The heat from each cell is rendered as a color into the leds array
// //     The heat-to-color mapping uses a black-body radiation approximation.
// //
// // Temperature is in arbitrary units from 0 (cold black) to 255 (white hot).
// //
// // This simulation scales it self a bit depending on NUM_LEDS; it should look
// // "OK" on anywhere from 20 to 100 LEDs without too much tweaking. 
// //
// // I recommend running this simulation at anywhere from 30-100 frames per second,
// // meaning an interframe delay of about 10-35 milliseconds.
// //
// // Looks best on a high-density LED setup (60+ pixels/meter).
// //
// //
// // There are two main parameters you can play with to control the look and
// // feel of your fire: COOLING (used in step 1 above), and SPARKING (used
// // in step 3 above).
// //
// // COOLING: How much does the air cool as it rises?
// // Less cooling = taller flames.  More cooling = shorter flames.
// // Default 55, suggested range 20-100 
// #define COOLING  70

// // SPARKING: What chance (out of 255) is there that a new spark will be lit?
// // Higher chance = more roaring fire.  Lower chance = more flickery fire.
// // Default 120, suggested range 50-200.
// #define SPARKING 150


// void Fire2012WithPalette()
// {
// // Array of temperature readings at each simulation cell
//   static uint8_t heat[NUM_LEDS];

//   // Step 1.  Cool down every cell a little
//     for( int i = 0; i < NUM_LEDS; i++) {
//       heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
//     }
  
//     // Step 2.  Heat from each cell drifts 'up' and diffuses a little
//     for( int k= NUM_LEDS - 1; k >= 2; k--) {
//       heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
//     }
    
//     // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
//     if( random8() < SPARKING ) {
//       int y = random8(7);
//       heat[y] = qadd8( heat[y], random8(160,255) );
//     }

//     // Step 4.  Map from heat cells to LED colors
//     for( int j = 0; j < NUM_LEDS; j++) {
//       // Scale the heat value from 0-255 down to 0-240
//       // for best results with color palettes.
//       uint8_t colorindex = scale8( heat[j], 240);
//       CRGB color = ColorFromPalette( gPal, colorindex);
//       int pixelnumber;
//       if( gReverseDirection ) {
//         pixelnumber = (NUM_LEDS-1) - j;
//       } else {
//         pixelnumber = j;
//       }
//       leds[pixelnumber] = color;
//     }
// }

// // Fire2012 with programmable Color Palette
// //
// // This code is the same fire simulation as the original "Fire2012",
// // but each heat cell's temperature is translated to color through a FastLED
// // programmable color palette, instead of through the "HeatColor(...)" function.
// //
// // Four different static color palettes are provided here, plus one dynamic one.
// // 
// // The three static ones are: 
// //   1. the FastLED built-in HeatColors_p -- this is the default, and it looks
// //      pretty much exactly like the original Fire2012.
// //
// //  To use any of the other palettes below, just "uncomment" the corresponding code.
// //
// //   2. a gradient from black to red to yellow to white, which is
// //      visually similar to the HeatColors_p, and helps to illustrate
// //      what the 'heat colors' palette is actually doing,
// //   3. a similar gradient, but in blue colors rather than red ones,
// //      i.e. from black to blue to aqua to white, which results in
// //      an "icy blue" fire effect,
// //   4. a simplified three-step gradient, from black to red to white, just to show
// //      that these gradients need not have four components; two or
// //      three are possible, too, even if they don't look quite as nice for fire.
// //
// // The dynamic palette shows how you can change the basic 'hue' of the
// // color palette every time through the loop, producing "rainbow fire".

// void setup() {
//   delay(3000); // sanity delay
//   FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
//   FastLED.setBrightness( BRIGHTNESS );

//   // This first palette is the basic 'black body radiation' colors,
//   // which run from black to red to bright yellow to white.
//   //gPal = HeatColors_p;
  
//   // These are other ways to set up the color palette for the 'fire'.
//   // First, a gradient from black to red to yellow to white -- similar to HeatColors_p
//      //gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White);
  
//   // Second, this palette is like the heat colors, but blue/aqua instead of red/yellow
//      gPal = CRGBPalette16(CRGB::Black, CRGB::Blue, CRGB::Aqua);
  
//   // Third, here's a simpler, three-step gradient, from black to red to white
//   //   gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::White);

// }

// int count = 0;

// void loop()
// {
//   // CRGB color = ColorFromPalette( gPal, count % 256, BRIGHTNESS, NOBLEND);
//   // for( int j = 0; j < NUM_LEDS; j++) {
//   //   leds[j] = color;
//   // }
//   // count += (256/16);

//   // Add entropy to random number generator; we use a lot of it.
//   random16_add_entropy( random());

//   // Fourth, the most sophisticated: this one sets up a new palette every
//   // time through the loop, based on a hue that changes every time.
//   // The palette is a gradient from black, to a dark color based on the hue,
//   // to a light color based on the hue, to white.
//   //
//   //   static uint8_t hue = 0;
//   //   hue++;
//   //   CRGB darkcolor  = CHSV(hue,255,192); // pure hue, three-quarters brightness
//   //   CRGB lightcolor = CHSV(hue,128,255); // half 'whitened', full brightness
//   //   gPal = CRGBPalette16( CRGB::Black, darkcolor, lightcolor, CRGB::White);


//   Fire2012WithPalette(); // run simulation frame, using palette colors
  
//   FastLED.show(); // display this frame
//   FastLED.delay(1000 / FRAMES_PER_SECOND);
// }

/// @file    Pride2015.ino
/// @brief   Animated, ever-changing rainbows.
/// @example Pride2015.ino

#include "FastLED.h"

// Pride2015
// Animated, ever-changing rainbows.
// by Mark Kriegsman

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

// // This function draws rainbows with an ever-changing,
// // widely-varying set of parameters.
// void pride() 
// {
//   static uint16_t sPseudotime = 0;
//   static uint16_t sLastMillis = 0;
//   static uint16_t sHue16 = 0;
 
//   uint8_t sat8 = beatsin88( 87, 220, 250);
//   uint8_t brightdepth = beatsin88( 341, 96, 224);
//   uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
//   uint8_t msmultiplier = beatsin88(147, 23, 60);

//   uint16_t hue16 = sHue16;//gHue * 256;
//   uint16_t hueinc16 = beatsin88(113, 1, 3000);
  
//   uint16_t ms = millis();
//   uint16_t deltams = ms - sLastMillis ;
//   sLastMillis  = ms;
//   sPseudotime += deltams * msmultiplier;
//   sHue16 += deltams * beatsin88( 400, 5,9);
//   uint16_t brightnesstheta16 = sPseudotime;
  
//   for( uint16_t i = 0 ; i < NUM_LEDS; i++) {
//     hue16 += hueinc16;
//     uint8_t hue8 = hue16 / 256;

//     brightnesstheta16  += brightnessthetainc16;
//     uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

//     uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
//     uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
//     bri8 += (255 - brightdepth);
    
//     CRGB newcolor = CHSV( hue8, sat8, bri8);
    
//     uint16_t pixelnumber = i;
//     pixelnumber = (NUM_LEDS-1) - pixelnumber;
    
//     nblend( leds[pixelnumber], newcolor, 64);
//   }
// }

#define DATA_PIN    5
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    300
#define BRIGHTNESS  25
#define FRAMES_PER_SECOND 40

CRGB leds[NUM_LEDS];

CRGBPalette256 pallate;


// void wide_pulse_setup(CRGB pulseColor, CRGB backgroundColor, int pulseWidth){
//   for (int i = 0; i < pulseWidth; i++){
//     leds[i] = blend(background, pulseColor, f=)
//   }
// }

#define PLASMA_RESOLUTION 20
#define PLASMA_SPEED 10
#define PLASMA_OFFSET 100

CRGBPalette256 plasma_pallate;
uint8_t noise_buffer[NUM_LEDS];
uint32_t noise_counter = 0;

void plasma(){
  // get next noise frame
  for (int i = 0; i < NUM_LEDS; i++){
    noise_buffer[i] = inoise8(PLASMA_RESOLUTION * (PLASMA_OFFSET + i), noise_counter);
    Serial.printf("%x ", noise_buffer[i]);
  }
  Serial.write("\n");
  noise_counter += PLASMA_SPEED;

  // map noise to pallate
  for (int i = 0; i < NUM_LEDS; i++){
    leds[i] = ColorFromPalette(plasma_pallate, noise_buffer[i]);
  }
}

void setup() {
  //delay(5000); // 3 second delay for recovery

  Serial.write("Setup!\n\r");
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip)
    .setDither(BRIGHTNESS < 255);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 400);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

  pallate = CRGBPalette256(CRGB::Black, CRGB::Blue, CRGB::Aqua, CRGB::Blue);

  // start the first led and black out all others
  //fill_gradient_RGB(leds, NUM_LEDS, CRGB::Blue, CRGB::White, CRGB::Blue);
  // CRGB middle = CRGB::Aqua;
  // CRGB background = CRGB::Blue;
  // uint16_t quarter = NUM_LEDS / 4;
  // uint16_t half = (NUM_LEDS / 2);
  //   uint16_t last = NUM_LEDS - 1;
  //   fill_gradient_RGB( leds,    0, background, quarter, middle);
  //   fill_gradient_RGB( leds, quarter, middle, half, background);
  //   fill_solid(&leds[half], NUM_LEDS / 2, background);

  //fill_solid(leds, NUM_LEDS, CRGB::Blue);

  plasma_pallate = CRGBPalette256(CRGB::Black, CRGB::DarkBlue, CRGB::Aqua);
}

// plasma



void decay(){
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] -= 0x000008;
  }
}

void propagate(){

  CRGB temp = leds[NUM_LEDS - 1];
  for (int i = NUM_LEDS - 1; i > 0; i--){
    leds[i] = leds[i - 1];
  }
  leds[0] = temp;
}

void charged_pulse(){
  propagate();
  leds[0] = CRGB::White;
}

void loop(){
  plasma();
  FastLED.show(); // display this frame
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}


int count = 0;

void loop2()
{
  Serial.write("Loop ");
  Serial.write(count);
  Serial.write("!\n\r");

  if (count < 400){
    propagate();
  } else if (count == 400){
    fill_solid(leds, NUM_LEDS, CRGB::Blue);
  } else if (count < 416){
    decay();
  } else {
    charged_pulse();
  }
  

  FastLED.show(); // display this frame
  if (count <= 100){
    FastLED.delay(1000 / FRAMES_PER_SECOND);
  } else if (count < 400){
    FastLED.delay(1000 / FRAMES_PER_SECOND / 4);
  } else if (count <= 416){
    FastLED.delay(1000 / FRAMES_PER_SECOND); 
  } else {
    FastLED.delay(1000 / FRAMES_PER_SECOND / 8);
  }

  count++;
}