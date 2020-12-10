#include <SD.h> //Load SD library

//file stuff
int chipSelect = 8;
File file; // file object that is used to read and write data

//button stuff
int buttonPin = 4;
int buttonState = 0;
bool buttonPressed = false;

void setup() {
  // Debug stuff
  Serial.begin(9600);
  Serial.println("Arduino SD Card Test 1");

  //Micro SD Stuff
  pinMode(chipSelect, OUTPUT);// chip select pin must be set to OUTPUT mode
  if (!SD.begin(chipSelect)) { // Initialize SD card
    Serial.println("Could not initialize SD card."); // if return value is false, something went wrong.
  }else{
    Serial.println("initialized SD card.");
  }

  if (SD.exists("Test.txt")) {
    Serial.println("File exists in setup");
  }else{
    file = SD.open("Test.txt", FILE_WRITE); // open "file.txt" to write data
    if (file) {
      file.println("Hello World"); // write "Hello world" to new file
      file.close(); // close file
      Serial.println("File Created During Setup");
    } else {
      Serial.println("Could not open file (writing).");
    }
  }

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
      Serial.println("button pressed");

      file = SD.open("Test.txt", FILE_READ);
      Serial.println("--- Reading start ---");
      char character;
      while ((character = file.read()) != -1) { // this while loop reads data stored in "Test.txt" and prints it to serial monitor
        Serial.print(character);
      }
      file.close();
      Serial.println("--- Reading end ---");
      
    }

  }else{
    buttonPressed = false;
  }
}
