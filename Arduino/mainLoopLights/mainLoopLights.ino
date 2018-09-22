//~~~~~~~~~~~~~~~~~~~~~ SD Card Data stuff ~~~~~~~~~~~~~~~~~~~~~~~
#include <limits.h>
#include <SPI.h>

// next two lines for SdFat
#include <SdFat.h>
SdFat SD;
#define CS_PIN SS //define comunication on CS pin
#define CSV_DELIM ',' //CSV is comma delimiter

File file1; // instantiate an instance of file
File file2; // instantiate an instance of file
File file3; // instantiate an instance of file

const char* fname1 = "MAINTR~1.TXT"; //High frequency file
const char* fname2 = "MAINTR~2.TXT"; //low frequency file
const char* fname3 = "MAINTR~3.TXT"; //Mid frequencyfile

//~~~~~~~~~~~~~~~~~~~~~~ LED stuff ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <FastLED.h>



#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define PIN_LEDARRAY    6 // pin to send data to LED

//Change the brightness of the LEDs here according to how many you have
#define BRIGHTNESS        50

#define LED_TYPE           WS2812B // Type of LED
#define COLOR_ORDER        GRB //Order of colours

//Change the number of LEDs here according to how many you have
#define NUM_LEDS          18


CRGB leds[NUM_LEDS];
//~~~~~~~~~~~~~~~~~~~~~~ RF stuff ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
const int RF_PIN = 2;


void setup() {

  Serial.begin(9600); // begin serial communication
  // Wait for USB Serial
  //     while (!Serial)
  //     {
  //        yield();
  //      }
  // Initialize the SD.
  if (!SD.begin(CS_PIN))
  {
    Serial.println("begin failed");
    return;
  }

  mySwitch.enableReceive(RF_PIN);  // Receiver on interrupt 0 => that is pin #2
  delay(2000); // 2 second delay for recovery

  // LED strip configuration
  FastLED.addLeds<LED_TYPE, PIN_LEDARRAY, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS/10);

}

uint16_t lightIntensityLow; //initialize light intensity
uint16_t lightIntensityMid; //initialize light intensity
uint16_t lightIntensityHigh; //initialize light intensity

int loopVal = 0; // this is the value that determines if there is a loop to play

int t_loopVal = 0; // this value is checked against loopVal to see if the brain waves have changed state

const int music_play = 4;
int receive_messages = 1;
int play_music = 0;

void loop() {

  //Check if there is a signal on the wire
  if (mySwitch.available() && receive_messages)
  {
   // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
  
    int receivedData = mySwitch.getReceivedValue(); // define loopVal as the value on the receiver pin

    if (receivedData == music_play) {
      play_music = 1;

      //Serial.print("Play music received");
      //Serial.println(loopVal);
      mySwitch.resetAvailable(); // reset the receiver pin

      receive_messages = 0;
    }
  }

  if (play_music)
  {
    //Serial.println("Start Music");
    //open the file for the main track
    int ckf1 = openFile(file1, fname1);
    int ckf2 = openFile(file2, fname2);
    int ckf3 = openFile(file3, fname3);
    if (ckf1 && ckf2 && ckf3)
    {

      // read sd Card for a given number of
      int loopCount = 0;
      //Serial.println("Running LIghts");
      while (file1.available() && file2.available() && file3.available())
      {
        
        //Serial.println("Fuck shit fucker motherfucker");
        int chk1 = csvReadUint16(&file2, &lightIntensityLow, CSV_DELIM) ;
        int chk2 = csvReadUint16(&file3, &lightIntensityMid, CSV_DELIM) ;
        int chk3 = csvReadUint16(&file1, &lightIntensityHigh, CSV_DELIM) ;

        if (chk1 ==  CSV_DELIM && chk2 ==  CSV_DELIM && chk3 ==  CSV_DELIM )
        {

          
          //Set lights to intensities
          runLights(lightIntensityLow* 2, lightIntensityMid*2, lightIntensityHigh*2);

            

          //
//                    Serial.print("low intensity is: ");
//                    Serial.print(lightIntensityLow);
//                    Serial.print("        ");
//                    Serial.print("Mid intensity is: ");
//                    Serial.print(lightIntensityMid);
//                    Serial.print("        ");
//                    Serial.print("High intensity is: ");
//                    Serial.println(lightIntensityHigh);
//                    Serial.flush();
 
        }
        loopCount ++;
        if (loopCount > 11050)
        {
          break;
        }
      }
      //Serial.println("Ending track ...... ");
      play_music = 0; // End track

      //Serial.println("Closing files ........");
      file1.close();
      file2.close();
      file3.close();
    }

  }
  else
  {
    // Default state for the lights
    runLights(9, 5, 4);
    //Serial.println("No data received yet");


  }

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~           Functions               ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int openFile(File &file, const char *fname)
{
  file = SD.open(fname, FILE_READ);
  if (!file)
  {
    //Serial.println("open failed");
    Serial.println(fname);
    return 0;
  }
  //Serial.println("opened file successfully");
  return 1;
}
// Function takes an open file and returns an integer that describes the ascii code of the
// delimiter character, access the string returned from the text file through the str variable
// passed by reference
int csvReadText(File* file, char* str, size_t size, char delim)
{
  char ch;
  int rtn;
  size_t n = 0;
  while (true) {
    // check for EOF
    if (!file->available()) {
      rtn = 0;
      break;
    }
    if (file->read(&ch, 1) != 1) {
      // read error
      rtn = -1;
      break;
    }
    // Delete CR.
    if (ch == '\r') {
      continue;
    }
    if (ch == delim || ch == '\n') {
      rtn = ch;
      break;
    }
    if ((n + 1) >= size) {
      // string too long
      rtn = -2;
      n--;
      break;
    }
    str[n++] = ch;
  }
  str[n] = '\0';

  return rtn;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Convert the value read from the CSV to an unsigned 32 bit integer
int csvReadUint32(File* file, uint32_t* num, char delim)
{
  char buf[20];
  char* ptr;
  int rtn = csvReadText(file, buf, sizeof(buf), delim);
  if (rtn < 0) return rtn;
  *num = strtoul(buf, &ptr, 10);
  if (buf == ptr) return -3;
  while (isspace(*ptr)) ptr++;
  return *ptr == 0 ? rtn : -4;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Convert the value read from the CSV to an unsigned 16 bit integer
int csvReadUint16(File* file, uint16_t* num, char delim)
{
  uint32_t tmp;
  int rtn = csvReadUint32(file, &tmp, delim);
  if (rtn < 0) return rtn;
  if (tmp > UINT_MAX) return -5;
  *num = tmp;
  return rtn;
}

// Run the LED lights based on the intensity of the signal
void runLights(uint16_t ArrayLow, uint16_t ArrayMid, uint16_t ArrayHigh)
{
  // First, clear the existing led values
  FastLED.clear();
  for (int i = 0; i < ArrayLow ; i++)
  {
    leds[i] = CRGB::Red;
  }
  for (int i = ArrayLow ; i < ArrayMid + ArrayLow; i++)
  {
    leds[i] = CRGB::Green;
  }
  for (int i = ArrayMid + ArrayLow; i < ArrayHigh + ArrayMid + ArrayLow; i++)
  {
    leds[i] = CRGB::Blue;
  }
  //Show light values
  FastLED.show();

  //delay for 20ms to show the lights
  delay(11);

}

