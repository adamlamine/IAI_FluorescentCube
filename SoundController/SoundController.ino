#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

#define CLK 18       // SPI Clock, shared with SD card
#define MISO 19      // Input data, from VS1053/SD card
#define MOSI 23      // Output data, to VS1053/SD card
#define RESET  -1      // VS1053 reset pin (unused!)
#define MP3CS     16      // VS1053 chip select pin (output)
#define XDCS    17      // VS1053 Data/command select pin (output)
#define SDCS 26     // Card chip select pin
#define DREQ 25       // VS1053 Data request, ideally an Interrupt pin
Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(RESET, MP3CS, XDCS, DREQ, SDCS);

volatile bool listenMode = false;
volatile bool listenModeJustStarted = false;
volatile uint8_t interruptCounter = 0;

unsigned long listenStart = millis();
unsigned long listenDuration = 25;
unsigned long currentTime = millis();

uint8_t currentTrack = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Adafruit VS1053 Simple Test");

  if (! musicPlayer.begin()) {
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
  Serial.println(F("VS1053 found"));
  
   if (!SD.begin(SDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);
  }
  Serial.println("SD found!");
  
  musicPlayer.setVolume(2,2);
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);


  pinMode(15, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(15), inputSensed, CHANGE);

}

void inputSensed(){
    if(listenMode){
        interruptCounter++;
    } else {
        listenMode = true;
        listenModeJustStarted = true;
    }
}

void listeningEnded(){
    Serial.println("listening Ended");
    Serial.print("COUNTER: ");Serial.println(interruptCounter);

    String filename = "/track00";

    if(interruptCounter >= 10){
      filename = "/track0";
    }

    filename = filename + interruptCounter;
    filename = filename + ".mp3";
    const char* filenameC = filename.c_str();

    if(currentTrack != interruptCounter && interruptCounter != 0){
      musicPlayer.startPlayingFile(filenameC);
      Serial.println(interruptCounter);
      if(interruptCounter < 10){
        currentTrack = interruptCounter;
      }
    }

    interruptCounter = 0;
    listenMode = false;
    listenModeJustStarted = false;
}


void loop() {

  if(!musicPlayer.playingMusic){
    String filename = "/track00";
    filename = filename + currentTrack;
    filename = filename + ".mp3";
    const char* filenameC = filename.c_str();
    musicPlayer.startPlayingFile(filenameC);
  }

  if(listenMode){

    if(listenModeJustStarted){
        listenStart = millis();
        listenModeJustStarted = false;
    }

    currentTime = millis();
    if (listenStart + listenDuration < currentTime)
    {   
        listenMode = false;
        listeningEnded();
    }
  }

}