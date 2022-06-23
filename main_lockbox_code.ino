#include <Servo.h>
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>

PN532_I2C pn532i2c(Wire);
PN532 nfc(pn532i2c);

Servo myservo;  // create servo object to control a servo
int pos=1; // variable to store the servo position

void setup() {
  nfc.begin();
  nfc.SAMConfig(); // configure board to read RFID tags 
} 

void loop() {
  if(pos==1){
    myservo.attach(3);  // attaches the servo on pin 3 to the servo object "Digital 3"
    myservo.writeMicroseconds(2300);
    pos=2;
    delay(1000);
  }
  if(pos==3){
    myservo.attach(3);  // attaches the servo on pin 3 to the servo object "Digital 3"
    myservo.writeMicroseconds(1000);
    pos=4;
    delay(1000);
  }
  if(pos==2){
    myservo.detach();
  }
  if(pos==4){
    myservo.detach();
    delay(700);
  }
  String ringUid;
  boolean success;
  uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0};  // Buffer to store the returned UID
  uint8_t uidLength; // Length of the UID (4)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);

  if (success & uidLength==4) {

    for (uint8_t i=0; i<4; i++){
      ringUid += String(uid[i], HEX);
    }
    if (ringUid=="1dd0fc37" || ringUid=="7360441c"){
      if(pos!=4){
        pos=3;
      }
      if(pos==4){
        pos=1;
      }
    }
  }
  else {

Serial.println("Access Denied");
  }
 }
