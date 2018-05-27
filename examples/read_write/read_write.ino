#include <EEPROM.h>
#include <EType.h>
#include <IPAddress.h>

EByte               testByte(0);
EIPAddress          testIp(EByte::size());
EString             testString(EByte::size() + EIPAddress::size());
EType<int>          testInt(EByte::size() + EIPAddress::size() + EString::size());

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(2000);
  Serial.println();
  Serial.println("Current status:");
  Serial.print("testByte   =");Serial.println(testByte);
  Serial.print("testString =");Serial.println(testString);
  Serial.print("testInt    =");Serial.println(testInt);
  Serial.print("testIp     =");Serial.println(IPAddress(testIp));
  Serial.println("===========================");
  
  Serial.println("Enter value 0:255");
  while (Serial.available() <= 0) {};
  testByte = Serial.parseInt();

  Serial.println("Enter value -32768:32767");
  while (Serial.available() <= 0) {};
  testInt = Serial.parseInt();

  Serial.println("Enter string (32 char max!)");
  while (Serial.available() <= 0) {};
  String str = Serial.readString();
  testString = str.c_str();

  Serial.print("Enter IPAddress (xxx.xxx.xxx.xxx)");
  while (Serial.available() <= 0) {};
  str = Serial.readStringUntil('\r');
  IPAddress ip;
  testIp = ip;
  
  Serial.println();
  Serial.println("===========================");
  Serial.println("Restart board");
  delay(500);
  asm volatile ("  jmp 0"); 
}

void loop() {
  return;
}
