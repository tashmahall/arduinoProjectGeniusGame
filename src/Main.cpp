#include "Arduino.h"

#define LED_YELLOW 3
#define LED_RED 4
#define LED_GREEN 5
#define LED_WHITE 6
#define HALF_SECOND 500

#define BOTTON_YELLOW 9
#define BOTTON_RED  10
#define BOTTON_GREEN  11
#define BOTTON_WHITE  12

#define SEED 0

int ledsAndButtons[4][2]={{LED_YELLOW,BOTTON_YELLOW},
                          {LED_RED   ,BOTTON_RED   },
                          {LED_GREEN ,BOTTON_GREEN },
                          {LED_WHITE ,BOTTON_WHITE }};

int sizeSequence = 0;
int *sequenceLeds;
int *sequenceButtons;



// int ledNow;

void translateLed(int led){
  // Serial.println(led);
  switch(led){
    case 3:
      Serial.println("LED_YELLOW");
      break;
    case 4:
      Serial.println("LED_RED");
      break;
    case 5:
      Serial.println("LED_GREEN");
      break;
    case 6:
      Serial.println("LED_WHITE");
      break;
    default:
      Serial.println("Number unrecognized");
  }
}
void translateButton(int button){
  // Serial.println(button);
  switch(button){
    case 9:
      Serial.println("BOTTON_YELLOW");
      break;
    case 10:
      Serial.println("BOTTON_RED");
      break;
    case 11:
      Serial.println("BOTTON_GREEN");
      break;
    case 12:
      Serial.println("BOTTON_WHITE");
      break;
    default:
      Serial.println("Number unrecognized");
  }
}

void blink(int led, int delayy){
  Serial.println("Blinking led ");
  translateLed(led);
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
  for(int i=0;i<4;i++){
//    Serial.println(leds[i][0]);
    pinMode(leds[i][0], OUTPUT);
  }
}
void startEntrancePorts(int botton[4][2]){
  for(int j = 0;j<4;j++){
//    Serial.println(botton[i][1]);
    pinMode(botton[j][1], INPUT_PULLUP);
  }
}

void startGeniusGame(){
//  Serial.println("Starting exit ports");
  startExitPorts(ledsAndButtons);
//  Serial.println("Starting Enter ports");
  startEntrancePorts(ledsAndButtons);
  sizeSequence =0;

}
int discoveringButtonPressed(){
  int reading =2;
  Serial.println("Reading the Button pressed");
  while (true){
    reading = digitalRead(BOTTON_YELLOW);
    if(reading == 0){
      translateButton(BOTTON_YELLOW);
      return BOTTON_YELLOW;
    }
    reading = digitalRead(BOTTON_RED);
    if(reading == 0){
      translateButton(BOTTON_RED);
      return BOTTON_RED;    
    }
    reading = digitalRead(BOTTON_GREEN);
    if(reading == 0){
      translateButton(BOTTON_GREEN);
      return BOTTON_GREEN;    
    }
    reading = digitalRead(BOTTON_WHITE);
    if(reading == 0){
      translateButton(BOTTON_WHITE);
      return BOTTON_WHITE;    
    }
  } 
  return NULL;
}
void blikButonPressed(int button, int ledsButs[4][2]){
  for (int i = 0 ; i<4 ; i++){
    if(button == ledsButs[i][1]){
      blink(ledsButs[i][0],HALF_SECOND);
    }
  }
}

bool readSequence(int ledsButs[4][2], int seqLed[], int seqButton[], int sizeSeq){
  for (int i = 0 ; i<sizeSeq ; i++){
    int buttonPressed = discoveringButtonPressed();
    blikButonPressed(buttonPressed, ledsButs);
    if(seqButton[i] == buttonPressed) {
      continue;
    }else{
      return false;
    }
  }
  return true;
}

void increaseSequence(int novoLedButton[][2], int *&seqLed, int *&seqButton, int* sizeSeq){
  int newSize = (*sizeSeq+1)*sizeof(int);
  void * newArrayLed = malloc ( newSize );
  void * newArrayButton = malloc ( newSize );
  int sizeTemp = *sizeSeq+1;
  // Serial.println("Creating new sequence size");
  // Serial.println(sizeTemp);
  // Serial.println("\n");
  // delay(1000);
  for(int i = 0 ; i<=sizeTemp-1;i++){
    ((int*)newArrayLed)[i] = 0;
    ((int*)newArrayButton)[i] = 0;
    if(i==sizeTemp-1){
        int lTemp = novoLedButton[0][0];
        int bTemp = novoLedButton[0][1];
        ((int*)newArrayLed)[i] = lTemp;
        ((int*)newArrayButton)[i] = bTemp;
        Serial.println("Added new led to the sequence");
    }else{
        ((int*)newArrayButton)[i]=((int*)seqButton)[i];
        ((int*)newArrayLed)[i]=((int*)seqLed)[i];
        Serial.println("Added old led to the sequence");
      }
      translateLed(((int*)newArrayLed)[i]);
  }
  if (seqButton!=0){
    free(seqButton);
    free(seqLed);
  } 
  *sizeSeq = sizeTemp;
  seqLed = ((int*)newArrayLed);
  seqButton = ((int*)newArrayButton);
  // delay(1000);
}
void blinkSequence(int seq[],int sizeSeq){
  Serial.println("Blinking sequence");
  for(int i=0; i<sizeSeq;i++){
    // translateLed(seq[i]);
    // delay(3000);
    blink(seq[i], HALF_SECOND);
  }
}
void missedSequence(int ledsButs[4][2], int *&seqLed, int *&seqButton, int* sizeSeq){
  for(int j = 2000 ; j>=0 ; j=j-500){
    turnOnAll(ledsButs,j);  
    turnOffAll(ledsButs,j/2);
  }
  free(seqButton);
  free(seqLed);
  *sizeSeq = 0;
  int newSize = (*sizeSeq+1)*sizeof(int);
  void * newArrayLed = malloc ( newSize );
  void * newArrayButton = malloc ( newSize );
  seqLed = ((int*)newArrayLed);
  seqButton = ((int*)newArrayButton);

}
void showLedSequence(){
  for(int i =0; i<sizeSequence; i++){
    // translateLed(sequenceLeds[i]);
  }
  delay(5000);
}
void setup(){
  Serial.begin(9600);
  int seed = analogRead(SEED);
  randomSeed(seed);
  startGeniusGame();
}
void loop(){
  Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n");
  Serial.println("Starting loop");
  Serial.println("Size of sequence led");
  Serial.println(sizeSequence);
  int randomNumber = random(0,4);
  // Serial.println("Randomic Number");
  // Serial.println(randomNumber);
  // Serial.println("\n");
  int ledTemp = ledsAndButtons[randomNumber][0];
  int buttonTemp = ledsAndButtons[randomNumber][1];
  // int ledButtonTemp[1][2] ;= {{ledTemp,buttonTemp}};
  int ledButtonTemp[1][2] ;
  ledButtonTemp[0][0]=ledTemp;
  ledButtonTemp[0][1]=buttonTemp;
  // Serial.println("increasing sequence with led  ");
  // Serial.println(ledButtonTemp[0][0] );
  increaseSequence(ledButtonTemp, sequenceLeds, sequenceButtons, &sizeSequence);
  blinkSequence(sequenceLeds, sizeSequence);
  bool hitSequence = readSequence(ledsAndButtons,sequenceLeds,sequenceButtons,sizeSequence); 
  if (hitSequence == false){
    missedSequence(ledsAndButtons,sequenceLeds, sequenceButtons, &sizeSequence);
  }
  // discoveringButtonPressed();
  // delay(1000);
//   Serial.println("Blik the new sequence");
  // showLedSequence();
//   // readBottonSequence();
  // ledButtonTemp[0][0]=1000000;
  // ledButtonTemp[0][1]=1000000;
  // discoveringButtonPressed();

}

