#include <Otto9.h> 

class CustomOtto: public Otto9 {
    public:
      void hello();
      void randomDancing(bool withSound = false, int speed = 400);
      void crazyDance(int count = 16);
      void horizontMove(int count = 6, int left = 80, int right = 100, int speed = 100, int defaultLeft = 90, int defaultRight = 90);
      void moveFoot(int leg = 3, int value = 90, int speed = 100, int leg1 = 3, int value1 = 90, bool drigdrig = false);
      void michaelJacksonDance();
      void michaelJacksonDanceFirstScene(int count = 3);
      void michaelJacksonDanceSecondScene(int count = 6);
      void readEspMessage(int &refMoveID);
      void readConsoleMessage(int &refMoveID);
      void initESP(uint32_t baud = 115200);
};