#include "Arduino.h"

#define LED_YELLOW 3
#define LED_RED 4
#define LED_GREEN 5
#define LED_WHITE 6
#define HALF_MINUTE 500

#define BOTTON_YELLOW 10
#define BOTTON_RED  11
#define BOTTON_GREEN  12
#define BOTTON_WHITE  13

int leds[4]={LED_YELLOW,LED_RED,LED_GREEN,LED_WHITE};
int *sequenceLeds;
int sizeSequenceLeds;

int bottons[4] = {BOTTON_YELLOW,BOTTON_RED,BOTTON_GREEN,BOTTON_WHITE};

// int ledNow;
void readBottonSequence(){
  //TODO Implements 
}

void blink(int led, int delayy){
  Serial.println(led);
  digitalWrite(led,HIGH);
  delay(delayy);
  digitalWrite(led,LOW);
  delay(delayy);
}

void turnOnAll(int leds[], int delayy){

  for(int i =0;i<4;i++){
    digitalWrite(leds[i],HIGH);
  }
  delay(delayy);
}
void turnOffAll(int leds[], int delayy){
  for(int i =0;i<4;i++){
    digitalWrite(leds[i],LOW);
  }
  delay(delayy);
}
void startExitPorts(int leds[]){
  for(int i;i<4;i++){
    pinMode(leds[i], OUTPUT);
  }
}
void startEnterPorts(int botton[]){
  for(int i = 10;i<14;i++){
    pinMode(botton[i], INPUT_PULLUP);
  }
}

void iniciarJogoGenius(){
  startExitPorts(leds);
  startEnterPorts(bottons);
  sizeSequenceLeds =0;
  int sTepm[sizeSequenceLeds];
  sequenceLeds = sTepm;

}
void increaseSequence(int novoLed){
  int seqTemp[sizeSequenceLeds+1];
  for(int i = 0 ; i<sizeSequenceLeds+1;i++){
    if(i==sizeSequenceLeds){
      seqTemp[i] = novoLed;
      sequenceLeds = seqTemp;
    }else{
      seqTemp[i] = sequenceLeds[i];
    }
  }
  sizeSequenceLeds++;
}
void blinkSequence(int *seq,int sizeSeq){
  for(int i=0; i<sizeSeq;i++){
    blink(seq[i], HALF_MINUTE);
  }
}
void errouSequencia(){
  turnOnAll(leds, 2000);
  int seqTemp[0];
  sequenceLeds = seqTemp;
  sizeSequenceLeds = 0;
}
void setup(){
  Serial.begin(9600);
  iniciarJogoGenius();
}
void loop(){
  int led = random(0,3);
  increaseSequence(leds[led]);
  blinkSequence(sequenceLeds, sizeSequenceLeds);
  readBottonSequence();
}
