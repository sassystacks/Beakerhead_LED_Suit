//~~~~~~~~~~~~~~~~~~~~~ Filter Data stuff ~~~~~~~~~~~~~~~~~~~~~~~



//~~~~~~~~~~~~~~~~~~~~~~ RF stuff ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
const int RF_PIN = 2;

//~~~~~~~~~~~~~~~~~~~~~~ LED stuff ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <FastLED.h>



#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define PIN_LEDARRAY    6// pin to send data to LED
#define PIN_LEDARRAY_LARGE_CIRCLE    5// pin to send data to small circle LED
#define PIN_LEDARRAY_SMALL_CIRCLE    4// pin to send data to large circleLED

//Change the brightness of the LEDs here according to how many you have
#define BRIGHTNESS        50

#define LED_TYPE           WS2812B // Type of LED
#define COLOR_ORDER        GRB //Order of colours

//Change the number of LEDs here according to how many you have
#define NUM_LEDS          18

//Change the number of LEDs here according to how many you have
#define NUM_LEDS_LARGE_CIRCLE          45

//Change the number of LEDs here according to how many you have
#define NUM_LEDS_SMALL_CIRCLE          25

CRGB leds[NUM_LEDS];
//CRGB leds_lcircle[NUM_LEDS_LARGE_CIRCLE];
//CRGB leds_scircle[NUM_LEDS_SMALL_CIRCLE];

// Create the arrays that describe the lights
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Low Waves ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Low Frequencies- Calm Brain Waves
int lightArrayLow [] = {0,
                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 5, 4, 4, 3, 1, 0, 4, 7, 6, 6, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        5, 5, 9, 5, 1, 1, 1, 3, 6, 5, 4, 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 5, 5, 3, 2, 1, 1, 5, 4, 5, 4, 3,
                        2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 5, 8, 5, 2, 1, 1, 1, 1, 5, 5, 2, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 3, 6, 5, 3, 3, 2, 0, 2, 8, 6, 5, 5, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 5, 6, 4, 3, 1, 1, 5, 7,
                        5, 4, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 4, 5, 3, 1, 1, 1, 3, 6, 4, 3, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 1, 3, 6, 6, 3, 2, 1, 1, 2, 5, 6, 5, 3, 2, 1, 0
                       };

//Mid Frequencies- Calm Brain Waves
int lightArrayMid[] = {2,
                       2, 1, 2, 2, 1, 1, 2, 3, 2, 2, 1, 1, 3, 3, 3, 2, 1, 1, 1, 4, 4, 2, 1, 1, 1, 1, 4, 3, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1,
                       1, 4, 3, 1, 1, 1, 1, 2, 3, 2, 2, 2, 2, 1, 1, 2, 2, 1, 0, 0, 0, 0, 3, 2, 2, 1, 0, 0, 2, 3, 1, 1, 1, 0, 0, 3, 2, 1, 1, 1,
                       0, 0, 6, 3, 2, 1, 1, 2, 2, 1, 3, 3, 2, 1, 1, 1, 2, 3, 1, 1, 1, 1, 1, 2, 2, 3, 2, 1, 1, 1, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 3, 2, 2, 2, 1, 0, 0, 4, 3, 2, 2, 1, 0, 0, 0, 2, 2, 1, 2, 2, 2, 1, 3, 3, 3, 2, 1, 1, 4, 3, 2, 1, 1, 1, 1, 3, 2,
                       2, 1, 1, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 1, 0, 0, 4, 3, 2, 1, 0, 0, 0, 2, 2, 2, 1, 1, 0, 0, 2, 3, 3, 2, 2, 2, 1,
                       2, 3, 2, 2, 1, 1, 1, 3, 2, 2, 1, 1, 1, 0, 3, 3, 2, 2, 1, 1, 1, 1
                      };

//High Frequencies - Calm Brain Waves
int lightArrayHigh[] = {2,
                        2, 1, 2, 2, 1, 1, 2, 3, 2, 2, 1, 1, 3, 3, 3, 2, 1, 1, 1, 4, 4, 2, 1, 1, 1, 1, 4, 3, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1,
                        1, 4, 3, 1, 1, 1, 1, 2, 3, 2, 2, 2, 2, 1, 1, 2, 2, 1, 0, 0, 0, 0, 3, 2, 2, 1, 0, 0, 2, 3, 1, 1, 1, 0, 0, 3, 2, 1, 1, 1,
                        0, 0, 6, 3, 2, 1, 1, 2, 2, 1, 3, 3, 2, 1, 1, 1, 2, 3, 1, 1, 1, 1, 1, 2, 2, 3, 2, 1, 1, 1, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 3, 2, 2, 2, 1, 0, 0, 4, 3, 2, 2, 1, 0, 0, 0, 2, 2, 1, 2, 2, 2, 1, 3, 3, 3, 2, 1, 1, 4, 3, 2, 1, 1, 1, 1, 3, 2,
                        2, 1, 1, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 1, 0, 0, 4, 3, 2, 1, 0, 0, 0, 2, 2, 2, 1, 1, 0, 0, 2, 3, 3, 2, 2, 2, 1,
                        2, 3, 2, 2, 1, 1, 1, 3, 2, 2, 1, 1, 1, 0, 3, 3, 2, 2, 1, 1, 1, 1
                       };

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Medium Waves ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Low Frequencies- Mid Brain Waves
int mediumArrayLow [] = {6,
                         5, 6, 6, 6, 8, 7, 7, 7, 9, 5, 5, 4, 6, 6, 7, 6, 5, 4, 5, 5, 4, 3, 6, 5, 5, 4, 3, 5, 7, 7, 5, 6, 5, 7, 5, 4, 7, 5, 4, 5,
                         6, 6, 8, 4, 5, 5, 4, 4, 7, 6, 6, 4, 4, 6, 6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 5, 4, 3, 2, 1, 1, 4, 4, 4, 4, 2,
                         2, 1, 5, 5, 5, 5, 5, 5, 5, 4, 6, 4, 6, 4, 4, 5, 4, 6, 5, 4, 5, 3, 2, 4, 6, 6, 4, 5, 5, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 3, 5, 4, 3, 3, 2, 0, 2, 7, 5, 5, 4, 1, 1, 0, 4, 8, 4, 5, 3, 6, 4, 5, 4, 5, 6, 4, 4, 4, 5, 5, 6, 5, 3, 4, 7, 7,
                         5, 6, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 4, 5, 3, 1, 0, 1, 3, 6, 4, 3, 2, 1, 1, 3, 3, 3, 6, 4, 4, 7,
                         3, 6, 5, 4, 4, 3, 6, 4, 4, 6, 2, 5, 4, 1, 4, 4, 2, 7, 3, 4, 2, 5
                        };

//Mid Frequencies- Mid Brain Waves
int mediumArrayMid[] = {1,
                        1, 1, 2, 2, 1, 2, 2, 2, 2, 2, 1, 1, 2, 3, 3, 2, 1, 1, 1, 4, 3, 3, 2, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 1,
                        2, 3, 2, 1, 1, 1, 1, 2, 3, 2, 2, 1, 2, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 1, 0, 0, 0, 3, 2, 1, 1, 1,
                        1, 0, 6, 4, 2, 2, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 3, 3, 1, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 3, 3, 2, 2, 1, 1, 0, 4, 3, 2, 2, 1, 0, 0, 0, 2, 2, 1, 2, 2, 2, 1, 3, 2, 1, 1, 1, 2, 3, 4, 2, 2, 1, 1, 1, 3, 2,
                        2, 1, 1, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 2, 1, 0, 0, 0, 2, 2, 2, 1, 1, 0, 0, 2, 2, 2, 2, 3, 2, 1,
                        2, 2, 1, 1, 1, 1, 1, 2, 3, 2, 1, 2, 1, 0, 3, 3, 2, 2, 1, 1, 1, 2
                       };

//High Frequencies - Mid Brain Waves
int mediumArrayHigh[] = {0,
                         0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 3, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0,
                         1, 1, 0, 0, 0, 0, 0, 2, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0,
                         0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 2, 1,
                         1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0
                        };

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Full  Waves  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Low Frequencies- Mid Brain Waves
int fullArrayLow [] = {5,
                       4, 5, 4, 4, 6, 5, 5, 5, 6, 4, 4, 3, 5, 4, 7, 5, 4, 3, 4, 4, 2, 6, 4, 3, 4, 3, 2, 9, 6, 5, 4, 5, 4, 5, 4, 3, 5, 4, 3, 4,
                       6, 4, 8, 3, 3, 3, 3, 3, 5, 5, 4, 3, 3, 4, 5, 2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 1, 0, 0, 2, 3, 4, 2, 1, 1, 0, 3, 3, 3, 3, 2,
                       1, 0, 3, 2, 5, 4, 3, 4, 4, 3, 3, 3, 3, 3, 3, 4, 3, 4, 4, 3, 4, 2, 1, 3, 4, 6, 4, 4, 4, 3, 4, 4, 2, 1, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 2, 4, 3, 3, 2, 1, 0, 1, 5, 4, 3, 3, 1, 1, 0, 3, 6, 3, 4, 2, 4, 3, 3, 4, 5, 4, 3, 3, 3, 5, 3, 4, 4, 3, 3, 5, 5,
                       3, 4, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 2, 0, 0, 4, 2, 7, 3, 1, 0, 0, 2, 4, 3, 2, 1, 1, 1, 2, 3, 3, 5, 3, 3, 5,
                       2, 4, 5, 2, 3, 2, 4, 3, 5, 5, 1, 3, 3, 1, 1, 3, 3, 5, 2, 3, 2, 4
                      };

//Mid Frequencies- Mid Brain Waves
int fullArrayMid[] = {2,
                      2, 1, 2, 2, 1, 1, 2, 3, 2, 2, 1, 1, 3, 3, 3, 2, 1, 1, 1, 4, 4, 2, 1, 1, 1, 1, 4, 3, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1,
                      1, 4, 3, 1, 1, 1, 1, 2, 3, 2, 2, 2, 2, 1, 1, 2, 2, 1, 0, 0, 0, 0, 3, 2, 2, 1, 0, 0, 2, 3, 1, 1, 1, 0, 0, 3, 2, 1, 1, 1,
                      0, 0, 6, 3, 2, 1, 1, 2, 2, 1, 3, 3, 2, 1, 1, 1, 2, 3, 1, 1, 1, 1, 1, 2, 2, 3, 2, 1, 1, 1, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 3, 2, 2, 2, 1, 0, 0, 4, 3, 2, 2, 1, 0, 0, 0, 2, 2, 1, 2, 2, 2, 1, 3, 3, 3, 2, 1, 1, 4, 3, 2, 1, 1, 1, 1, 3, 2,
                      2, 1, 1, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 1, 0, 0, 4, 3, 2, 1, 0, 0, 0, 2, 2, 2, 1, 1, 0, 0, 2, 3, 3, 2, 2, 2, 1,
                      2, 3, 2, 2, 1, 1, 1, 3, 2, 2, 1, 1, 1, 0, 3, 3, 2, 2, 1, 1, 1, 1
                     };

//High Frequencies - Mid Brain Waves
int fullArrayHigh[] = {1,
                       1, 0, 0, 0, 0, 0, 1, 2, 2, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       1, 2, 1, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 1, 3, 1, 0, 0, 0, 0, 0, 2, 2, 1, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 2, 2, 1, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1, 0, 0, 0, 0,
                       0, 2, 1, 0, 0, 0, 0, 2, 2, 1, 0, 0, 0, 0, 2, 2, 1, 1, 0, 0, 0, 0
                      };
/*
  int fullArray[222] [3]= {[2 1 5],
  [2 1 4],[1 0 5],[2 0 4],[2 0 4],[1 0 6],[1 0 5],[2 1 5],[3 2 5],[2 2 6],[2 0 4],[1 0 4],[1 0 3],[3 1 5],[3 2 4],[3 1 7],[2 0 5],[1 0 4],[1 0 3],[1 0 4],[4 0 4],[4 1 2],[2 2 6],[1 1 4],[1 0 3],[1 0 4],[1 0 3],[4 1 2],[3 2 9],[2 1 6],[2 0 5],[2 0 4],[2 0 5],[2 0 4],[2 0 5],[1 0 4],[1 0 3],[1 0 5],[1 0 4],[1 0 3],[1 0 4],
  [1 1 6],[4 2 4],[3 1 8],[1 0 3],[1 0 3],[1 0 3],[1 0 3],[2 0 3],[3 1 5],[2 2 5],[2 1 4],[2 0 3],[2 0 3],[1 0 4],[1 1 5],[2 3 2],[2 1 2],[1 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[3 2 2],[2 2 2],[2 1 2],[1 0 1],[0 0 0],[0 0 0],[2 1 2],[3 2 3],[1 1 4],[1 0 2],[1 0 1],[0 0 1],[0 0 0],[3 0 3],[2 0 3],[1 0 3],[1 0 3],[1 0 2],
  [0 0 1],[0 0 0],[6 1 3],[3 2 2],[2 1 5],[1 0 4],[1 0 3],[2 0 4],[2 0 4],[1 0 3],[3 2 3],[3 2 3],[2 1 3],[1 0 3],[1 0 3],[1 0 4],[2 2 3],[3 2 4],[1 0 4],[1 0 3],[1 0 4],[1 0 2],[1 0 1],[2 0 3],[2 2 4],[3 2 6],[2 0 4],[1 0 4],[1 0 4],[1 0 3],[2 1 4],[2 1 4],[1 0 2],[0 0 1],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],
  [0 0 0],[0 0 0],[0 0 0],[3 0 2],[2 2 4],[2 2 3],[2 0 3],[1 0 2],[0 0 1],[0 0 0],[4 0 1],[3 0 5],[2 0 4],[2 0 3],[1 0 3],[0 0 1],[0 0 1],[0 0 0],[2 0 3],[2 0 6],[1 0 3],[2 0 4],[2 0 2],[2 0 4],[1 0 3],[3 1 3],[3 2 4],[3 2 5],[2 0 4],[1 0 3],[1 0 3],[4 1 3],[3 2 5],[2 1 3],[1 0 4],[1 0 4],[1 0 3],[1 0 3],[3 0 5],[2 0 5],
  [2 0 3],[1 0 4],[1 0 3],[2 0 3],[2 0 3],[1 0 3],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[2 1 2],[2 2 1],[2 1 1],[1 0 2],[0 0 0],[0 0 0],[4 1 4],[3 2 2],[2 1 7],[1 0 3],[0 0 1],[0 0 0],[0 0 0],[2 0 2],[2 0 4],[2 0 3],[1 0 2],[1 0 1],[0 0 1],[0 0 1],[2 2 2],[3 2 3],[3 1 3],[2 0 5],[2 0 3],[2 0 3],[1 0 5],
  [2 0 2],[3 2 4],[2 1 5],[2 0 2],[1 0 3],[1 0 2],[1 0 4],[3 2 3],[2 2 5],[2 1 5],[1 0 1],[1 0 3],[1 0 3],[0 0 1],[3 2 1],[3 2 3],[2 1 3],[2 1 5],[1 0 2],[1 0 3],[1 0 2],[1 0 4]};

  int mediumArray[222] [3]= {[6 0 1],
  [5 0 1],[6 0 1],[6 0 2],[6 0 2],[8 0 1],[7 0 2],[7 1 2],[7 1 2],[9 1 2],[5 0 2],[5 0 1],[4 0 1],[6 1 2],[6 2 3],[7 1 3],[6 0 2],[5 0 1],[4 0 1],[5 0 1],[5 3 4],[4 2 3],[3 0 3],[6 0 2],[5 0 1],[5 0 1],[4 0 1],[3 0 1],[5 0 2],[7 1 2],[7 0 2],[5 1 2],[6 0 2],[5 0 2],[7 0 2],[5 1 2],[4 1 2],[7 1 1],[5 0 1],[4 0 2],[5 0 1],
  [6 1 2],[6 1 3],[8 0 2],[4 0 1],[5 0 1],[5 0 1],[4 0 1],[4 2 2],[7 1 3],[6 0 2],[6 0 2],[4 1 1],[4 0 2],[6 0 2],[6 0 2],[3 0 1],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[3 1 2],[5 0 2],[4 0 2],[3 0 1],[2 0 0],[1 0 0],[1 0 0],[4 2 3],[4 1 2],[4 0 1],[4 0 1],[2 0 1],
  [2 0 1],[1 0 0],[5 1 6],[5 2 4],[5 0 2],[5 0 2],[5 0 1],[5 0 2],[5 0 3],[4 0 1],[6 0 1],[4 0 1],[6 0 1],[4 0 1],[4 0 1],[5 0 1],[4 2 2],[6 2 2],[5 0 1],[4 0 1],[5 0 1],[3 0 1],[2 0 1],[4 2 2],[6 2 3],[6 0 3],[4 0 1],[5 0 1],[5 0 1],[4 0 2],[5 0 1],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],
  [0 0 0],[0 0 0],[0 0 0],[3 1 3],[5 2 3],[4 1 2],[3 0 2],[3 0 1],[2 0 1],[0 0 0],[2 2 4],[7 1 3],[5 0 2],[5 0 2],[4 0 1],[1 0 0],[1 0 0],[0 0 0],[4 0 2],[8 0 2],[4 0 1],[5 0 2],[3 0 2],[6 1 2],[4 0 1],[5 0 3],[4 0 2],[5 0 1],[6 0 1],[4 0 1],[4 0 2],[4 2 3],[5 1 4],[5 0 2],[6 0 2],[5 0 1],[3 0 1],[4 0 1],[7 2 3],[7 1 2],
  [5 1 2],[6 0 1],[4 0 1],[4 1 2],[4 1 2],[4 0 1],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[5 2 3],[4 1 3],[5 0 2],[3 0 1],[1 0 0],[0 0 0],[1 0 0],[3 2 2],[6 1 2],[4 0 2],[3 0 1],[2 0 1],[1 0 0],[1 0 0],[3 1 2],[3 1 2],[3 0 2],[6 0 2],[4 1 3],[4 0 2],[7 0 1],
  [3 0 2],[6 0 2],[5 0 1],[4 0 1],[4 0 1],[3 0 1],[6 0 1],[4 1 2],[4 1 3],[6 1 2],[2 0 1],[5 0 2],[4 0 1],[1 0 0],[4 2 3],[4 1 3],[2 0 2],[7 0 2],[3 0 1],[4 0 1],[2 0 1],[5 0 2]
  };

  int lightArray[222] [3]= {[0 0 0],
  [0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[3 1 2],[4 1 5],[4 1 4],[2 0 4],[1 0 3],[0 0 1],[0 0 0],[5 3 4],[4 2 7],[4 0 6],[2 0 6],[1 0 2],[1 0 2],[0 0 1],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],
  [3 1 5],[4 1 5],[3 0 9],[2 0 5],[1 0 1],[0 0 1],[0 0 1],[3 2 3],[4 0 6],[3 0 5],[2 0 4],[1 0 2],[1 0 2],[1 0 1],[0 0 1],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 1],[3 1 4],[3 0 5],[2 0 5],[2 0 3],[1 0 2],[1 0 1],[0 0 1],[4 2 5],[3 1 4],[2 0 5],[2 0 4],[1 0 3],
  [1 0 2],[0 0 1],[0 0 1],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[2 0 2],[2 2 5],[4 1 8],[2 0 5],[1 0 2],[1 0 1],[0 0 1],[0 0 1],[4 2 1],[4 1 5],[3 0 5],[1 0 2],[1 0 3],[0 0 1],[0 0 1],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],
  [0 0 0],[0 0 0],[0 0 0],[4 1 3],[3 2 6],[3 1 5],[2 0 3],[2 0 3],[1 0 2],[0 0 0],[6 2 2],[4 1 8],[3 0 6],[2 0 5],[2 0 5],[0 0 2],[0 0 1],[0 0 1],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[4 2 2],[4 1 5],[3 0 6],[2 0 4],[1 0 3],[1 0 1],[0 0 1],[4 2 5],[3 1 7],
  [2 1 5],[2 0 4],[1 0 1],[0 0 1],[0 0 1],[0 0 1],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[5 2 6],[3 1 4],[3 0 5],[2 0 3],[1 0 1],[0 0 1],[0 0 1],[3 2 3],[3 1 6],[3 0 4],[1 0 3],[1 0 2],[1 0 2],[1 0 1],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],
  [0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[0 0 0],[1 0 1],[3 1 3],[4 0 6],[3 0 6],[1 0 3],[1 0 2],[1 0 1],[0 0 1],[2 1 2],[3 0 5],[2 0 6],[2 0 5],[1 0 3],[1 0 2],[0 0 1],[0 0 0]
  };*/

//Get the length of the light loop array
unsigned int ARRAY_SIZE = sizeof(lightArrayLow) / sizeof(int);

// count the mainLoop
unsigned int loopCount = 0;

void setup() {

  // RF transmission stuff
  Serial.begin(9600);

  Serial.print(" Array Size is: ");
  Serial.println(ARRAY_SIZE);
  mySwitch.enableReceive(RF_PIN);  // Receiver on interrupt 0 => that is pin #2

  delay(2000); // 3 second delay for recovery

  // LED strip configuration
  FastLED.addLeds<LED_TYPE, PIN_LEDARRAY, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
//
//
//   // LED small ciclre configuration
//    FastLED.addLeds<LED_TYPE,PIN_LEDARRAY_LARGE_CIRCLE,COLOR_ORDER>(leds_lcircle, NUM_LEDS_LARGE_CIRCLE).setCorrection(TypicalLEDStrip);
//  
//     // LED large circle configuration
//    FastLED.addLeds<LED_TYPE,PIN_LEDARRAY_SMALL_CIRCLE,COLOR_ORDER>(leds_scircle, NUM_LEDS_SMALL_CIRCLE).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS / 10);

}

int loopVal = 0; // this is the value that determines if there is a loop to play
int chkVal = 0; // check if value changed on transmitter
int t_loopVal = 0; // this value is checked against loopVal to see if the brain waves have changed state

// loop numbers to run
const int loop1 = 1;
const int loop2 = 2;
const int loop3 = 3;

//convert beats per minute to samples per bar
const int SAMPLES_PER_BAR = (4 * 60) / (72 * .02);

//void runLights(int lightArrayLow[],int lightArrayMid[],int lightArrayHigh[])

uint8_t gHue = 0;

void loop() {



  // Check if there is data on the Receiver
  if (mySwitch.available())
  {
    if (!loopVal)
    {
      delay(1000);//delay if it's the first time receiving data
    }
    int receivedData = mySwitch.getReceivedValue(); // define loopVal as the value on the receiver pin

    if (receivedData == 4)
    {
      unsigned long init_time = millis(); //Get the time right now
      unsigned long currentime = millis();
      while (currentime - init_time < 90000)
      {        
         currentime = millis();
         bpm();
         FastLED.show();
         FastLED.delay(100);
      } 
    }

    if ((receivedData == loop1 || receivedData == loop2 || receivedData == loop3))
    {

      loopVal = receivedData;

      for (int i = 0; i < 4; i++)
      {
        runLoops();
        if (mySwitch.available() && i == 1)
        {
          t_loopVal = mySwitch.getReceivedValue();
          chkVal = 1;
        }

      }
      if (chkVal)
      {
        loopVal = t_loopVal;
        chkVal = 0;
      }




    }
    //
    //    Serial.print("brain state is: ");
    //    Serial.println(loopVal);
    mySwitch.resetAvailable(); // reset the receiver pin

  }


  else if (loopVal) {

    runLoops(); // run loops
  }

  else
  {
    // Default state for the lights
    //fill_solid( leds, NUM_LEDS, CRGB(50, 0, 200));
    runLights(9, 5, 4);
    //Serial.println(0);
  }


}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~           Functions               ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void runLoops()
{
  //Run for loop for the next samples per bar
  for (int i = 0; i < SAMPLES_PER_BAR / 4; i++)
  {
    // First, clear the existing led values

    loopCount++;//add to the loop count

    //if the loop count excedes the array size
    if (loopCount >= ARRAY_SIZE) 
    {
      loopCount = 0;
    }
    
    if (loopVal == loop1)
    { // Run low Brain Activity loops
      runLights(lightArrayLow[loopCount], lightArrayMid[loopCount], lightArrayHigh[loopCount]);
//                runLights_sCircle(lightArrayLow[loopCount]*1.3, lightArrayMid[loopCount]*1.3, lightArrayHigh[loopCount]*1.3);
//                runLights_lCircle(lightArrayLow[loopCount]*2, lightArrayMid[loopCount]*2, lightArrayHigh[loopCount]*2);


    }

    else if (loopVal == loop2)
    { // Run Mid Brain Activity loops
      runLights(mediumArrayLow[loopCount], mediumArrayLow[loopCount], mediumArrayLow[loopCount]);
//                runLights_sCircle(mediumArrayLow[loopCount]*1.3, mediumArrayLow[loopCount]*1.3, mediumArrayLow[loopCount]*1.3);
//                runLights_lCircle(mediumArrayLow[loopCount]*2, mediumArrayLow[loopCount]*2, mediumArrayLow[loopCount]*2);


    }

    else if (loopVal == loop3)
    { // Run High Brain Activity loops
      runLights(fullArrayLow[loopCount], fullArrayLow[loopCount], fullArrayLow[loopCount]);
//                runLights_sCircle(fullArrayLow[loopCount]*1.3, fullArrayLow[loopCount]*1.3, fullArrayLow[loopCount]*1.3);
//                runLights_lCircle(fullArrayLow[loopCount]*2, fullArrayLow[loopCount]*2, fullArrayLow[loopCount]*2);
    }

  }

}
void bpm()
{

  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 72;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 100, 255);
  for ( int i = 0; i < NUM_LEDS; i++) 
  { 
    //9948
  
    leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
  }
}
  void runLights(int ArrayLow, int ArrayMid, int ArrayHigh)
  {
    FastLED.clear();
    for (int i = 0; i < ArrayLow + 1; i++)
    {
      leds[i] = CRGB::Red;
      leds[i] += CHSV(0, -10*ArrayLow, 20*ArrayLow);

    }
    for (int i = ArrayLow; i < ArrayMid + ArrayLow + 1; i++)
    {
      leds[i] = CRGB::Green;
      leds[i] += CHSV(0,-10*ArrayLow, 20*ArrayMid);

    }
    for (int i = ArrayMid + ArrayLow; i < ArrayHigh + ArrayMid + ArrayLow + 1; i++)
    {
      leds[i] = CRGB::Blue;
      leds[i] += CHSV(0,-10*ArrayLow, 20*ArrayHigh);

    }
    FastLED.show(); // show the current state of LED
    FastLED.delay(20); // delay 20 ms

  }

//  void runLights_sCircle(int ArrayLow, int ArrayMid,int ArrayHigh)
//  {
//    for (int i =0; i < ArrayLow + 1; i++)
//      {
//         leds_scircle[i] = CRGB::Red;
//  
//      }
//     for(int i = ArrayLow; i < ArrayMid + ArrayLow+1; i++)
//     {
//        leds_scircle[i] = CRGB::Green;
//  
//     }
//      for(int i = ArrayMid + ArrayLow; i < ArrayHigh + ArrayMid + ArrayLow + 1; i++)
//     {
//        leds_scircle[i] = CRGB::Blue;
//  
//     }
//  
//  
//  }
//  
//  void runLights_lCircle(int ArrayLow, int ArrayMid,int ArrayHigh)
//  {
//    for (int i =0; i < ArrayLow + 1; i++)
//      {
//         leds_lcircle[i] = CRGB::Red;
//  
//      }
//     for(int i = ArrayLow; i < ArrayMid + ArrayLow+1; i++)
//     {
//        leds_lcircle[i] = CRGB::Green;
//  
//     }
//      for(int i = ArrayMid + ArrayLow; i < ArrayHigh + ArrayMid + ArrayLow + 1; i++)
//     {
//        leds_lcircle[i] = CRGB::Blue;
//  
//     }
//  
//  
//  }
