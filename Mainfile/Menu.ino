void printScreen(func){
  string* result = func()
  lcd.setCursor(0, 0)
  lcd.print(result[0])
  lcd.setCursor(0, 1)
  lcd.print(result[1])
}

string* screen0(){
  string* result = new string[2];
  result[0] = "REMAINING:";
  result[1] = "TEMP:";
  return result;
}

string screen1(){
  string* result = new string[2];
  result[0] = "ADJUST DELAY:";
  result[1] = " SECONDS";
  return result;
}

string screen2(){
  string* result = new string[2];
  result[0] = "HOLD B TO RESET";
  result[1] = "REMAINING SPRAYS";
  return result;
}

string screen3(){
    string result[] = {"LIGHT LEVEL:", ""}
}

string screen4(){
  string* result = new string[2];
  result[0] = "RANDOM WORD:";
  result[1] = "";
  return result;
}

string screen5(){
  string* result = new string[2];
  result[0] = "STOPWATCH:";
  result[1] = "00:00.00";
  return result;
}

string screen6(){
  string* result = new string[2];
  result[0] = "HEAD OR TAIL?:";
  result[1] = "";
  return result;
}

