#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_AHTX0.h>

//declared objects
Adafruit_AHTX0 aht;
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);

//declared pins used
#define BUTTON_A 15
#define BUTTON_B 32
#define BUTTON_C 14

//declared variables
int BATTERY_PERCENT = 0;
float BODY_TEMP = 0;
float BODY_HUMID = 0;

//setup all the stuff
void setup() {
  // Some boards work best if we also make a serial connection
  Serial.begin(9600);

  Serial.println("128x64 OLED FeatherWing test");
  delay(250); // wait for the OLED to power up
  display.begin(0x3C, true); // Address 0x3C default

  Serial.println("OLED begun");

  //display buffer at start
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  display.setRotation(1);
  Serial.println("Button test");

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  // text display tests
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0,0);
  display.setTextSize(2);
  //display.print("Connecting to SSID\n'adafruit':");
  //display.print("connected!");
  //display.println("IP: 10.0.1.23");
  //display.println("Sending val #0");
  display.printf("TACK DEBUG\n");

  display.display(); // actually display all of the above

  //setup AHT20 board
  if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT10 or AHT20 found");

  analogReadResolution(12);
}

//clear the display when asked
void clearDisplay(){
  display.clearDisplay();
  display.setCursor(0,0);
}

//simple display function
void displayData(float BODY_TEMP, float BODY_HUMID, int BATTERY_PERCENT){
  clearDisplay();
  display.setTextSize(2);
  display.print("TACK DEBUG\n");
  display.setTextSize(1);
  display.print("Temp is: ");
  display.print(BODY_TEMP);
  display.print(" deg F.\n");
  display.print("Hum  is: ");
  display.print(BODY_HUMID);
  display.print(" %rH.\n");
  display.print("Batt  %: ");
  display.print(BATTERY_PERCENT);
  display.print(" %.\n");
}

void loop() {

  //read the temp and humidity
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  
  //calculate menu variables
  BODY_TEMP = temp.temperature;
  BODY_TEMP = BODY_TEMP*9/5+32;
  BODY_HUMID = humidity.relative_humidity;
  BATTERY_PERCENT = (((analogRead(BATT_MONITOR)*2*3.3/4095)-3)/.7)*100;
  if(BATTERY_PERCENT> 100) BATTERY_PERCENT=100;

  displayData(BODY_TEMP,BODY_HUMID,BATTERY_PERCENT);

  //button commands, not sure what to do with this yet
  if(!digitalRead(BUTTON_A)) Serial.println("A");
  if(!digitalRead(BUTTON_B)) Serial.println("B");
  if(!digitalRead(BUTTON_C)) clearDisplay();
  
 //debug flags
  //Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
  //Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");
  //Serial.print(display.getCursorY());

  delay(10);
  
  yield();
  
  display.display();
}