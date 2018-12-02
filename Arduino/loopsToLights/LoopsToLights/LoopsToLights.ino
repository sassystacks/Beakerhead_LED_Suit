/* This is the main function to control the light loops that are driven by the music.

   To Do:
        - Control the timing of the lights using clock
        - Sync timing with brainwave section of the music

   BugFix Tests for Circle lights:
        - Rewrite large circle function
        - remove setup for small circle - made strange things happen on other strands
*/
#include <math.h>
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
#define PIN_LEDARRAY_LARGE_CIRCLE    5// pin to send data to large circle LED
#define PIN_LEDARRAY_SMALL_CIRCLE    4// pin to send data to small circleLED

//Change the brightness of the LEDs here according to how many you have
#define BRIGHTNESS        50

#define LED_TYPE           WS2812B // Type of LED

#define COLOR_ORDER GRB  //order the colors so they match the docs

//Change the number of LEDs here according to how many you have
#define NUM_LEDS          6

//Change the number of LEDs here according to how many you have
#define NUM_LEDS_LARGE_CIRCLE          45

//Change the number of LEDs here according to how many you have
#define NUM_LEDS_SMALL_CIRCLE          25

//Define arrays for the number of led on a strand
CRGB leds[NUM_LEDS];
CRGB leds_lcircle[NUM_LEDS_LARGE_CIRCLE];
CRGB leds_scircle[NUM_LEDS_SMALL_CIRCLE];

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
  FastLED.addLeds<LED_TYPE, 6>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // LED small ciclre configuration
  FastLED.addLeds<LED_TYPE, 5>(leds_lcircle, NUM_LEDS_LARGE_CIRCLE).setCorrection(TypicalLEDStrip);

  // LED large circle configuration
  FastLED.addLeds<LED_TYPE, 4>(leds_scircle, NUM_LEDS_SMALL_CIRCLE).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS / 10);

}

// loopVal is the value that determines if there is a loop to play
// loopVal = 0 - stand by light when music not playing
// loopVal = 1 - low brainwave activity
// loopVal = 2 - medium brainwave activity
// loopVal = 3 - high brainwave activity
// loopVal = 4 - beat the lights in time with music, but no correlation to music
int loopVal = 3;

// loop numbers to run
const int loop1 = 1;
const int loop2 = 2;
const int loop3 = 3;

//convert beats per minute to samples per bar
const int SAMPLES_PER_BAR = (4 * 60) / (72 * .02);

//void runLights(int lightArrayLow[],int lightArrayMid[],int lightArrayHigh[])
uint8_t gHue = 0;

// ~~~~~~~~~~~~~~~~ Colors ~~~~~~~~~~~~~~~~~~~~~~~
// Background color when song is inactive
CHSV backgroundColor = CHSV(190, 150, 150);

// lows
CHSV lowsColor = CHSV(150,255,255);

 //mids
 CHSV midsColor = CHSV(100,210,255);

 //highs
 CHSV highsColor = CHSV(80,200,255);
 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void loop() {

  // Check if there is data on the Receiver
  if (mySwitch.available())
  {
    if (!loopVal)
    {
      delay(1000);//delay if it's the first time receiving data
    }
    int receivedData = mySwitch.getReceivedValue(); // define loopVal as the value on the receiver pin

    // This means the song has started if (4) or brainwave has stopped (6)
    if (receivedData == 4 || receivedData == 6)
    {
      loopVal = 4; // set lights to beat with music
    }

    else if (receivedData != loopVal) // this if brainwave activity has changed
    {
      // start the new loop count to zero since brainwave activity has changed
      loopCount = 0;

      //set the the loop to either low mid or high brainwave value
      loopVal = receivedData;

    }

    mySwitch.resetAvailable(); // reset the receiver pin

  }

  if (loopVal > 0 && loopVal < 4)
  {
    for (int i = 0; i < SAMPLES_PER_BAR; i++)
    {

      // This runs the lights for 6 (lights), 28 (smallcircle) and 45 (large circle) for the element at the
      // point in the array defined by loopCount.
      // Set the lights to the values from the arrays that are built from the music

      if (loopVal == loop1) // low brain activity
      {
        runLights(lightArrayLow[loopCount], lightArrayMid[loopCount] , lightArrayHigh[loopCount] );
        runLights_sCircle(lightArrayLow[loopCount], lightArrayMid[loopCount] , lightArrayHigh[loopCount] );
        runLights_lCircle(lightArrayLow[loopCount], lightArrayMid[loopCount] , lightArrayHigh[loopCount] );
      }
      else if (loopVal == loop2) // medium brain activity
      {
        runLights(mediumArrayLow[loopCount], mediumArrayMid[loopCount] , mediumArrayHigh[loopCount] );
        runLights_sCircle(mediumArrayLow[loopCount], mediumArrayMid[loopCount] , mediumArrayHigh[loopCount] );
        runLights_lCircle(mediumArrayLow[loopCount], mediumArrayMid[loopCount] , mediumArrayHigh[loopCount] );
      }
      else // High brain activity
      {
        runLights(fullArrayLow[loopCount], fullArrayMid[loopCount] , fullArrayHigh[loopCount] );
        runLights_sCircle(fullArrayLow[loopCount], fullArrayMid[loopCount] , fullArrayHigh[loopCount] );
        runLights_lCircle(fullArrayLow[loopCount], fullArrayMid[loopCount] , fullArrayHigh[loopCount] );
      }
      FastLED.show();
      FastLED.delay(200);

      loopCount++; // increment the loop count to keep going through the lights

      //if the loop count excedes the array size
      if (loopCount >= ARRAY_SIZE)
      {
        loopCount = 0;
      }
    }
  }

  else if (loopVal == 4)
  {
    //Beat at the same beats per minute as the song
    bpm();
  }
  else
  {

    fill_solid(leds, NUM_LEDS, backgroundColor);
    fill_solid(leds_scircle, NUM_LEDS_SMALL_CIRCLE, backgroundColor);
    fill_solid(leds_lcircle, NUM_LEDS_LARGE_CIRCLE, backgroundColor);
    FastLED.show();
    FastLED.delay(100);
  }

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~           Functions               ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


void bpm()
{
  FastLED.clear();

  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 72;

  CRGBPalette16 palette = PartyColors_p;

  uint8_t beat = beatsin8( BeatsPerMinute, 100, 255);
  for ( int i = 0; i < NUM_LEDS; i++)
  {

    leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
  }
  for ( int i = 0; i < NUM_LEDS_SMALL_CIRCLE; i++)
  {

    leds_scircle[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
  }
  for ( int i = 0; i < NUM_LEDS_LARGE_CIRCLE; i++)
  {

    leds_lcircle[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
  }
  FastLED.show();
  FastLED.delay(100);
}

void runLights(int ArrayLow, int ArrayMid, int ArrayHigh)
{

  int scaledLow = (int)(round)(ArrayLow / 3);
  int scaledMid = (int)(round)(ArrayMid / 3);
  int scaledHigh = (int)(round)(ArrayHigh / 3);

  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CHSV(192, 100, 70);
  }

  for (int i = 0; i <  scaledLow ; i++) // lows
  {
    leds[i] = midsColor; 

  }
  for (int i = scaledLow ; i < scaledLow + scaledMid; i++)
  {
    leds[i] = midsColor; //

  }
  for (int i = scaledLow + scaledMid; i < scaledLow + scaledMid + scaledHigh; i++)
  {
    leds[i] = highsColor; // make these blue
  }

}

void runLights_sCircle(int ArrayLow, int ArrayMid, int ArrayHigh)
{

  float scaleFactor = 1.3;
  int scaledLow = (int)(ceil)(ArrayLow * scaleFactor);
  int scaledMid = (int)(ceil)(ArrayMid * scaleFactor);
  int scaledHigh = (int)(ceil)(ArrayHigh * scaleFactor);

  for (int i = 0; i < NUM_LEDS_SMALL_CIRCLE; i++)
  {
    leds_scircle[i] =  CHSV(192, 100, 70);
  }

  for (int i = 0; i < scaledLow; i++)
  {
    leds_scircle[i] = lowsColor; // lows
  }

  for (int i = scaledLow; i < scaledMid + scaledLow; i++)
  {
    leds_scircle[i] = midsColor; // mids
  }

  for (int i = scaledMid + scaledLow ; i < scaledHigh + scaledMid + scaledLow; i++)
  {
    leds_scircle[i] = highsColor; // highs
  }
}

void runLights_lCircle(int ArrayLow, int ArrayMid, int ArrayHigh)
{

  float scaleFactor = 2.5;
  int scaledLow = (int)(ceil)(ArrayLow * scaleFactor);
  int scaledMid = (int)(ceil)(ArrayMid * scaleFactor);
  int scaledHigh = (int)(ceil)(ArrayHigh * scaleFactor);

  for (int i = 0; i < NUM_LEDS_LARGE_CIRCLE; i++)
  {
    leds_lcircle[i] =  CHSV(192, 100, 70);
  }

  for (int i = 0; i < scaledLow; i++)
  {
    leds_lcircle[i] = lowsColor; // lows
  }

  for (int i = scaledLow; i < scaledMid + scaledLow; i++)
  {
    leds_lcircle[i] = midsColor; //mids
  }

  for (int i = scaledMid + scaledLow; i < scaledHigh + scaledMid + scaledLow ; i++)
  {
    leds_lcircle[i] = highsColor; //highs
  }
}
