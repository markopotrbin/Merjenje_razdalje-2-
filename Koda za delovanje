#include <Wire.h>
#include <Adafruit_VL53L0X.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define TFT_CS    15 // D8
#define TFT_DC     0 // D3
#define TFT_RST    2 // D4

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

const int steviloMeritev = 5;
int meritve[steviloMeritev];
int indeks = 0;
long vsota = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(4, 5); 

  tft.initR(INITR_BLACKTAB); 
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  
  if (!lox.begin()) {
    while(1);
  }

  // FIKSNI NAPIS - ostane na vrhu
  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(2);
  tft.setCursor(15, 10); // Poravnano na levi rob (15 px od roba)
  tft.print("RAZDALJA:");

  for (int i = 0; i < steviloMeritev; i++) meritve[i] = 0;
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false); 

  if (measure.RangeStatus != 4) {
    vsota = vsota - meritve[indeks];
    meritve[indeks] = measure.RangeMilliMeter;
    vsota = vsota + meritve[indeks];
    indeks = (indeks + 1) % steviloMeritev;

    float povprecje = (vsota / (float)steviloMeritev) / 10.0;

    // Pobrišemo samo spodnji del zaslona (pod napisom RAZDALJA)
    tft.fillRect(10, 40, 150, 80, ST77XX_BLACK);

    // IZPIS ŠTEVILKE - poravnano levo pod naslovom
    tft.setCursor(15, 45); 
    tft.setTextSize(4);
    tft.setTextColor(ST77XX_GREEN);
    tft.print(povprecje, 1);
    
    // IZPIS ENOTE "cm" - v NOVI VRSTI, poravnano levo
    tft.setCursor(15, 85); // 85 px navpično ga postavi v novo vrstico
    tft.setTextSize(2);
    tft.setTextColor(ST77XX_WHITE);
    tft.print("cm");

  } else {
    tft.fillRect(10, 40, 150, 80, ST77XX_BLACK);
    tft.setCursor(15, 55);
    tft.setTextSize(2);
    tft.setTextColor(ST77XX_RED);
    tft.print("ZUNAJ DOSEGA");
  }

  delay(400); 
}
