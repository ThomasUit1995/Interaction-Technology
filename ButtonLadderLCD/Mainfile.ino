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

//RGB

int colourRed = 0, colourGreen = 0, colourBlue = 255;

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
    case notInUse:
    if(((millis() - blinkTime) > blinkingTime)){
      blinkTime = millis();
      selectColour(0, 0, 255);
    }
    else if((millis() - blinkTime) > blinkingDelay){
      blinkTime = millis();
      selectColour(0, 0, 0);
    }
    break;
    case inUseNr1:
    break;
    case inUseNr2:
    break;
    case inUseClean:
    break;
    case inUseUnkn:
    break;
    case TRIGGERED:
    if((millis() - triggerTime) > triggerDelay){
      sprayMode = true;
      state = notInUse;
    }
    break;
    case operatorMenu:
    break;
  }
  
  if(state == TRIGGERED){
    
  }
  //else if( motionDetector() ){
    
  //}
  else{
    state = notInUse;
  }
}

void selectColour(int colourRed, int colourGreen, int colourBlue){
  analogWrite(redPin, colourRed);
  analogWrite(greenPin, colourGreen);
  analogWrite(bluePin, colourBlue);
}

