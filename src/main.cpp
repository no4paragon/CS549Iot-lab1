#include <Arduino.h>
#include <TFT_eSPI.h>
#include <Adafruit_CAP1188.h>
#include <Wire.h>
#include <SPI.h>
#define DISABLE_ALL_LIBRARY_WARNINGS

TFT_eSPI tft = TFT_eSPI(135, 240);



// Reset Pin is used for I2C or SPI
#define CAP1188_RESET  9

// CS pin is used for software or hardware SPI
#define CAP1188_CS  10

// These are defined for software SPI, for hardware SPI, check your
// board's SPI pins in the Arduino documentation
#define CAP1188_MOSI  11
#define CAP1188_MISO  12
#define CAP1188_CLK  13

//Part3
int cspin = GPIO_NUM_26;
int clkpin = GPIO_NUM_25;
int misopin = GPIO_NUM_33;
int mosipin = GPIO_NUM_32;
int resetpin = -1;
int sckpin = GPIO_NUM_25;
const int slavePin = GPIO_NUM_26;

// Software SPI
Adafruit_CAP1188 cap = Adafruit_CAP1188(clkpin, misopin, mosipin, cspin, resetpin);

// set up the speed, data order and data mode
SPISettings settingsA(2000000, MSBFIRST, SPI_MODE1); 
SPISettings settingsB(16000000, LSBFIRST, SPI_MODE3); 

void setup() {

  //Part 1
  Serial.begin(9600);
  cap.begin();
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(TFT_YELLOW);
  tft.setCursor(0,0);
  tft.setTextDatum(MC_DATUM);
  tft.setTextSize(5);
  
  Serial.println("CAP1188 test!");

  // Part 2
  // Initialize the sensor, if using i2c you can pass in the i2c address
  // if (!cap.begin(0x28)) {
  //   Serial.println("CAP1188 not found");
  //   while (1);
  // }
  // Serial.println("CAP1188 found!");

  // Part 3
  sleep(1);
  if(!cap.begin()){
    Serial.println("CAP1188 not found");
    while(1);
  }
  Serial.println("CAP1188 found!");

  delay(1000);
}

int count = 0;

void loop() {

  //Part 1
  // tft.fillScreen(TFT_BLUE);
  // tft.drawString(String(count), tft.width()/2, tft.height()/2-16);
  // sleep(1);
  // count++;

  //Part 2 & 3
  uint8_t touched = cap.touched();

  if (touched == 0) {
    // No touch detected
    Serial.println("No touch detected");
  } else {
    Serial.println("Touch detected");
  }

  for (uint8_t i=0; i<8; i++) {
    if (touched & (1 << i)) {
      count += 1;
    }
  }

  tft.fillScreen(TFT_RED);
  tft.setTextColor(TFT_WHITE);
  tft.drawString(String(count), tft.width()/2, tft.height()/2-16);
  count = 0;
  delay(50);
}