#include <OneWire.h>

// DS18S20 Temperature chip i/o
OneWire ds(18);  // on pin 18/A4
int HighByte, LowByte, TReading, SignBit, Tc_100, Whole, Fract;

String calculateTemp(){
  //OneWire
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];
  
  ds.reset_search();
  if ( !ds.search(addr)) {
      //Serial.print("No more addresses.\n");
      ds.reset_search();
      return "";
  }
  
  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);         // start conversion, with parasite power on at the end

  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.

  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
  }  
  LowByte = data[0];
  HighByte = data[1];
  TReading = (HighByte << 8) + LowByte;
  SignBit = TReading & 0x8000;  // test most sig bit
  if (SignBit) // negative
  {
    TReading = (TReading ^ 0xffff) + 1; // 2's comp
  }
  Tc_100 = (6 * TReading) + TReading / 4;    // multiply by (100 * 0.0625) or 6.25

  Whole = Tc_100 / 100;  // separate off the whole and fractional portions
  Fract = Tc_100 % 100;

  char buffer1 [4];
  char buffer2 [4];
  itoa(Whole, buffer1, 10);
  itoa(Fract, buffer2, 10);
  
  String res = String(buffer1);
  res = res + ".";
  res = res + String(buffer2);

  return res;
}

