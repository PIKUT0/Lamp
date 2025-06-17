//------------------DEFINE------------------//
#define BUTT 3
#define Charge 7
#define LEDO 21
#define LED_SH 9
//----------Define our type
enum systemd{
  LED_NF, 
  CHARGE_NF,
  Blink
};

//-------- Useful variables
systemd currency = LED_NF;
bool inCharge = false;
bool ledState = false;
bool inBlink  = false;
bool Jacky    = false;
bool BRU      = true;
//bool Station  = false;
bool buttonActive = false; 
uint8_t blinkBrightness = 0;
uint32_t btnPress, myTimer, fakeTimer = 0;


//-----SETUP-----//
void setup(){
  pinMode(Charge, OUTPUT);
  pinMode(BUTT, INPUT);
  pinMode(LED_SH, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(Charge, LOW);
  digitalWrite(LED_SH, LOW); 
  digitalWrite(LED_BUILTIN, LOW);
}

//-----FUNCTIONS-----//
void TouchYourButt(){
  digitalWrite(LED_BUILTIN, LOW);
  if(digitalRead(BUTT) == HIGH){
    if (!buttonActive){
      buttonActive = true;
      btnPress = millis();
      myTimer = millis();
    }
    if (millis() - myTimer >= 1500){
      Jacky = !Jacky;
    }
    if (millis() - btnPress >= 3000){
      Jacky = !Jacky;
      LongDick();
      buttonActive = false;
    }
  }
  else {
    fakeTimer = millis();
    if (buttonActive){
      if(!Jacky) currency = LED_NF;
      if(Jacky) currency = CHARGE_NF;
      ShortClick();
      buttonActive = false;  
    }
  }
}

void ShortClick()
{
  if (inBlink) return;

  switch(currency){
    case LED_NF:
      ledState = !ledState;
      break;
    case CHARGE_NF:
      inCharge = !inCharge;
      break;
  }
}


void LongDick()
{
  inBlink = !inBlink;
  if(inBlink){
    currency = Blink;
    blinkBrightness = 0;
    BRU = true;
  }
  else{
    currency = LED_NF;
    ledState = (blinkBrightness > 127);
  }
}

void BlinkMode()
{
  while(digitalRead(BUTT) == LOW){ 
    if(millis() - fakeTimer > 50){
      fakeTimer = millis();
      if(BRU){
        blinkBrightness++;
        if (blinkBrightness >= 255){
          blinkBrightness = 255;
          BRU = false;
        }
      }
      else{
        blinkBrightness--;
        if (blinkBrightness <= 0){
          blinkBrightness = 0;
          BRU = true;
        }
      }
    }
    analogWrite(LED_SH, blinkBrightness);
  } 
}
//----LOOP----//
void loop(){
  // BASE analogWrite(9, 255);
 /* while(!Station){
    digitalWrite(LED_BUILTIN, HIGH);
    Station = digitalRead(BUTT);
    fakeTimer = millis();
  }*/
  TouchYourButt();
  switch(currency){
    case LED_NF:
      digitalWrite(LED_SH,ledState);
      break;
    case CHARGE_NF:
      digitalWrite(Charge, inCharge);
      break;
    case Blink:
      BlinkMode();
      break;
  }
}
 
