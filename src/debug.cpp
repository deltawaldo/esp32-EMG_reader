//This code is used to test out hardware.
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht;
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);
int voltagePin = 35;
int batteryPercent = 0;
int bodyTemp = 0;
int bodyHumid = 0;

#define BUTTON_A 15
#define BUTTON_B 32
#define BUTTON_C 14

void setup() {
  // Some boards work best if we also make a serial connection
  Serial.begin(9600);

  Serial.println("128x64 OLED FeatherWing test");
  delay(250); // wait for the OLED to power up
  display.begin(0x3C, true); // Address 0x3C default

  Serial.println("OLED begun");

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
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

void loop() {

  //read the temp and humidity
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  bodyTemp = (9/5)*temp.temperature+32;
  bodyHumid = humidity.relative_humidity;
  batteryPercent = (((analogRead(voltagePin)*2*3.3/4095)-3)/.7)*100;
  if(batteryPercent > 100){
    batteryPercent=100;
  }

  if(!digitalRead(BUTTON_A)) {
    display.setCursor(0,0);
    display.clearDisplay();
    display.setTextSize(2);
    display.print("TACK DEBUG\n");
    display.setTextSize(1);
    display.print("Temp is: ");
    display.print(bodyTemp);
    display.print(" deg F.\n");
    display.print("Hum  is: ");
    display.print(bodyHumid);
    display.print(" %rH.\n");
    display.print("Batt  %: ");
    display.print(batteryPercent);
    display.print(" %.\n");
   }

  if(!digitalRead(BUTTON_B)) {
    display.setCursor(0,0);
    display.clearDisplay();
    display.setTextSize(2);
    display.print("TACK DEBUG\n");
    display.setTextSize(1);
    display.print("Hum is: ");
    display.print(humidity.relative_humidity);
    display.print("%rH.\n");
  }

  if(!digitalRead(BUTTON_C)) {
    display.clearDisplay();
    display.setCursor(0,0);
  };
  
 //debug flags
  //Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
  //Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");
  //Serial.print(display.getCursorY());

  delay(10);
  
  yield();
  
  display.display();
}