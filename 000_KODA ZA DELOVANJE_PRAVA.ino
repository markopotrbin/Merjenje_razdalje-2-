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

const int steviloMeritev = 50; 
int meritve[steviloMeritev];

void setup() {
  Serial.begin(115200);
  Wire.begin(4, 5); 

  tft.initR(INITR_BLACKTAB); 
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  
  if (!lox.begin()) {
    while(1);
  }

  // Nastavitev proračuna na 20 ms za maksimalno hitrost senzorja
  lox.setMeasurementTimingBudgetMicroSeconds(20000); 

  // FIKSNI NAPIS
  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(2);
  tft.setCursor(15, 10); 
  tft.print("RAZDALJA:");
}

void loop() {
  long vsota = 0;
  int uspesneMeritve = 0;

  // Hitro vzorčenje podatkov
  for (int i = 0; i < steviloMeritev; i++) {
    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false); 

    if (measure.RangeStatus != 4) {
      vsota += measure.RangeMilliMeter;
      uspesneMeritve++;
    }
  }

  if (uspesneMeritve > 0) {
    
    // Surova izračunana razdalja v centimetrih iz senzorja
    float povprecje = (vsota / (float)uspesneMeritve) / 10.0;

    // --- POPOLNOMA TOČEN TRIDELNI POPRAVEK ODSTOPANJA ---
    if (povprecje > 30.0) {
      povprecje = povprecje - 2.5; // Nad 30 cm odštejemo 1.5 cm
    } 
    else if (povprecje > 20.0) {
      povprecje = povprecje - 1.5; // Med 20 cm in 30 cm odštejemo 0.5 cm
    } 
    else {
      povprecje = povprecje - 1.4; // Do 20 cm odštejemo 1.0 cm
    }

    // Varnostna varovalka za negativne vrednosti
    if (povprecje < 0) povprecje = 0.0;

    // Brisanje starega izpisa pod naslovom
    tft.fillRect(10, 40, 150, 80, ST77XX_BLACK);

    // IZPIS ŠTEVILKE
    tft.setCursor(15, 45); 
    tft.setTextSize(4);
    tft.setTextColor(ST77XX_GREEN);
    tft.print(povprecje, 1);
    
    // IZPIS ENOTE "cm"
    tft.setCursor(15, 85); 
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

  delay(300); 
}
