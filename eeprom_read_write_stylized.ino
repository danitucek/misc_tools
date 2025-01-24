#include <EEPROM.h>

int charInLine = 0; //counter for the length of bytes in one row
int EEsize = 512; //size of the EEPROM, change to the value your MCU has (ATMega328P: 512, ATMega32u4: 1024)


void setup() {
  Serial.begin(9600);
  //randToEeprom(); - USE WISELY, EEPROM only has 100k rewrites, never put in loop!!!
  readEeprom();

}
void loop() {
}

//this function read the contents of the EEPROM and prints it out
//on the serial monitor in a standard 8 byte pattern (values in DEC, or HEX (add HEX after addr at line 30))
void readEeprom() {
  Serial.println();
  Serial.print("00: "); //initial print to reduce code size
  for (int addr = 0; addr < EEsize; addr++) {
    if (charInLine >= 8) { //the condition for a LF after 8 bytes
      Serial.println();
      if (addr<16) Serial.print("0"); //condition to add a leading 0 when the hex number in below 0x10 (16 in DEC)
      Serial.print(addr,HEX);
      Serial.print(": ");
      charInLine = 0;
    }
    if (EEPROM.read(addr)<16) Serial.print("0");
    Serial.print(EEPROM.read(addr),HEX);
   // Serial.print(addr);
    Serial.print(" ");
    charInLine++;
  }
}

void randToEeprom() {
  Serial.print("Writing random numbers to EEPROM");
  for (int addr = 0; addr < EEsize; addr++) {
    int num = random(0,255);
    EEPROM.update(addr, num); //use .update instead of .write for a single-cell overwrite (not whole memory)
    Serial.print(".");
  }
  Serial.println(" DONE!");
}
