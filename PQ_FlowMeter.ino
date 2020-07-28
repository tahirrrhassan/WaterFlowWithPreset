#include <EEPROM.h>
#include <TimerOne.h>

#define sensorPin 2
#define A 0 
#define B 1
#define C 3
#define D 4
#define E 5
#define F 6
#define G 7

#define out 19

#define p1 9 //PROCESS VALUE L
#define p2 8
#define p3 14
#define p4 15 //PROCESS VALUE R

#define s1 13 //SET POINT L
#define s2 12
#define s3 11
#define s4 10 //SET POINT R

#define up 16
#define shift 17
#define set 18

String final;
// The hall-effect flow sensor outputs approximately 4.5 pulses per second per
float calibrationFactor = 7.5; //450 pulses / 60 sec

volatile unsigned int pulseCount=0, count=0;  

float flow = 0.0;
int pVal = 0;
int sVal = 0;
int d=0,e=0,f=0,g=0;
unsigned long oldTime = 0;
int p=0,w,x,y,z;
int dd = 400;
int prgc=0;
boolean program=0, eeprom=0, a=0,b1=0,b2=0,b3=0,c=0,on=0;

void digit(int x){
  switch(x){
    case 0:
      digitalWrite(A,1);digitalWrite(B,1);digitalWrite(C,1);digitalWrite(D,1);digitalWrite(E,1);digitalWrite(F,1);digitalWrite(G,0);
      break;
    case 1:
      digitalWrite(A,0);digitalWrite(B,1);digitalWrite(C,1);digitalWrite(D,0);digitalWrite(E,0);digitalWrite(F,0);digitalWrite(G,0);
      break;
    case 2:
      digitalWrite(A,1);digitalWrite(B,1);digitalWrite(C,0);digitalWrite(D,1);digitalWrite(E,1);digitalWrite(F,0);digitalWrite(G,1);
      break;
    case 3:
      digitalWrite(A,1);digitalWrite(B,1);digitalWrite(C,1);digitalWrite(D,1);digitalWrite(E,0);digitalWrite(F,0);digitalWrite(G,1);
      break;
    case 4:
      digitalWrite(A,0);digitalWrite(B,1);digitalWrite(C,1);digitalWrite(D,0);digitalWrite(E,0);digitalWrite(F,1);digitalWrite(G,1);
      break;
    case 5:
      digitalWrite(A,1);digitalWrite(B,0);digitalWrite(C,1);digitalWrite(D,1);digitalWrite(E,0);digitalWrite(F,1);digitalWrite(G,1);
      break;
    case 6:
      digitalWrite(A,1);digitalWrite(B,0);digitalWrite(C,1);digitalWrite(D,1);digitalWrite(E,1);digitalWrite(F,1);digitalWrite(G,1);
      break;
    case 7:
      digitalWrite(A,1);digitalWrite(B,1);digitalWrite(C,1);digitalWrite(D,0);digitalWrite(E,0);digitalWrite(F,0);digitalWrite(G,0);
      break;
    case 8:
      digitalWrite(A,1);digitalWrite(B,1);digitalWrite(C,1);digitalWrite(D,1);digitalWrite(E,1);digitalWrite(F,1);digitalWrite(G,1);
      break;
    case 9:
      digitalWrite(A,1);digitalWrite(B,1);digitalWrite(C,1);digitalWrite(D,1);digitalWrite(E,0);digitalWrite(F,1);digitalWrite(G,1);
      break;
    default:
      digitalWrite(A,0);digitalWrite(B,0);digitalWrite(C,0);digitalWrite(D,0);digitalWrite(E,0);digitalWrite(F,0);digitalWrite(G,0);
      break; 
  }
}
void Update(){
  switch(prgc){
    case 0:
      digit(pVal/1000);
      digitalWrite(p1, 0);
      delayMicroseconds(dd);
      digitalWrite(p1, 1);
      if(!program){
        digit(sVal/1000);
        digitalWrite(s1, 0);
        delayMicroseconds(dd);
        digitalWrite(s1, 1);
      } else {
        if(p==3){
          if(count>=10){
            a=!a;
            count=0;
          } else count++;
          
          if(a){
            digit(sVal/1000);
            digitalWrite(s1, 0);
            delayMicroseconds(dd);
            digitalWrite(s1, 1);
          } else {
            digit(10);
            digitalWrite(s1, 0);
            delayMicroseconds(dd);
            digitalWrite(s1, 1);
          }
        } else{
          digit(sVal/1000);
          digitalWrite(s1, 0);
          delayMicroseconds(dd);
          digitalWrite(s1, 1);
        }
      }
      break;
    case 1:
      digit((pVal/100)%10);
      digitalWrite(p2, 0);
      delayMicroseconds(dd);
      digitalWrite(p2, 1);
      if(!program){
        digit((sVal/100)%10);
        digitalWrite(s2, 0);
        delayMicroseconds(dd);
        digitalWrite(s2, 1);
      } else {
        if(p==2){
          if(count>=10){
            a=!a;
            count=0;
          } else count++;
          
          if(a){
            digit((sVal/100)%10);
            digitalWrite(s2, 0);
            delayMicroseconds(dd);
            digitalWrite(s2, 1);
          } else {
            digit(10);
            digitalWrite(s2, 0);
            delayMicroseconds(dd);
            digitalWrite(s2, 1);
          }
        } else{
          digit((sVal/100)%10);
          digitalWrite(s2, 0);
          delayMicroseconds(dd);
          digitalWrite(s2, 1);
        }
      }
      break;
    case 2:
      digit((pVal/10)%10);
      digitalWrite(p3, 0);
      delayMicroseconds(dd);
      digitalWrite(p3, 1);
      if(!program){
        digit((sVal/10)%10);
        digitalWrite(s3, 0);
        delayMicroseconds(dd);
        digitalWrite(s3, 1);
      } else {
        if(p==1){
          if(count>=10){
            a=!a;
            count=0;
          } else count++;
          
          if(a){
            digit((sVal/10)%10);
            digitalWrite(s3, 0);
            delayMicroseconds(dd);
            digitalWrite(s3, 1);
          } else {
            digit(10);
            digitalWrite(s3, 0);
            delayMicroseconds(dd);
            digitalWrite(s3, 1);
          }
        } else{
          digit((sVal/10)%10);
          digitalWrite(s3, 0);
          delayMicroseconds(dd);
          digitalWrite(s3, 1);
        }
      }
      break;
    case 3:
      digit(pVal%10);
      digitalWrite(p4, 0);
      delayMicroseconds(dd);
      digitalWrite(p4, 1);
      if(!program){
        digit(sVal%10);
        digitalWrite(s4, 0);
        delayMicroseconds(dd);
        digitalWrite(s4, 1);
      } else {
        if(p==0){
          if(count>=10){
            a=!a;
            count=0;
          } else count++;
          
          if(a){
            digit(sVal%10);
            digitalWrite(s4, 0);
            delayMicroseconds(dd);
            digitalWrite(s4, 1);
          } else {
            digit(10);
            digitalWrite(s4, 0);
            delayMicroseconds(dd);
            digitalWrite(s4, 1);
          }
        } else{
          digit(sVal%10);
          digitalWrite(s4, 0);
          delayMicroseconds(dd);
          digitalWrite(s4, 1);
        }
      }
      break;
  }
}

void Display(){
  if(!digitalRead(set)){
    if(!b1){
      program=!program;
      b1=1;
    }
  } else b1=0;
  
  MAIN();
  Update();
  prgc++;
  if(prgc==4) prgc=0;
}

void Delay(unsigned int delaytime){
  while(d<=delaytime){
    d++;
  }
  d=0;
}


void Flow(){
  flow = (pulseCount) / calibrationFactor;
  //oldTime = millis();
  flow = (flow * 0.767); //FOR LpM
  pVal = flow;
  pulseCount = 0;
  attachInterrupt(0, pulseCounter, FALLING);
}

void MAIN(){
  if(f>=200){ //200 = 1S
    detachInterrupt(0);
    f=0;
    on=1;//Flow();
  } else f++;
  if(program){
     if(!digitalRead(shift)){
      if(!b2){
        b2=1;
        if(p==3) p=0; //3-2-1-0
        else p++;
      }
    } else b2=0;
    if(!c){
      if(!digitalRead(up)){
        eeprom=1;
        w = sVal/1000;    
        x = (sVal/100)%10;
        y = (sVal/10)%10;
        z = sVal%10;
        switch(p){
          case 0:
            if (z>=9) z=0;
            else z++;
            break;
          case 1:
            if (y>=9) y=0;
            else y++;
            break;
          case 2:
            if (x>=9) x=0;
            else x++;
            break;
          case 3:
            if (w>=9) w=0;
            else w++;
            break;
        }
        sVal = w*1000;
        sVal += x*100;
        sVal += y*10;
        sVal += z;
        c=1;
      }
    } else{
      if(e>=30){ //30
        e=0;
        c=0;
      } else e++;
    }
  }
}

void setup(){  
  pinMode(sensorPin, INPUT_PULLUP);
  pinMode(up, INPUT_PULLUP);
  pinMode(shift, INPUT_PULLUP);
  pinMode(set, INPUT_PULLUP);
  pinMode(out, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);
  pinMode(p4, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(s4, OUTPUT);

  for(int i=8; i<=15; i++) digitalWrite(i, 1);
  if(EEPROM.read(24)>99){
    EEPROM.write(24, 0);
    EEPROM.write(25, 0);
    sVal=0;
  }
  if(EEPROM.read(25)>99){
    EEPROM.write(24, 0);
    EEPROM.write(25, 0);
    sVal=0;
  }
  sVal = (EEPROM.read(24))*100;
  sVal += EEPROM.read(25);
  Timer1.initialize(5000); //0.005 Seconds
  Timer1.attachInterrupt(Display);
  attachInterrupt(0, pulseCounter, FALLING);
}

void loop(){  
  //MAIN();
  if(on){
    on=0;
    Flow();
    //sVal++;
  }
  if(eeprom){
    if(!program){
      EEPROM.update(24, sVal/100);
      EEPROM.update(25, sVal%100);
      eeprom=0;
      Delay(10);
    }
  }
  if(pVal < sVal){
    if(g>=100){
      digitalWrite(out, 1);
      g=0;
    } else g++;
  }
  else{
    digitalWrite(out, 0);
    g=0;
  }
  
}

void pulseCounter(){
  pulseCount++;
}
