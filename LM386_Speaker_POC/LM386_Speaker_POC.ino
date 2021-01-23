#include <pcmConfig.h>
#include <pcmRF.h>
#include <TMRpcm.h>

#include <SD.h>
#define SD_ChipSelectPin 4
#include <SPI.h>


//file setup
int chipSelect = 4;
File file;

//music setup 
TMRpcm tmrpcm; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Arduino Speaker Test");

  //music stuff
  tmrpcm.speakerPin = 9;

  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
    return;
  }else{
    Serial.println("SD Sucess");
  }

  //tmrpcm.setVolume(5);
  tmrpcm.setVolume(5);
  //tmrpcm.quality(0);
  tmrpcm.play("1.wav");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(tmrpcm.isPlaying()){
    Serial.println("playing"); 
  }
}
