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

int ledsAndButtons[4][2]={{LED_YELLOW,BOTTON_YELLOW},
                          {LED_RED   ,BOTTON_RED   },
                          {LED_GREEN ,BOTTON_GREEN },
                          {LED_WHITE ,BOTTON_WHITE }};
int sizeSequence;
int *sequenceLeds;
int *sequenceButtons;


int bottons[4] = {BOTTON_YELLOW,BOTTON_RED,BOTTON_GREEN,BOTTON_WHITE};

// int ledNow;
void readBottonSequence(){
  //TODO Implements
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
//    Serial.println(leds[i][0]);
    pinMode(leds[i][0], OUTPUT);
  }
}
void startEntrancePorts(int botton[4][2]){
  for(int i = 0;i<4;i++){
//    Serial.println(botton[i][1]);
    pinMode(botton[i][1], INPUT_PULLUP);
  }
}

void startGeniusGame(){
//  Serial.println("Starting exit ports");
  startExitPorts(ledsAndButtons);
//  Serial.println("Starting Enter ports");
  startEntrancePorts(ledsAndButtons);
  sizeSequence =0;

}
void increaseSequence(int novoLedButton[1][2]){
  Serial.println("Creating new sequence size");
  Serial.println(sizeSequence+1);
  Serial.println("\n");
  delay(1000);
  int *ledSeqTemp = new int [sizeSequence+1];
  int *buttonSeqTemp= new int[sizeSequence+1];
 
  for(int i = 0 ; i<=sizeSequence;i++){
    
    if(i==sizeSequence){
      ledSeqTemp[i] = novoLedButton[0][0];
      buttonSeqTemp[i] = novoLedButton[0][1];
      
      Serial.println("Adding new led to the sequence");
      Serial.println(novoLedButton[0][0]);
      delay(2000);
      break;
    }else{
      Serial.println("Adding old led to the sequence");
      Serial.println(sequenceLeds[i]);
      ledSeqTemp[i] = sequenceLeds[i];
      buttonSeqTemp[i] = sequenceButtons[i];
    }
  }
  sequenceLeds = ledSeqTemp;
  sequenceButtons = buttonSeqTemp;
  sizeSequence++;
  delete [] ledSeqTemp;
  delete [] buttonSeqTemp;
  delay(2000);
}
void blinkSequence(int (*seq)[2],int sizeSeq){
  for(int i=0; i<sizeSeq;i++){
    blink(seq[i][0], HALF_MINUTE);
  }
}
void missedSequence(){
  turnOnAll(ledsAndButtons, 5000);
  int seqTemp[0][2];
}
void setup(){
  Serial.begin(9600);
  startGeniusGame();
}
void loop(){
  Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n");
  Serial.println("Starting loop");
  Serial.println("Size of sequence led");
  Serial.println(sizeSequence);
  int randomNumber = random(0,3);
  Serial.println("Randomic Number");
  Serial.println(randomNumber);
  Serial.println("\n");
  int ledTemp = ledsAndButtons[randomNumber][0];
  int buttonTemp = ledsAndButtons[randomNumber][1];
  int ledButtonTemp[1][2] = {{ledTemp,buttonTemp}};
  // Serial.println("increasing sequence with led  ");
  // Serial.println(ledButtonTemp[0][0] );
  increaseSequence(ledButtonTemp);
  delay(1000);
//   Serial.println("Blik the new sequence");
//   blinkSequence(sequenceLeds, sizeSequence);
//   // readBottonSequence();
}

