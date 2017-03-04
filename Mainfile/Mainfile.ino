const int notInUse = 0;
const int inUseNr1 = 1;
const int inUseNr2 = 2;
const int inUseClean = 3;
const int inUseUnkn = 4;
const int TRIGGERED = 5;
const int operatorMenu = 6;
int state;

//blinking
long blinkTime = -1;
int blinkingTime = 500;
int blinkingDelay = 500;

//pins
//RBG
const int redPin = 11, greenPin = 10, bluePin = 9; 
//Motion sensor
const int motionPin = 12;
//AirWick
const int airWick = 13;
//Override trigger button
const int triggerPin = 17;


//Manual override button pin 17
int triggerState;
long triggerTime;
long sprayTime;
long triggerDelay = 5000;
long sprayingTime = 2000;
bool triggerInUse = false;
bool sprayMode = false;
bool spraying = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(triggerPin, INPUT);
  pinMode(airWick, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  triggerState = digitalRead(triggerPin);
  
  if(triggerState == 0 && !triggerInUse){
    state = TRIGGERED;
    triggerInUse = true;
    triggerTime = millis();
  }

  if(sprayMode == true){
    if(!spraying){
      digitalWrite(airWick, HIGH);
      sprayTime = millis();
      spraying = true;
    }
    if(spraying && ((millis() - sprayTime) > sprayingTime)){
      spraying = false;
      digitalWrite(airWick, LOW);
      triggerInUse = false;
      sprayMode = false;
    }
  }

  switch(state){
    //State not in use : LED OFF
    case notInUse:
    selectColour(0,0,0);
    break;

    //State in use number 1 : LED GREEN
    case inUseNr1:
    selectColour(0,255,0);
    break;

    //State in use number 2 : LED GREEN BLINKING
    case inUseNr2:
    if(((millis() - blinkTime) > blinkingTime)){
      blinkTime = millis();
      selectColour(0, 255, 0);
    }
    else if((millis() - blinkTime) > blinkingDelay){
      blinkTime = millis();
      selectColour(0, 0, 0);
    }
    break;

    //State in use cleaning : LED BLUE
    case inUseClean:
    selectColour(0,0,255);
    break;

    //State in use but unknown : LED RED
    case inUseUnkn:
    selectColour(255,0,0);
    break;

    //State manual override mode triggered : LED RED BLINKING
    case TRIGGERED:
    if((millis() - triggerTime) > triggerDelay){
      sprayMode = true;
      state = notInUse;
    }
    if(((millis() - blinkTime) > blinkingTime)){
      blinkTime = millis();
      selectColour(255, 0, 0);
    }
    else if((millis() - blinkTime) > blinkingDelay){
      blinkTime = millis();
      selectColour(0, 0, 0);
    }
    break;

    //State operator manu active : LED BLUE BLINKING
    case operatorMenu:
    if(((millis() - blinkTime) > blinkingTime)){
      blinkTime = millis();
      selectColour(0, 0, 255);
    }
    else if((millis() - blinkTime) > blinkingDelay){
      blinkTime = millis();
      selectColour(0, 0, 0);
    }
    break;
  }
  
  if(state != TRIGGERED){
    state = notInUse;
  }
}

void selectColour(int colourRed, int colourGreen, int colourBlue){
  analogWrite(redPin, colourRed);
  analogWrite(greenPin, colourGreen);
  analogWrite(bluePin, colourBlue);
}

