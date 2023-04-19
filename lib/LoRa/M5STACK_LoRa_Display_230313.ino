//
//  920MHz LoRa/FSK RF module ES920LR3 
//  receive data display
//
//  MaiaR Create 2022/06/05
//  add RSSI 2023/01/20
//
//  Applicable model
//  * M5Stack BASIC    with Module/UNIT
//  * M5Stack CORE2    with Module/UNIT
//  * M5Stack ATOM S3  with KIT/UNIT
//


#ifdef ARDUINO_M5STACK_Core2
#include <M5Core2.h>
#define TSIZE 4
#define RPOS 180
#define SX 270
#define SY 35
#define SR 15
#elif defined ARDUINO_M5Stack_Core_ESP32
#include <M5Stack.h>
#define TSIZE 4
#define RPOS 180
#define SX 270
#define SY 35
#define SR 15
#elif defined ARDUINO_M5Stack_ATOMS3
#include <M5AtomS3.h>
#define TSIZE 2
#define RPOS 100
#define SX 100
#define SY 80
#define SR 8
#endif

#include "LoRa.h"


void setup() {
  M5.begin();
  LoRaInit();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(TSIZE);
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.println("LoRa");
  M5.Lcd.println("Display");
  M5.Lcd.println("Stand-by");
#ifdef ARDUINO_M5STACK_Core2
  M5.Spk.begin();
#elif defined ARDUINO_M5Stack_Core_ESP32
  M5.Speaker.begin();
  M5.Speaker.setVolume(2);
#endif
}

void loop(){
  if (Serial2.available() > 0) {
    String rxs = Serial2.readString();
    Serial.print(rxs);
    char Buf[5];
    rxs.toCharArray(Buf, 5);
    int16_t rssi = strtol(Buf,NULL,16);
    rxs = rxs.substring(4);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.fillCircle(SX, SY, SR, GREEN);
    M5.Lcd.setCursor(0, 20);
    if (rxs.length() > 12){
      M5.Lcd.println("T:" + rxs.substring( 2, 6 ) + " 'C" );
      M5.Lcd.println("H:" + rxs.substring( 8,12 ) + " %"  );
      if (rxs.length() > 16){
        M5.Lcd.println("P:" + rxs.substring(14,18 ) + " hPa");
      }
    } else {
      M5.Lcd.println(rxs);
    }
    M5.Lcd.setCursor(0, RPOS);
    M5.Lcd.print("R: ");
    M5.Lcd.print(rssi);
    M5.Lcd.print(" dB");
#ifdef ARDUINO_M5STACK_Core2
    M5.Spk.DingDong();
#elif defined ARDUINO_M5Stack_Core_ESP32
    M5.Speaker.beep();
    delay(100);
    M5.Speaker.mute();
#endif
    delay(400);
    M5.Lcd.fillCircle(SX, SY, SR, BLACK);
  }
}
