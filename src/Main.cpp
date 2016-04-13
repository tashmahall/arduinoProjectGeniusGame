#include "Arduino.h"

#define LED_YELLOW 3
#define LED_RED 4
#define LED_GREEN 5
#define LED_WHITE 6

int leds[4]={LED_YELLOW,LED_RED,LED_GREEN,LED_WHITE};

// int ledNow;

void blink(int led, int delayy){
  Serial.println(led);
  digitalWrite(led,HIGH);
  delay(delayy);
  digitalWrite(led,LOW);
  delay(delayy);
}

void setup(){
  Serial.begin(9600);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_WHITE, OUTPUT);
}
void loop(){
  for(int i =1 ; i<4;i++){
    // Serial.println(i);
    blink(leds[i],200);

  }
  for(int h = 2 ; h>-1;h--){
    // Serial.println(h);
    blink(leds[h],200);
  }
}
