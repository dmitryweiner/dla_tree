#include <S65Display.h> 

#define MAX_ARRAY_LENGTH 1700

S65Display lcd;
  
//neighbor pixel directions
byte nx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
byte ny[] = {0, 1, 1, 1, 0, -1, -1, -1};
byte screen [ MAX_ARRAY_LENGTH ];
int currentArrayLength = 0;

boolean isOnScreen(int x, int y) {
  for (int i = 0; i < currentArrayLength; i++ ) {
    if (screen[i*2] == x && screen[i*2+1] == y) {
      return true;
    }
  }
  return false;
} 

boolean setOnScreen(int x, int y) {
  if (currentArrayLength >= (MAX_ARRAY_LENGTH/2)) {
    return false;
  }
  if (!isOnScreen(x, y)){
    screen[currentArrayLength*2]   = x;
    screen[currentArrayLength*2+1] = y;
    currentArrayLength++;
  }
  return true;
}

boolean clearMemory() {
  for (int i = 0; i < MAX_ARRAY_LENGTH; i++) {
    screen[i] = 0;
  }
  currentArrayLength = 0;
  return true;
}

void setup() 
{ 
  lcd.init(2); 
  randomSeed(analogRead(0));
} 
  

void loop(){ 
    
    while (true) {
      beginOfLoop:
      byte x, y;
      byte xc, yc;
      byte xn, yn;
      int maxIt = 50;
      int rmax;
      float a;
      boolean outOfMemoryFlag = false;
      float rm = 1.0;

      xc = (S65_WIDTH - 1) / 2;
      yc = (S65_HEIGHT - 1) / 2;
      rmax = min(xc, yc) - 1;
      lcd.clear(0); 
      clearMemory();
      if (setOnScreen(xc, yc)) {
        lcd.drawPixel(xc, yc, RGB(255, 255, 255));
      }
      while (rm < rmax) {
        boolean flag = false;
        a = 3.14159265 * 2 * random(0, 100)/100;
        x = xc + rm * cos(a);
        y = yc + rm * sin(a);
        for (int i = 0; i < maxIt; i++){
          byte rand = random(0, 8);
          x = x + nx[rand];
          y = y + ny[rand];
          if (x < 0 || x > (S65_WIDTH - 1) || y < 0 || y > (S65_HEIGHT - 1)) {
            break;
          }
          if (!isOnScreen(x, y)){
              //check the neighbors
              for (byte k = 0; k < 8; k++){
                  xn = x + nx[k];
                  yn = y + ny[k];
                  if (isOnScreen(xn, yn)) {
                      if (setOnScreen(x, y)) {
                        lcd.drawPixel(x, y, RGB(255, 255, 255));
                      } else {
                        goto beginOfLoop;
                      }
                      float r;
                      r = sqrt((x - xc) * (x - xc) + (y - yc) * (y - yc));
                      if (r > rm) {
                          rm = r;
                      }
                      flag = true;
                      break;
                  }
              }
          }//if not on screen
          if (flag) {
            break;
          }
        }//for
      }//while(r<rmax)
   }//while(true)
}
