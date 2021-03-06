#include <math.h>

enum Dials{
 H_DIAL = 0,
 S_DIAL,
 V_DIAL,
};

const int R_LIGHT = 3,
          G_LIGHT = 5,
          B_LIGHT = 6;

float chroma, hueP, X, matchVal;

float lastHSV[3], HSV[3], RGB[3];

const bool VERBOSE_RGB = true,
           VERBOSE_HSV = false;

void setup() {
  pinMode(R_LIGHT, OUTPUT);
  pinMode(G_LIGHT, OUTPUT);
  pinMode(B_LIGHT, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(dialsChanged()) updateRGB();
  
  if(VERBOSE_RGB){
    Serial.print(RGB[0]);
    Serial.print(", ");
    Serial.print(RGB[1]);
    Serial.print(", ");
    Serial.println(RGB[2]);
  }
  if(VERBOSE_HSV){
    Serial.print(HSV[0]);
    Serial.print(", ");
    Serial.print(HSV[1]);
    Serial.print(", ");
    Serial.println(HSV[2]);
  }
}

bool dialsChanged(){
  for(int i=0; i<3; i++) lastHSV[i] = HSV[i];
    
  HSV[0] = 360.0 * (analogRead(H_DIAL)/1023.0);
  HSV[1] = analogRead(S_DIAL)/1023.0;
  HSV[2] = analogRead(V_DIAL)/1023.0;
  
  for(int i=0; i<3; i++) if(lastHSV[i] != HSV[i]) return true;
  return false;
}

void updateRGB(){
  chroma = HSV[1] * HSV[2];
  hueP = HSV[0]/60.0;
  X = chroma*(1-abs(fmod(hueP,2)-1));
  
  if(hueP >= 0 && hueP < 1){
    RGB[0] = chroma;
    RGB[1] = X;
    RGB[2] = 0;
  }else if(hueP >= 1 && hueP < 2){
    RGB[0] = X;
    RGB[1] = chroma;
    RGB[2] = 0;
  }else if(hueP >= 2 && hueP < 3){
    RGB[0] = 0;
    RGB[1] = chroma;
    RGB[2] = X;
  }else if(hueP >= 3 && hueP < 4){
    RGB[0] = 0;
    RGB[1] = X;
    RGB[2] = chroma;
  }else if(hueP >= 4 && hueP < 5){
    RGB[0] = X;
    RGB[1] = 0;
    RGB[2] = chroma;
  }else if(hueP >= 5){
    RGB[0] = chroma;
    RGB[1] = 0;
    RGB[2] = X;
  }

  matchVal = HSV[2] - chroma;

  RGB[0] += matchVal;
  RGB[1] += matchVal;
  RGB[2] += matchVal;
  
  analogWrite(R_LIGHT, (int)(RGB[0]*255));
  analogWrite(G_LIGHT, (int)(RGB[1]*255));
  analogWrite(B_LIGHT, (int)(RGB[2]*255));
}
