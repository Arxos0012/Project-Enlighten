/*This is a demo for the conversion of an HSV colorspace to
  an rgb one. The math comes from Wikipedia's HSV and HSL Color
  page. This demo smoothly transitions through the color spectrum
  through the change in the hue component of HSV.*/

float h = 0, s = 1, v = 1,  //hsv values for color
      C,                    //chroma
      H,                    //idk
      X,                    //idk :P
      M,                    //irdk -.-
      r, g, b;              //rgb output

long lastTime;

void setup(){
  noStroke();
  size(800, 600);
  lastTime = millis();
}

void draw(){
  if(millis() - lastTime >= 25){
    h = (h+1) % 360;
    
    C = s*v;
    H = h/60.0;
    X = C*(1-abs((H%2)-1));
    
   if(H >= 0 && H < 1){
      r = C;
      g = X;
      b = 0;
    }else if(H >= 1 && H < 2){
      r = X;
      g = C;
      b = 0;
    }else if(H >= 2 && H < 3){
      r = 0;
      g = C;
      b = X;
    }else if(H >= 3 && H < 4){
      r = 0;
      g = X;
      b = C;
    }else if(H >= 4 && H < 5){
      r = X;
      g = 0;
      b = C;
    }else if(H >= 5){
      r = C;
      g = 0;
      b = X;
    }
    
    M = v - C;
    
    r += M;
    g += M;
    b += M;
    
    background((int)(255*r),(int)(255*g),(int)(255*b));
    
    lastTime = millis();
  }
}