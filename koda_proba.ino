#include <Wire.h>
#include <Adafruit_VL53L0X.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define TFT_CS     15 
#define TFT_DC      0 
#define TFT_RST     2 

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

const int MAX_DOSEG_CM = 150;

void setup() {
  Serial.begin(115200);
  Wire.begin(4, 5); 
  tft.initR(INITR_BLACKTAB); 
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  
  if (!lox.begin()) {
    tft.setCursor(15, 55);
    tft.setTextColor(ST77XX_RED);
    tft.print("NAPAKA SENZORJA");
    while(1);
  }

  // High Accuracy mode (200ms)
  lox.setMeasurementTimingBudgetMicroSeconds(200000);

  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(2);
  tft.setCursor(15, 10);
  tft.print("RAZDALJA:");
}

void loop() {
  long vsotaMM = 0;
  int uspesneMeritve = 0;
  unsigned long startMillis = millis();

  // 1-sekundno okno vzorčenja
  while (millis() - startMillis < 1000) {
    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false);

    if (measure.RangeStatus != 4 && measure.RangeMilliMeter <= (MAX_DOSEG_CM * 10)) {
      vsotaMM += measure.RangeMilliMeter;
      uspesneMeritve++;
    }
  }

  tft.fillRect(10, 40, 150, 60, ST77XX_BLACK); 

  if (uspesneMeritve > 0) {
    float razdaljaCm = (vsotaMM / (float)uspesneMeritve) / 10.0;

    // --- DINAMIČNA KALIBRACIJA ---
    // Če je razdalja večja od 50 cm, uporabi korekcijski faktor.
    // Faktor 0.98 pomeni, da bomo rezultat zmanjšali za 2% (kar je 1cm pri 50cm).
    if (razdaljaCm > 50.0) {
      // Formula: ohrani 50cm, vse kar je nad tem pa korigiraj
      // Če pri 50cm kaže 51cm, potrebujemo faktor 0.9803
      razdaljaCm = 50.0 + (razdaljaCm - 50.0) * 0.98; 
    }
    // -----------------------------

    tft.setCursor(15, 45); 
    tft.setTextSize(4);
    tft.setTextColor(ST77XX_GREEN);
    tft.print(razdaljaCm, 1); 
    
    tft.setCursor(15, 85); 
    tft.setTextSize(2);
    tft.setTextColor(ST77XX_WHITE);
    tft.print("cm");

    // Število vzorcev (za občutek hitrosti)
    tft.setTextSize(1);
    tft.setCursor(130, 110);
    tft.setTextColor(ST77XX_YELLOW);
    tft.print("n="); tft.print(uspesneMeritve);

  } else {
    tft.setCursor(15, 55);
    tft.setTextSize(2);
    tft.setTextColor(ST77XX_RED);
    tft.print("NI SIGNALA");
  }
}
