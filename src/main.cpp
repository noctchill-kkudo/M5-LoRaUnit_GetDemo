#include <Arduino.h>
#include <M5Stack.h>
#include "LoRa.h"

void setup() {
  Serial.begin(115200);
  M5.begin();
  LoRaInit();

  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextColor(WHITE,MAROON);
  M5.Lcd.print("     LoRa Module Host     ");
}

void loop() {
  if (Serial2.available() > 0) {
    String rxs = Serial2.readString();
    Serial.print(rxs);
    char Buf[5];
    rxs.toCharArray(Buf, 5);
    int16_t rssi = strtol(Buf,NULL,16);
    rxs = rxs.substring(4);

    M5.Lcd.setCursor(15, 50);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(3);
    M5.Lcd.print("MSG : ");
    M5.Lcd.print(rxs);

    M5.Lcd.setCursor(15, 100);
    M5.Lcd.setTextColor(GREEN);
    M5.Lcd.print("RSSI : ");
    M5.Lcd.print(rssi);
    M5.Lcd.print("  dB");

    delay(1000);
    M5.Lcd.fillRect(100, 50, 200, 30, BLACK);
    M5.Lcd.fillRect(120, 100, 100, 30, BLACK);
  }
}