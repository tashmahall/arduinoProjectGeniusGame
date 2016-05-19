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

int ledred = 4;           // the pin that the LED is attached to
int ledblue = 6;
int ledgreen = 5;

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

void gameOfThronesIntroSong(){

//G3
digitalWrite(ledred, HIGH);
digitalWrite(ledblue, HIGH);
digitalWrite(ledgreen, HIGH);
tone(A0, 1575, 2000);
delay(10000);


////////////////////////////////ONE
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

////////////////////////////////TWO
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

//////////////////////////////THREE
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

///////////////////////////////FOUR
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

///////////////////////////////FIVE

//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);
tone(A0, 131, 375);
delay(400);

//E3
digitalWrite(ledblue, HIGH);
tone(A0, 165, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

///////////////////////////////SIX
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

//////////////////////////////SEVEN

//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//E3
digitalWrite(ledblue, HIGH);
tone(A0, 165, 175);
delay(200);
digitalWrite(ledblue, LOW); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);
digitalWrite(ledred, LOW);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);


//////////////////////////////EIGHT

//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

/////////////////////////////////////////////////CHORUS1////////////////////////////////////////////
  
  
//G4  
digitalWrite(ledred, HIGH);
tone(A0, 392, 1175);
delay(1200);
digitalWrite(ledred, LOW);

//C4
digitalWrite(ledblue, HIGH);
tone(A0, 262, 1175);
delay(1200);
digitalWrite(ledblue, LOW);

//DS4
digitalWrite(ledred, HIGH);
tone(A0, 311, 175);
delay(200);

//F4
digitalWrite(ledblue, HIGH);
tone(A0, 349, 175);
delay(200);

//G4
digitalWrite(ledgreen, HIGH);
tone(A0, 392, 775);
delay(800);

//C4
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 262, 775);
delay(800);

//DS4
digitalWrite(ledred, HIGH);
tone(A0, 311, 175);
delay(200);

//F4
digitalWrite(ledblue, HIGH);
tone(A0, 349, 175);
delay(200);

//////////////////////////////
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

///////////////////////////////
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);



/////////////////////////////
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

/////////////////////////////
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);
// while(brightness > 0)
//   {
//   digitalWrite(ledred, brightness);
//   digitalWrite(ledblue, brightness);
//   digitalWrite(ledgreen, brightness);
//   brightness = brightness - fadeAmount;
//   if (brightness == 0 || brightness == HIGH) {
//     fadeAmount = -fadeAmount ;
//   }
// }
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
// brightness = HIGH;
// fadeAmount = 5;





//F4
digitalWrite(ledred, HIGH);
tone(A0, 349, 1175);
delay(1200);
digitalWrite(ledred, LOW);

//AS4
digitalWrite(ledblue, HIGH);
tone(A0, 233, 1175);
delay(1200);
digitalWrite(ledblue, LOW);

//D4
digitalWrite(ledred, HIGH);
tone(A0, 294, 175);
delay(200);

//DS4
digitalWrite(ledblue, HIGH);
tone(A0, 311, 175);
delay(200);

//F4
digitalWrite(ledgreen, HIGH);
tone(A0, 349, 775);
delay(800);

//AS3
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 233, 775);
delay(800);

//DS4
digitalWrite(ledred, HIGH);
tone(A0, 311, 175);
delay(200);

//D4
digitalWrite(ledblue, HIGH);
tone(A0, 294, 175);
delay(200);

//////////////////////////////
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

///////////////////////////////
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);


/////////////////////////////
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

/////////////////////////////
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

/////////////////////////////////////////////////CHORUS2////////////////////////////////////////////
  
  
//G5  
digitalWrite(ledred, HIGH);
tone(A0, 392, 1175);
delay(1200);
digitalWrite(ledred, LOW);

//C4
digitalWrite(ledblue, HIGH);
tone(A0, 262, 1175);
delay(1200);
digitalWrite(ledblue, LOW);

//DS4
digitalWrite(ledred, HIGH);
tone(A0, 311, 175);
delay(200);

//F4
digitalWrite(ledblue, HIGH);
tone(A0, 349, 175);
delay(200);

//G4
digitalWrite(ledgreen, HIGH);
tone(A0, 392, 775);
delay(800);

//C4
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 262, 775);
delay(800);

//DS4
digitalWrite(ledred, HIGH);
tone(A0, 311, 175);
delay(200);

//F4
digitalWrite(ledblue, HIGH);
tone(A0, 349, 175);
delay(200);

//////////////////////////////
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

///////////////////////////////
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);



/////////////////////////////
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

/////////////////////////////
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);
// while(brightness > 0)
//   {
//   digitalWrite(ledred, brightness);
//   digitalWrite(ledblue, brightness);
//   digitalWrite(ledgreen, brightness);
//   brightness = brightness - fadeAmount;
//   if (brightness == 0 || brightness == HIGH) {
//     fadeAmount = -fadeAmount ;
//   }
// }
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
// brightness = HIGH;
// fadeAmount = 5;

//////////////////////////////////////////

//F4
digitalWrite(ledred, HIGH);
tone(A0, 349, 1175);
delay(1200);
digitalWrite(ledred, LOW);

//AS4
digitalWrite(ledblue, HIGH);
tone(A0, 233, 1175);
delay(1200);
digitalWrite(ledblue, LOW);

//D4
digitalWrite(ledred, HIGH);
tone(A0, 294, 175);
delay(200);

//DS4
digitalWrite(ledblue, HIGH);
tone(A0, 311, 175);
delay(200);

//F4
digitalWrite(ledgreen, HIGH);
tone(A0, 349, 775);
delay(800);

//AS3
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 233, 775);
delay(800);

//DS4
digitalWrite(ledred, HIGH);
tone(A0, 311, 175);
delay(200);

//D4
digitalWrite(ledblue, HIGH);
tone(A0, 294, 175);
delay(200);

//////////////////////////////
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

///////////////////////////////
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);


/////////////////////////////
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

/////////////////////////////
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

/////////////////////////////////////////////////CHORUS3////////////////////////////////////////////
  
  
//G5  
digitalWrite(ledred, HIGH);
tone(A0, 784, 1175);
delay(1200);
digitalWrite(ledred, LOW);

//C5
digitalWrite(ledblue, HIGH);
tone(A0, 523, 1175);
delay(1200);
digitalWrite(ledblue, LOW);

//DS5
digitalWrite(ledred, HIGH);
tone(A0, 622, 175);
delay(200);

//F5
digitalWrite(ledblue, HIGH);
tone(A0, 698, 175);
delay(200);

//G5
digitalWrite(ledgreen, HIGH);
tone(A0, 784, 775);
delay(800);

//C5
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 523, 775);
delay(800);

//DS5
digitalWrite(ledred, HIGH);
tone(A0, 622, 175);
delay(200);

//F5
digitalWrite(ledblue, HIGH);
tone(A0, 698, 175);
delay(200);

//////////////////////////////
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

///////////////////////////////
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);



/////////////////////////////
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

/////////////////////////////
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);
// while(brightness > 0)
//   {
//   digitalWrite(ledred, brightness);
//   digitalWrite(ledblue, brightness);
//   digitalWrite(ledgreen, brightness);
//   brightness = brightness - fadeAmount;
//   if (brightness == 0 || brightness == HIGH) {
//     fadeAmount = -fadeAmount ;
//   }
// }
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
// brightness = HIGH;
// fadeAmount = 5;


////////////////////////////////


//F5
digitalWrite(ledred, HIGH);
tone(A0, 698, 1175);
delay(1200);
digitalWrite(ledred, LOW);

//AS4
digitalWrite(ledblue, HIGH);
tone(A0, 466, 1175);
delay(1200);
digitalWrite(ledblue, LOW);

//D5
digitalWrite(ledred, HIGH);
tone(A0, 587, 575);
delay(600);

//DS5
digitalWrite(ledblue, HIGH);
tone(A0, 622, 575);
delay(600);

//D5
digitalWrite(ledgreen, HIGH);
tone(A0, 587, 575);
delay(600);

//AS4
tone(A0, 466, 575);
delay(600);

///////////////////////////////

//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

///////////////////////////////
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);


/////////////////////////////
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

/////////////////////////////
  
//C3
digitalWrite(ledred, LOW);  
digitalWrite(ledblue, LOW);  
digitalWrite(ledgreen, LOW);  
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);
// while(brightness > 0)
//   {
  // digitalWrite(ledred, brightness);
  // digitalWrite(ledblue, brightness);
  // digitalWrite(ledgreen, brightness);
  // brightness = brightness - fadeAmount;
//   if (brightness == 0 || brightness == HIGH) {
//     fadeAmount = -fadeAmount ;
//   }
// }
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
// brightness = HIGH;
// fadeAmount = 5;



//////////////////////////////////////////////////////////////////////////////////////////

//C5
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 523, 375);
delay(400);


//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

///////////

//C5
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 523, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);


///////////////////////////////////////////

//AS4
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 466, 375);
delay(400);

//D3
digitalWrite(ledred, HIGH);
tone(A0, 147, 175);
delay(200);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200);

//F3
digitalWrite(ledgreen, HIGH);
tone(A0, 175, 375);
delay(400);

/////////

//AS4
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 466, 375);
delay(400);

//D3
digitalWrite(ledred, HIGH);
tone(A0, 147, 175);
delay(200);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200);

//F3
digitalWrite(ledgreen, HIGH);
tone(A0, 175, 375);
delay(400);


//////////////////////////////////////////

//GS4
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 415, 375);
delay(400);

//C3
digitalWrite(ledred, HIGH);
tone(A0, 131, 175);
delay(200);

//D3
digitalWrite(ledblue, HIGH);
tone(A0, 147, 175);
delay(200);

//DS3
digitalWrite(ledgreen, HIGH);
tone(A0, 156, 375);
delay(400);

//////////

//GS4
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 415, 375);
delay(400);

//C3
digitalWrite(ledred, HIGH);
tone(A0, 131, 175);
delay(200);

//D3
digitalWrite(ledblue, HIGH);
tone(A0, 147, 175);
delay(200);

//DS3
digitalWrite(ledgreen, HIGH);
tone(A0, 156, 375);
delay(400);


/////////////////////////////////////////

//G4
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 392, 375);
delay(400);

//AS2
digitalWrite(ledred, HIGH);
tone(A0, 117, 175);
delay(200);

//C3
digitalWrite(ledblue, HIGH);
tone(A0, 131, 175);
delay(200);

//D3
digitalWrite(ledgreen, HIGH);
tone(A0, 147, 375);
delay(400);

///////////

//G4
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 392, 375);
delay(400);

//AS2
digitalWrite(ledred, HIGH);
tone(A0, 117, 175);
delay(200);

//C3
digitalWrite(ledblue, HIGH);
tone(A0, 131, 175);
delay(200);

//D3
digitalWrite(ledgreen, HIGH);
tone(A0, 147, 375);
delay(400);


/////////////////////////////////////////

//DS4
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 311, 375);
delay(400);

//G2
digitalWrite(ledblue, HIGH);
tone(A0, 98, 175);
delay(200);

//GS2
digitalWrite(ledgreen, HIGH);
tone(A0, 104, 175);
delay(200);

//AS2
digitalWrite(ledred, HIGH);
tone(A0, 117, 375);
delay(400);

///////////

//DS4
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 311, 375);
delay(400);

//G2
digitalWrite(ledblue, HIGH);
tone(A0, 98, 175);
delay(200);

//GS2
digitalWrite(ledgreen, HIGH);
tone(A0, 104, 175);
delay(200);

//AS2
digitalWrite(ledred, HIGH);
tone(A0, 117, 375);
delay(400);


//////////////////////////////////////////

//DS4
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 311, 375);
delay(400);

//G2
digitalWrite(ledblue, HIGH);
tone(A0, 98, 175);
delay(200);

//G2
digitalWrite(ledred, HIGH);
tone(A0, 98, 175);
delay(200);

//DS4
digitalWrite(ledgreen, HIGH);
tone(A0, 311, 375);
delay(400);

//F4
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 349, 775);
delay(400);

//GS2
digitalWrite(ledblue, HIGH);
tone(A0, 104, 175);
delay(200);

//GS2
digitalWrite(ledgreen, HIGH);
tone(A0, 104, 175);
delay(200);

//F4
digitalWrite(ledred, HIGH);
tone(A0, 349, 375);
delay(400);

//////////////////////////////////////////

//C4
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 262, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

///////////

//C3
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

//C3
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

//C3
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

//C5
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 523, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

///////////

//C5
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
digitalWrite(ledblue, HIGH);
tone(A0, 523, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);


///////////////////////////////////////////

//AS4
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 466, 375);
delay(400);

//D3
digitalWrite(ledred, HIGH);
tone(A0, 147, 175);
delay(200);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200);

//F3
digitalWrite(ledgreen, HIGH);
tone(A0, 175, 375);
delay(400);

/////////

//AS4
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 466, 375);
delay(400);

//D3
digitalWrite(ledred, HIGH);
tone(A0, 147, 175);
delay(200);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200);

//F3
digitalWrite(ledgreen, HIGH);
tone(A0, 175, 375);
delay(400);


//////////////////////////////////////////

//GS4
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 415, 375);
delay(400);

//C3
digitalWrite(ledred, HIGH);
tone(A0, 131, 175);
delay(200);

//D3
digitalWrite(ledblue, HIGH);
tone(A0, 147, 175);
delay(200);

//DS3
digitalWrite(ledgreen, HIGH);
tone(A0, 156, 375);
delay(400);

//////////

//GS4
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 415, 375);
delay(400);

//C3
digitalWrite(ledred, HIGH);
tone(A0, 131, 175);
delay(200);

//D3
digitalWrite(ledblue, HIGH);
tone(A0, 147, 175);
delay(200);

//DS3
digitalWrite(ledgreen, HIGH);
tone(A0, 156, 375);
delay(400);


/////////////////////////////////////////

//G4
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 392, 375);
delay(400);

//AS2
digitalWrite(ledred, HIGH);
tone(A0, 117, 175);
delay(200);

//C3
digitalWrite(ledblue, HIGH);
tone(A0, 131, 175);
delay(200);

//D3
digitalWrite(ledgreen, HIGH);
tone(A0, 147, 375);
delay(400);

///////////

//G4
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 392, 375);
delay(400);

//AS2
digitalWrite(ledred, HIGH);
tone(A0, 117, 175);
delay(200);

//C3
digitalWrite(ledblue, HIGH);
tone(A0, 131, 175);
delay(200);

//D3
digitalWrite(ledgreen, HIGH);
tone(A0, 147, 375);
delay(400);


/////////////////////////////////////////

//DS4
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 311, 375);
delay(400);

//G2
digitalWrite(ledred, HIGH);
tone(A0, 98, 175);
delay(200);

//GS2
digitalWrite(ledblue, HIGH);
tone(A0, 104, 175);
delay(200);

//AS2
digitalWrite(ledgreen, HIGH);
tone(A0, 117, 375);
delay(400);

///////////

//DS4
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 311, 375);
delay(400);

//G2
digitalWrite(ledred, HIGH);
tone(A0, 98, 175);
delay(200);

//GS2
digitalWrite(ledblue, HIGH);
tone(A0, 104, 175);
delay(200);

//AS2
digitalWrite(ledgreen, HIGH);
tone(A0, 117, 375);
delay(400);


//////////////////////////////////////////

//DS4
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 311, 775);
delay(800);

//DS4
digitalWrite(ledred, HIGH);
tone(A0, 311, 375);
delay(400);

//D4
digitalWrite(ledred, LOW);
tone(A0, 294, 775);
delay(800);

//D4
digitalWrite(ledblue, HIGH);
tone(A0, 294, 375);
delay(400);

//////////////////////////////////////////

//C4
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 262, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

///////////

//C3
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

/////////////

//C3
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

////////////

//C3
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

///////////////

//C3
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 131, 375);
delay(400);

//DS3
digitalWrite(ledblue, HIGH);
tone(A0, 156, 175);
delay(200); 
  
//F3
digitalWrite(ledred, HIGH);
tone(A0, 175, 175);
delay(200);

//G3
digitalWrite(ledgreen, HIGH);
tone(A0, 196, 375);
delay(400);

////////////////////////////////////////////////

//C3
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
tone(A0, 131, 375);
delay(400);

//DS5
digitalWrite(ledblue, HIGH);
tone(A0, 622, 175);
delay(200); 
  
//F5
digitalWrite(ledred, HIGH);
tone(A0, 698, 175);
delay(200);

//G5
digitalWrite(ledgreen, HIGH);
tone(A0, 784, 375);
delay(400);

/////////////////////////////////////////////////

//C5
digitalWrite(ledgreen, HIGH);
tone(A0, 523, 375);
delay(400);

//DS5
digitalWrite(ledred, LOW);
tone(A0, 622, 175);
delay(200); 
  
//F5
digitalWrite(ledgreen, LOW);
tone(A0, 698, 175);
delay(200);

//G5
digitalWrite(ledblue, LOW);
tone(A0, 784, 375);
delay(400);

/////////////////////////////////////////////////

//C5
digitalWrite(ledgreen, HIGH);
tone(A0, 523, 375);
delay(400);

//DS5
digitalWrite(ledblue, HIGH);
tone(A0, 622, 175);
delay(200); 
  
//F5
digitalWrite(ledred, HIGH);
tone(A0, 698, 175);
delay(200);

//G5
digitalWrite(ledgreen, HIGH);
tone(A0, 784, 375);
delay(400);
// while(brightness > 0)
//   {
//   digitalWrite(ledred, brightness);
//   digitalWrite(ledblue, brightness);
//   digitalWrite(ledgreen, brightness);
//   brightness = brightness - fadeAmount;
//   if (brightness == 0 || brightness == HIGH) {
//     fadeAmount = -fadeAmount ;
//   }
// }
digitalWrite(ledred, LOW);
digitalWrite(ledgreen, LOW);
digitalWrite(ledblue, LOW);
// brightness = HIGH;
// fadeAmount = 5;

delay(3000);

}
void setup(){
  Serial.begin(9600);
  int seed = analogRead(SEED);
  randomSeed(seed);
  startGeniusGame();
  pinMode(A0, OUTPUT);
}
void loop(){
  gameOfThronesIntroSong();
  // Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n");
  // Serial.println("Starting loop");
  // Serial.println("Size of sequence led");
  // Serial.println(sizeSequence);
  // int randomNumber = random(0,4);
  // int ledTemp = ledsAndButtons[randomNumber][0];
  // int buttonTemp = ledsAndButtons[randomNumber][1];
  // int ledButtonTemp[1][2] ;
  // ledButtonTemp[0][0]=ledTemp;
  // ledButtonTemp[0][1]=buttonTemp;
  // increaseSequence(ledButtonTemp, sequenceLeds, sequenceButtons, &sizeSequence);
  // blinkSequence(sequenceLeds, sizeSequence);
  // bool hitSequence = readSequence(ledsAndButtons,sequenceLeds,sequenceButtons,sizeSequence); 
  // if (hitSequence == false){
  //   missedSequence(ledsAndButtons,sequenceLeds, sequenceButtons, &sizeSequence);
  // }

}

