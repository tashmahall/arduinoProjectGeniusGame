#include "Arduino.h"
<<<<<<< HEAD
#define LED_YELLOW 3
#define LED_RED 4
#define LED_GREEN 5
#define LED_WHITE 6


int ledNow;

void blink(int led, int delayy){
  digitalWrite(led,HIGH);
  Serial.println(led);
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
  for(int i =4 ; i<7;i++){
    ledNow = i;
    blink(ledNow,200);

  }
  for(int h = 5 ; h>2;h--){
    ledNow = h;
    blink(ledNow,50);
  }


=======

void setup(){

}

void loop(){
  
>>>>>>> 181debe18a47d8102a73b0d6e9cdc47b40394fbd
}
