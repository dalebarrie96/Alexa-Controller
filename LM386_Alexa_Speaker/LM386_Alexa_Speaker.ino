#include <pcmConfig.h>
#include <pcmRF.h>
#include <TMRpcm.h>

#include <SD.h>
#define SD_ChipSelectPin 4
#include <SPI.h>

//two minutes in Milliseconds
#define twoMins 120000


//file setup
const int chipSelect = 4;
File file;

//music setup 
TMRpcm tmrpcm; 

//button stuff
const int buttonPin = 2;
int buttonState = 0;
bool buttonPressed = false;

//Timer Stuff
unsigned long lastCall;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Arduino Speaker Test");

  //music stuff
  tmrpcm.speakerPin = 9;

  //fileStuff
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
    return;
  }else{
    Serial.println("SD Sucess");
  }
  
  randomSeed(analogRead(0));

  tmrpcm.setVolume(5);
  tmrpcm.quality(1);

  //button stuff
  pinMode(buttonPin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  buttonState = digitalRead(buttonPin);
  
  // check if the pushbutton is pressed
  if (buttonState == HIGH) {
    
    if(!buttonPressed){ //i have no idea why, but arduino doesnt like this inline with parent if
      buttonPressed = true;
      Serial.println("Button Pressed");

      unsigned long now = millis();
      
      if(!tmrpcm.isPlaying() && (!lastCall || (now - lastCall >= twoMins))){
        tmrpcm.play(generateFileName().c_str());
        lastCall = millis();
      }else{
        Serial.println("Button pressed but play condirions not met");
      }
    }
  }else{
    buttonPressed = false;
  }
}

String generateFileName(){
  String ext = String(".wav");
  long fileNo = random(2, 7);
  String filename = String(fileNo + ext);
  Serial.println("About to play - " + filename);
  return filename;
}
