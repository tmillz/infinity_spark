// Infinity Spark Example Code

// include the library code:
#include <LiquidCrystal.h>

// Fan
#define ENABLE 9
#define DIRA 6
#define DIRB 7

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// lowest and highest flame sensor readings:
const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum

// Fan
int i;

// Define Speaker pin
const int piezoPin = 8;

// Define fan pins


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("JBMDL");

  // Fan ---set pin direction
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  
  // initialize serial communication @ 9600 baud:
  Serial.begin(9600);  
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print("Infinity Spark!");

  // Spark Detector
  // read the sensor on analog A0:
  int sensorReading = analogRead(A0);
  // map the sensor range (four options):
  // ex: 'long int map(long int, long int, long int, long int, long int)'
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);
  
  // range value:
  switch (range) {
  case 0:    // A fire closer than 1.5 feet away.
    Serial.println("** Close Spark **");
    tone(piezoPin, 1000, 500);
    digitalWrite(ENABLE,HIGH); // enable fan on
    digitalWrite(DIRA,HIGH); //one way
    digitalWrite(DIRB,LOW);
    break;
  case 1:    // A fire between 1-3 feet away.
    Serial.println("** Distant Spark **");
    tone(piezoPin, 1000, 500);
    // digitalWrite(ENABLE,HIGH); // enable fan on
    // digitalWrite(DIRA,HIGH); //one way
    // digitalWrite(DIRB,LOW);
    break;
  case 2:    // No fire detected.
    Serial.println("No Spark");
    //digitalWrite(DIRA,LOW); // fan stop
    break;
  }
  delay(1);  // delay between reads
}
