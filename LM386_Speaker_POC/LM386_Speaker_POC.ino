#include <SD.h>

//file setup
int chipSelect = 8;
File file;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Arduino Speaker Test");

  //Micro SD Stuff
  pinMode(chipSelect, OUTPUT);// chip select pin must be set to OUTPUT mode
  if (!SD.begin(chipSelect)) { // Initialize SD card
    Serial.println("Could not initialize SD card."); // if return value is false, something went wrong.
  }else{
    Serial.println("initialized SD card.");
  }

  if (SD.exists("1.wav")) {
    Serial.println("audio clip exists in setup");
  }else{
    Serial.println("audio clip missing in setup");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
