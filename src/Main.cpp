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

int ledsAndButtons[4][2]={{LED_YELLOW,BOTTON_YELLOW},{LED_RED,BOTTON_RED},{LED_GREEN,BOTTON_GREEN},{LED_WHITE,BOTTON_WHITE}};
int sizeSequenceLeds;
int (*sequenceLeds)[2];


int bottons[4] = {BOTTON_YELLOW,BOTTON_RED,BOTTON_GREEN,BOTTON_WHITE};

// int ledNow;
void readBottonSequence(){

}

void blink(int led, int delayy){
  Serial.println("lighting led ");
  Serial.println(led );
  digitalWrite(led,HIGH);
  delay(delayy);
  digitalWrite(led,LOW);
  delay(delayy);
}

void turnOnAll(int leds[][2], int delayy){
  for(int i =0;i<4;i++){
    digitalWrite(leds[i][0],HIGH);
  }
  delay(delayy);
}
void turnOffAll(int leds[][2], int delayy){
  for(int i =0;i<4;i++){
    digitalWrite(leds[i][0],LOW);
  }
  delay(delayy);
}
void startExitPorts(int leds[4][2]){
  for(int i;i<4;i++){
    Serial.println("Starting exit ");
    Serial.println(leds[i][0]);
    pinMode(leds[i][0], OUTPUT);
  }
}
void startEntrancePorts(int botton[4][2]){
  for(int i = 0;i<4;i++){
    Serial.println("Starting entrance");
    Serial.println(botton[i][1]);
    pinMode(botton[i][1], INPUT_PULLUP);
  }
}

void startGeniusGame(){
  Serial.println("Starting exit ports");
  startExitPorts(ledsAndButtons);
  Serial.println("Starting Enter ports");
  startEntrancePorts(ledsAndButtons);
  sizeSequenceLeds =0;

}
void increaseSequence(int novoLedButton[1][2]){
  Serial.println("Creating new Array of sequence leds");
  int seqTemp[sizeSequenceLeds+1][2];
  for(int i = 0 ; i<=sizeSequenceLeds;i++){
    if(i==sizeSequenceLeds){
      Serial.println("Adding to the new sequence the led ");
      Serial.println(novoLedButton[0][0]);
      seqTemp[i][0] = novoLedButton[0][0];
      seqTemp[i][1] = novoLedButton[0][1];
      sequenceLeds = seqTemp;
    }else{
      Serial.println("Adding to the new sequence the led ");
      Serial.println(sequenceLeds[i][0]);
      seqTemp[i][0] = sequenceLeds[i][0];
      seqTemp[i][1] = sequenceLeds[i][1];
    }
  }
  sizeSequenceLeds++;
}
void blinkSequence(int (*seq)[2],int sizeSeq){
  for(int i=0; i<sizeSeq;i++){
    blink(seq[i][0], HALF_MINUTE);
  }
}
void errouSequencia(){
  turnOnAll(ledsAndButtons, 5000);
  int seqTemp[0][2];
  sequenceLeds = seqTemp;
  sizeSequenceLeds = 0;
}
void setup(){
  Serial.begin(9600);
  startGeniusGame();
}
void loop(){
//   Serial.println("Starting loop");
//   int ledPosition = random(0,3);
//   Serial.println("led position");
//   int ledButtonTemp[1][2] = {{ledsAndButtons[ledPosition][0],ledsAndButtons[ledPosition][1]}};
// Serial.println("increasing sequence with led  ");
//   Serial.println(ledButtonTemp[0][0] );
//   increaseSequence(ledButtonTemp);
//   Serial.println("Blik the new sequence");
//   blinkSequence(sequenceLeds, sizeSequenceLeds);
//   // readBottonSequence();
}
