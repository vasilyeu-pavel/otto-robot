#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>

#include <customOtto/CustomOtto.h>
CustomOtto Otto;  //This is Otto!

/*
         --------------- 
        |     O   O     |
        |---------------|
YR 3==> |               | <== YL 2
         --------------- 
            ||     ||
            ||     ||
RR 5==>   -----   ------  <== RL 4
         |-----   ------|
*/

#define PIN_YL 3 
#define PIN_YR 2 
#define PIN_RR 4
#define PIN_RL 5 
#define PIN_Trigger  8  //TRIGGER pin (8)
#define PIN_Echo     9  //ECHO pin (9)
// BUZZER PIN //////////////////////////////////////////////////////////////////////////////
#define PIN_Buzzer A3 //BUZZER pin (13)
// SOUND SENSOR PIN //////////////////////////////////////////////////////////////////////////
#define PIN_NoiseSensor A6  //SOUND SENSOR   ANALOG pin (A6)

// declare move func
void move(int *pMoveID);

///////////////////////////////////////////////////////////////////
//-- Global Variables -------------------------------------------//
///////////////////////////////////////////////////////////////////

//-- Movement parameters
int T=1000;              //Initial duration of movement

int moveSize=15;         //Asociated with the height of some movements

int moveID = 0;          //Move variables

///////////////////////////////////////////////////////////////////
//-- Setup ------------------------------------------------------//
///////////////////////////////////////////////////////////////////
void setup(){
  uint32_t baud = 115200;

  // Serial communication initialization
  Serial.begin(baud);  
  Otto.initESP(baud);
  
  // Set the servo pins
  Otto.init(PIN_YL, PIN_YR, PIN_RL, PIN_RR, true, PIN_NoiseSensor, PIN_Buzzer, PIN_Trigger, PIN_Echo);
  // Otto.init(PIN_YL, PIN_YR, PIN_RL, PIN_RR, true);

  // Set a random seed
  randomSeed(analogRead(A6));

  Otto.home();

  Otto.sing(S_connection);

  delay(50);
}
///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
///////////////////////////////////////////////////////////////////
void loop() {
  Otto.readEspMessage(moveID);
  Otto.readConsoleMessage(moveID);

  move(&moveID);
}

///////////////////////////////////////////////////////////////////
//-- Function  --------------------------------------------------//
///////////////////////////////////////////////////////////////////
// -- Function to execute the right movement according the movement command received.
void move(int *pMoveID) {
  switch (*pMoveID) {
    // simple movements //////////////////////////////////////////////////////////////////////////
    case 0:
      Otto.home();
      break;
    case 1: //M 1 1000 
      Otto.walk(1,300,1);
      break;
    case 2: //M 2 1000 
      Otto.walk(1,T,-1);
      break;
    case 3: //M 3 1000 
      Otto.turn(1,T,1);
      break;
    case 4: //M 4 1000 
      Otto.turn(1,T,-1);
      break;
    //  grouped movements ////////////////////////////////////////////////////////////////////////
    case 5: //M 5 1000 30 
      Otto.updown(1,T,moveSize);
      break;
    case 6: //M 6 1000 30
      Otto.moonwalker(1,T,moveSize,1);
      break;
    case 7: //M 7 1000 30
      Otto.moonwalker(1,T,moveSize,-1);
      break;
    case 8: //M 8 1000 30
      Otto.swing(1,T,moveSize);
      break;
    case 9: //M 9 1000 30 
      Otto.crusaito(1,T,moveSize,1);
      break;
    case 10: //M 10 1000 30 
      Otto.crusaito(1,T,moveSize,-1);
      break;
    case 11: //M 11 1000 
      Otto.jump(1,T);
      break;
    case 12: //M 12 1000 30 
      Otto.flapping(1,T,moveSize,1);
      break;
    case 13: //M 13 1000 30
      Otto.flapping(1,T,moveSize,-1);
      break;
    case 14: //M 14 1000 20
      Otto.tiptoeSwing(1,T,moveSize);
      break;
    case 15: //M 15 500 
      Otto.bend(1,T,1);
      break;
    case 16: //M 16 500 
      Otto.bend(1,T,-1);
      break;
    case 17: //M 17 500 
      Otto.shakeLeg(1,T,1);
      break;
    case 18: //M 18 500 
      Otto.shakeLeg(1,T,-1);
      break;
    case 19: //M 19 500 20
      Otto.jitter(1,T,moveSize);
      break;
    case 20: //M 20 500 15
      Otto.ascendingTurn(1,T,moveSize);
      break;
    case 21: //M 20 500 15
      Otto.shakeLeg(1,T,1);
      break;
    case 25: 
      Otto.hello();
      moveID = 0;
      break;
   //  dancing  //////////////////////////////////////////////////////////////////////////
    case 22: 
      Otto.randomDancing();
      break;
    case 23: 
      Otto.randomDancing(true);
      break;
    case 24: 
      Otto.crazyDance();
      break;
    case 26: 
      Otto.michaelJacksonDance();
      moveID = 0;
      break;
    //  sounds  //////////////////////////////////////////////////////////////////////////
    case 30: 
      Otto.sing(S_sad);
      moveID = 0;
      break;
    case 31: 
      Otto.sing(S_buttonPushed);
      moveID = 0;
      break;
    case 32: 
      Otto.sing(S_confused);
      moveID = 0;
      break;
    case 33: 
      Otto.sing(S_cuddly);
      moveID = 0;
      break;
    case 34: 
      Otto.sing(S_disconnection);
      moveID = 0;
      break;
    case 35: 
      Otto.sing(S_fart3);
      moveID = 0;
      break;
    case 36: 
      Otto.sing(S_happy);
      moveID = 0;
      break;
    case 37: 
      Otto.sing(S_happy_short);
      moveID = 0;
      break;
    case 38: 
      Otto.sing(S_OhOoh);
      moveID = 0;
      break;
    case 39: 
      Otto.sing(S_sleeping);
      moveID = 0;
      break;
    case 40: 
      Otto.sing(S_superHappy);
      moveID = 0;
      break;
    //  other movements  ////////////////////////////////////////////////////////////////////////
    case 41: 
      // run forward
      Otto.walk(1,300,1);
      break;
    case 42: 
      // run back
      Otto.walk(1,300,-1);
      break;
    case 43:
      Otto.turn(1,300,1);
      break;
    case 44:
      Otto.turn(1,300,-1);
      break;
   //  random dancing  ////////////////////////////////////////////////////////////////////////
   //  receive bit rate from music by websocket [type int]from 1 to 9 /////////////////////////
    case 50:
      Otto.randomDancing(false, 1000);
      break;
    case 51:
      Otto.randomDancing(false, 900);
      break;
    case 52:
      Otto.randomDancing(false, 800);
      break;
    case 53:
      Otto.randomDancing(false, 700);
      break;
    case 54:
      Otto.randomDancing(false, 600);
      break;
    case 55:
      Otto.randomDancing(false, 500);
      break;
    case 56:
      Otto.randomDancing(false, 400);
      break;
    case 57:
      Otto.randomDancing(false, 300);
      break;
    case 58:
      Otto.randomDancing(false, 200);
      break;
    case 59:
      Otto.randomDancing(false, 100);
      break;        
    default:
      break;
  }
}