#include "CustomOtto.h"
#include <SoftwareSerial.h>

SoftwareSerial esp8266(11,12);

// ESP variables
int length = 2;
char buffer [2];
char termChar = '\n';

///////////////////////////////////////////////////////////////////
//-- ESP start  -------------------------------------------------//
///////////////////////////////////////////////////////////////////
void CustomOtto::initESP(uint32_t baud = 115200) {
    esp8266.begin(baud);
}

///////////////////////////////////////////////////////////////////
//-- Read Function  ---------------------------------------------//
///////////////////////////////////////////////////////////////////
void CustomOtto::readConsoleMessage(int &refMoveID) {
  if (Serial.available() > 0) {
      home();

      String message = Serial.readString();
      Serial.println(message);
      int num = atoi(message.begin());

      refMoveID = num;
  }
}

void CustomOtto::readEspMessage(int &refMoveID) {
  // читает сообщения от есп
  if(esp8266.available() > 0 ) {
     int numChars = esp8266.readBytesUntil(termChar, buffer, length);
     buffer[numChars]='\0';

    // получаем символ
    refMoveID = atoi(buffer);;
    
    Serial.println(refMoveID);
  }
}

///////////////////////////////////////////////////////////////////
//-- Otto custom movement  --------------------------------------//
///////////////////////////////////////////////////////////////////
void CustomOtto::hello() {
    home();
    int T2=800; 
    int start = 0;
    int d = 0;

    for (int i = 0; i < 8; i++) {
        d = 90 - start;
        int bend[4]={90, 90, 0, d};

        _moveServos(T2/2, bend);
        start += 10;
    }

    for (int i = 0; i < 6; i++) {
        int bend[4]={90, 90, 90, d};
        if (i % 2 == 0) {
            bend[2] = 5;
        } else {
            bend[2] = 170;
        }

        _moveServos(T2/2, bend);
    }

  home();
}

void CustomOtto::crazyDance(int count = 16){
    home();
    int T2=800; 

    for (int i = 0; i < count; i++) {
        int bend[4]={90, 90, 90, 90};
        if (i % 2 == 0) {
            bend[0] = 5;
            bend[3] = 5;
        } else {
            bend[0] = 170;
            bend[3] = 170;
        }

        _moveServos(T2/2, bend);
    }
    home();
}

void CustomOtto::horizontMove(int count = 6, int left = 80, int right = 100, int speed = 100, int defaultLeft = 90, int defaultRight = 90){
    for (int i = 0; i < count; i++) {
      int bend[4]={90, 90, defaultLeft, defaultRight};

      if (i % 2 == 0) {
          bend[0] = left;
          bend[1] = right;
      } else {
          bend[0] = right;
          bend[1] = left;
      }

      _moveServos(speed, bend);
    }

    home();    
}

void CustomOtto::moveFoot(int leg = 3, int value = 90, int speed = 100, int leg1 = 3, int value1 = 90, bool drigdrig = false){
    int state[4]={90, 90, 90, 90};

    state[leg] = value;

    _moveServos(speed, state);

    int home[4] = {90, 90, 90, 90};

    home[leg1] = value1;

    _moveServos(speed, home);

    if (value1 != 90) {
      int toHome[4] = {90,90,90,90};
      _moveServos(speed, toHome);
    }
}

///////////////////////////////////////////////////////////////////
//-- Otto custom dance  -----------------------------------------//
///////////////////////////////////////////////////////////////////
void CustomOtto::randomDancing(bool withSound = false, int speed = 400) {
    char voices[9] = {S_happy_short, S_OhOoh2,S_OhOoh, S_surprise, S_superHappy,S_happy, S_fart1,S_fart2,S_fart3};
    home();

    int bend[4]={random(70, 110), random(70, 110), random(5, 170), random(5, 170)};

    _moveServos(400, bend);

    if (withSound) {
        sing(voices[random(1, 14)]);
    }

    home();
}

void CustomOtto::michaelJacksonDance() {
    int T=1000;              //Initial duration of movement

    michaelJacksonDanceFirstScene(3);
    walk(1,T,-1);

    michaelJacksonDanceSecondScene(10);

    jump(1,T);

    for (int i = 0; i < 10; i++) {
        moveFoot(2, 30, 700, 3, 160);
        delay(100);
        horizontMove(4, 90, 75, 50);
    }

    delay(200);

    crazyDance(10);

    home();
}

void CustomOtto::michaelJacksonDanceFirstScene(int count = 3) {
    for (int i = 0; i < count; i++) {
    moveFoot(2, 50, 100);
    delay(100);
    moveFoot(2, 80, 100);
    delay(400);
  }
  for (int i = 0; i < count; i++) {
    moveFoot(2, 70, 100);
    moveFoot(3, 120, 100);
    moveFoot(2, 70, 100);

    delay(200);

    horizontMove(1, 80, 100);

    delay(200);

    moveFoot(2, 50, 100);
    moveFoot(3, 120, 100);
    moveFoot(2, 80, 100);

    delay(100);

    horizontMove(3, 80, 100);

    delay(200);
  }

  for (int i = 0; i < 2; i++) {
    moveFoot(2, 40, 100);
    moveFoot(3, 140, 100);
    moveFoot(2, 60, 100);

    delay(100);

    horizontMove(2, 70, 110);

    delay(200);
  }
}

void CustomOtto::michaelJacksonDanceSecondScene(int count = 6) {
    for (int i = 0; i < count; i++) {
      moveFoot(2, 60, 100);
      moveFoot(3, 130, 100);

      delay(200);

      horizontMove(6, 105, 75, 50);

      delay(100);
    }
}