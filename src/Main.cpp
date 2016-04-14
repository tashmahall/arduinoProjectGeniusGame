#include "Arduino.h"

#define LED_YELLOW 3
#define LED_RED 4
#define LED_GREEN 5
#define LED_WHITE 6
#define HALF_MINUTE 500;

int leds[4]={LED_YELLOW,LED_RED,LED_GREEN,LED_WHITE};
int *sequence;
int sizeSequence;

// int ledNow;

void blink(int led, int delayy){
  Serial.println(led);
  digitalWrite(led,HIGH);
  delay(delayy);
  digitalWrite(led,LOW);
  delay(delayy);
}

void acendeTodos(int leds[], int delayy){

  for(int i =0;i<4;i++){
    digitalWrite(leds[i],HIGH);
  }
  delay(delayy);
}
void apagaTodos(int leds[], int delayy){
  for(int i =0;i<4;i++){
    digitalWrite(leds[i],LOW);
  }
  delay(delayy);
}
void iniciaPortasSaidas(int leds[]){
  for(int i;i<4;i++){
    pinMode(leds[i], OUTPUT);
  }
}

void iniciarJogoGenius(){
  iniciaPortasSaidas(leds);
  sizeSequence =0;
  int sTepm[sizeSequence];
  sequence = sTepm;

}
void aumentaSequencia(int novoLed){
  int seqTemp[sizeSequence+1];
  for(int i = 0 ; i<sizeSequence+1;i++){
    if(i==sizeSequence){
      seqTemp[i] = novoLed;
      sequence = seqTemp;
    }else{
      seqTemp[i] = sequence[i];
    }
  }
  sizeSequence++;
}
void blinkSequence(int *seq,int sizeSeq){
//TODO finish this method
}
void errouSequencia(){
  acendeTodos(leds, 2000);
  int seqTemp[0];
  sequence = seqTemp;
  sizeSequence = 0;
}
void setup(){
  Serial.begin(9600);
  iniciarJogoGenius();
}
void loop(){
  int led = random(0,3);
  aumentaSequencia(leds[led]);
}
