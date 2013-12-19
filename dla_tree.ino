#include <S65Display.h> 

S65Display lcd;
  
//neighbor pixel directions
byte nx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
byte ny[] = {0, 1, 1, 1, 0, -1, -1, -1};
byte screen[S65_WIDTH][S65_HEIGHT/8];
void setup() 
{ 
  lcd.init(2); 
  lcd.clear(0); 
  randomSeed(analogRead(0));
} 
  

void loop(){ 
    byte x, y;
    int steps;
    bool flag;
    byte a;
    //# start random walk
    x = S65_WIDTH / 2;
    y = S65_HEIGHT / 2;
    steps = 0;
    flag = false;
    while (true) {
        if (screen[x][y] == 0) {
          //check the neighbors
          for (byte k=0; k<7; k++){
            byte xn, yn;
            xn = x + nx[k];
            yn = y + ny[k];
            if (xn < 0 || xn > (S65_WIDTH - 1) || yn < 0 || yn > (S65_HEIGHT - 1)){
              lcd.drawPixel(x, y, RGB(255, 255, 255));
              screen[x][y] = 255;
              flag = true;
              break;
            }
            if (screen[xn][yn] > 0){
              screen[x][y] = 255;
              flag = true;
              break;
            }
          }
        }
        if (flag == true){
            break;
        }
        a = random(0, 7);
        x = x + nx[a];
        y = y + ny[a];
        steps += 1;
    }
    if (steps < 2) {
      lcd.clear(0); 
    }
}
