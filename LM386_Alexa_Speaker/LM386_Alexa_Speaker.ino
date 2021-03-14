#include <pcmConfig.h>
#include <pcmRF.h>
#include <TMRpcm.h>

#include <SD.h>
#define SD_ChipSelectPin 4
#include <SPI.h>

//one minutes in Milliseconds
#define oneMin 60000
//5 seconds long hold
#define fiveSecs 5000

//file setup
const int chipSelect = 4;
File file;

//WAV setup 
TMRpcm tmrpcm; 

//Button Setup
const int buttonPin = 2;
int buttonState = 0;
bool buttonPressed = false;

//Timer Setup
unsigned long lastCall;
unsigned long buttonPressTimer;

//Last File No
int lastNo;

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino Speaker Test");

  //Speaker data out pin
  tmrpcm.speakerPin = 9;

  //Micro SD card initialise checks
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
    return;
  }else{
    Serial.println("SD Sucess");
  }

  //Random Song Setup
  randomSeed(analogRead(0));
  
  //TMRpcm Property Setup
  tmrpcm.setVolume(5);
  tmrpcm.quality(1);

  //Button pin setup
  pinMode(buttonPin, INPUT);

  //Builtin LED
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {

  buttonState = digitalRead(buttonPin);
  
  // check if the pushbutton is pressed
  if (buttonState == HIGH) {
    
    if(!buttonPressed){
      buttonPressTimer = millis();
      
      buttonPressed = true;
      Serial.println("Button Pressed");
      
      if(!tmrpcm.isPlaying() && (!lastCall || (millis() - lastCall >= oneMin))){
        tmrpcm.play(generateFileName().c_str());
        lastCall = millis();
      }else{
        Serial.println("Button pressed but play condirions not met");
      }
    }

    if((millis() - buttonPressTimer > fiveSecs)){
      buttonPressTimer = 0;
      lastCall = 0;
    }
    
  }else{
    buttonPressed = false;
  }
}

//Method to generate a filename (assuming it follows the correct naming convention)
String generateFileName(){
  String ext = String(".wav");
  String filename = String(getNewRandomNumber() + ext);
  Serial.println("About to play - " + filename);
  return filename;
}

//Method to generate a new random number that isnt the same as the last one.
int getNewRandomNumber(){
  int fileNo;
  do{
    fileNo = random(2, 7);
  }while(fileNo == lastNo);
  
  lastNo = fileNo;
  return fileNo;
}
