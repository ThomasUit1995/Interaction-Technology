#include <LiquidCrystal.h>

LiquidCrystal lcd(0,1,2,3,4,5);

const int buttonPin = 13;
const int ledR = 9;
const int ledG = 10;
const int ledB = 11; 

const int BUTTON1 = 1;
const int BUTTON2 = 2;

const int BUTTON1LOW = 750; //left button
const int BUTTON1HIGH = 890;
const int BUTTON2LOW = 900; //right button
const int BUTTON2HIGH = 1100;

int buttonState;
int lastButtonState;
int choice = 0;
int counter = 0;

int brightnessR = LOW;
int brightnessG = LOW;
int brightnessB = LOW;

long lastDebounceTime = 0;
long debounceDelay = 50;

void setup(){
  pinMode(buttonPin, INPUT);
  //lcd.begin(16,2);
  //state0();
  Serial.begin(9600);
}

void loop(){
  //analogWrite(ledR, brightnessR);
  //analogWrite(ledG, brightnessG);
  //analogWrite(ledB, brightnessB);

  int reading = analogRead(buttonPin);

  Serial.println(reading);
/*
  
  int tmpButtonState = LOW;
  
  if(reading>BUTTON2LOW && reading<BUTTON2HIGH){
    //Read switch 2
    tmpButtonState = BUTTON2;
  }else if(reading>BUTTON1LOW && reading<BUTTON1HIGH){
    //Read switch 1
    tmpButtonState = BUTTON1;
  }else{
    tmpButtonState = LOW;
  }
  
  // check to see if you just pressed the button 
  // (i.e. the input went from LOW to a buttonState),  and you've waited 
  // long enough since the last press to ignore any noise:  

  // If the switch changed, due to noise or pressing:
  if (tmpButtonState != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
    if (tmpButtonState == BUTTON2){
      counter = counter + 1; 
    }
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    buttonState = tmpButtonState;
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = tmpButtonState;

  if(buttonState == BUTTON2){
    
    choice = counter % 3;
  
    switch(choice){
      case 0:
      state0(); 
      break;
      case 1:
      state1();
      break;
      case 2:
      state2();
    }
  }
  */
}

void state0(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp:       C");
  lcd.setCursor(6, 0);
  lcd.print(calculateTemp());
}

void state1(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Schermpie");
  lcd.setCursor(0,1);
  lcd.print("twee");
}

void state2(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("LCD");
  lcd.setCursor(0,1);
  lcd.print("drie");
}
