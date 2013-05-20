#include "TLedstrip.h"

// ---------------------------------------------------------------------------
TLedStrip::TLedStrip(int num):_num(num) {
  _ledstrip = (PIXEL *)(malloc(num*sizeof(PIXEL)));
}

// ---------------------------------------------------------------------------
void TLedStrip::init() {
  blank();
}

// ---------------------------------------------------------------------------
void TLedStrip::set(int pos, byte *pElement) {

  pos = constrain(pos, 0, _num-1);

  _ledstrip[pos] = *((PIXEL *)(pElement));
}

// ---------------------------------------------------------------------------
void TLedStrip::setRGB(int pos, int r, int g, int b) {

  pos = constrain(pos, 0, _num-1);

  _ledstrip[pos].r = (byte)(constrain(r,0,255));
  _ledstrip[pos].g = (byte)(constrain(g,0,255));
  _ledstrip[pos].b = (byte)(constrain(b,0,255));  
}

// ---------------------------------------------------------------------------
void TLedStrip::setHSV(int pos, int hue, int  sat, int val) 
  {  
  // hue: 0 - 359, saturation: 0 - 255, val (lightness): 0 - 255
    
  if (hue > 359) hue = hue % 359;
  val = constrain(val,0,255);
  sat = constrain(sat,0,255);
   
  if (sat == 0) 
    { 
	// Acromatic color (gray)
    setRGB(pos, val, val, val);
    } 
  else  
    {
	int r, g, b;
    int base   = ((255 - sat) * val) >> 8;
	
    if (hue < 60) {
      r = val;
      g = (((val - base)*hue)/60) + base;
      b = base;
    }
    else if (hue < 120) {
      r = (((val - base)*(60-(hue%60)))/60) + base;
      g = val;
      b = base;
      }
    else if (hue < 180) {
      r = base;
      g = val;
      b = (((val - base)*(hue%60))/60) + base;
    }
    else if (hue < 240) {
      r = base;
      g = (((val - base)*(60 - (hue%60)))/60) + base;
      b = val;
    }
    else if (hue < 300) {
      r = (((val - base)*(hue%60))/60) + base;
      g = base;
      b = val;
    }
    else if (hue < 360) {
      r = val;
      g = base;
      b = (((val - base)*(60 - (hue%60)))/60) + base;
    }
      
    setRGB(pos, r, g, b);
    }
  }

// ---------------------------------------------------------------------------
byte * TLedStrip::get(int pos) {
  pos = constrain(pos, 0, _num-1);
  return (byte *)(&(_ledstrip[pos]));
}

// ---------------------------------------------------------------------------
void TLedStrip::blank() {
  setRGB(0, 0, 0, 0);
  fill(1, _num-1, (byte *)(_ledstrip));
}

// ---------------------------------------------------------------------------
void TLedStrip::white() {
  setRGB(0,255,255,255);
  fill(1, _num-1, (byte *)(_ledstrip));
}

// ---------------------------------------------------------------------------
void TLedStrip::fill(int pos, int length, byte *pLed) {

  // Protect buffer boundaries
  pos    = constrain(pos, 0, _num-1);
  length = constrain(length, 0, _num-pos);
  while(length-- > 0)  _ledstrip[pos++] = *((PIXEL*)(pLed));
}

// ---------------------------------------------------------------------------
void TLedStrip::rotateLeft(int pos, int length) {
  
  // Protect buffer boundaries
  pos    = constrain(pos, 0, _num-1);
  length = constrain(length, 0, _num-pos);

  _ledstrip[pos+length-1] = _ledstrip[pos];  
  shiftLeft(pos, length-1);
}

// ---------------------------------------------------------------------------
void TLedStrip::rotateRight(int pos, int length) {
  
  // Protect buffer boundaries
  pos    = constrain(pos, 0, _num-1);
  length = constrain(length, 0, _num-pos);

  _ledstrip[pos] = _ledstrip[pos+length-1];  
  shiftRight(pos+1, length-1);
}

// ---------------------------------------------------------------------------
void TLedStrip::shiftLeft(int pos, int length) {

  // Protect buffer boundaries
  length = constrain(length, 0, _num-pos)-1;
  pos    = constrain(pos,    0, _num-1);

  while((length--) > 0) {
    _ledstrip[pos] = _ledstrip[pos+1];
    pos++;
  }
}

// ---------------------------------------------------------------------------
void TLedStrip::shiftRight(int pos, int length) {
  
  // Protect buffer boundaries
  length = constrain(length, 0, _num-pos)-1;
  pos    = constrain(pos, 0, _num-1)+length;
  
  while((length--) > 0) {
    _ledstrip[pos] = _ledstrip[pos-1];
    pos--;
  }
}

// ---------------------------------------------------------------------------
void TLedStrip::copy(int posA, int posB, int length) {

  // Protect buffer boundaries
  posA   = constrain(posA, 0, _num-1);
  length = constrain(length, 0, _num-posA);

  if (length <= 0) return;
  posA = constrain(posA,0,_num);
  posB = constrain(posB,0,_num); 
  if (posA+length > _num) length = _num-posA;
  if (posB+length > _num) length = _num-posB;  

  if(posA > posB) {
    for(int i = posA, j = posB; i < posA+length; i++, j++) {
      _ledstrip[j] = _ledstrip[i]; 
    }
  }
  if(posB > posA) {
    for(int i = posA+length-1, j = posB+length-1; i >= posA; i--, j--) {
      _ledstrip[j] = _ledstrip[i]; 
    } 
  }
}

// ---------------------------------------------------------------------------
void TLedStrip::mirror(int posA, int posB, int length) {

  if(posA > posB) {
    for(int a = posA, b = posB+length-1; a < posA+length-1; a++, b--) {
      _ledstrip[b] = _ledstrip[a];
    }
  }
  if(posB > posA) {
    for(int a = posA+length-1, b = posB; a >= posA; a--, b++) {
      _ledstrip[b] = _ledstrip[a];
    }
  }  
}

// ---------------------------------------------------------------------------
byte TLedStrip::filter(byte current, byte target, int coeff) {
  
  int diff   = target - current;
  int delta  = diff / coeff;
  int result = current + delta;

  if (delta == 0) result = target;
    
  return constrain(result, 0, 255);
}

// ---------------------------------------------------------------------------
void TLedStrip::filter(byte *pTarget, byte *pRef, int coeff) {

  ((PIXEL *)(pTarget))->r = filter(((PIXEL *)(pTarget))->r, ((PIXEL *)(pRef))->r, coeff);
  ((PIXEL *)(pTarget))->g = filter(((PIXEL *)(pTarget))->g, ((PIXEL *)(pRef))->g, coeff);
  ((PIXEL *)(pTarget))->b = filter(((PIXEL *)(pTarget))->b, ((PIXEL *)(pRef))->b, coeff); 
}

// ---------------------------------------------------------------------------
void TLedStrip::filter(int pos, int length, int coeff, byte *pRGB) {
  
  for(int i=pos; i < pos+length; i++) filter( get(i), pRGB, coeff);
}

