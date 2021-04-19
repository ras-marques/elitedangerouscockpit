// Simple example application that shows how to read four Arduino
// digital pins and map them to the USB Joystick library.
//
// Ground digital pins 9, 10, 11, and 12 to press the joystick 
// buttons 0, 1, 2, and 3.
//
// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only.
//
// by Matthew Heironimus
// 2015-11-20
//--------------------------------------------------------------------

#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  18, 1, //Buttons,  Hats
  true, true, false, //X, Y, Z
  true, true, false, //Rx, Ry, Rz, 
  true, true, //Rudder, Throttle
  false, false, false //Accelerator, Brake, Steering
  );

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  // Initialize Button Pins
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);

  // Initialize Joystick Library
  Joystick.begin();
}

// Last state of the button
int lastButtonState[3] = {0,0,0};

void loop() {
  Joystick.setButton(0, !digitalRead(3));
  Joystick.setButton(1, !digitalRead(5));
  Joystick.setButton(2, !digitalRead(4));
  Joystick.setButton(8, !digitalRead(6));
  Joystick.setButton(9, !digitalRead(7));
  Joystick.setButton(6, !digitalRead(8));
  Joystick.setButton(10, !digitalRead(9));
  Joystick.setButton(5, !digitalRead(10));
  Joystick.setButton(3, !digitalRead(11));
  Joystick.setButton(4, !digitalRead(12));
  Joystick.setButton(7, !digitalRead(13));

  int XAxisAnalog = map(analogRead(1), 0, 1024, 1024, 0);
  int YAxisAnalog = map(analogRead(0), 0, 1024, 1024, 0);
  int ThrottleAnalog = map(analogRead(2), 0, 1024, 1024, 0);
  
  Joystick.setXAxis(XAxisAnalog);
  Joystick.setYAxis(YAxisAnalog);
  Joystick.setThrottle(ThrottleAnalog);

  String nano;
  if(Serial1.available()) {
    nano = Serial1.readStringUntil('\n');// read the incoming data as string
    //Serial.println(nano);

    char nanoArray[100];
    nano.toCharArray(nanoArray, 100);
    int arrayOfNanoInts[15];
    char* token = strtok(nanoArray, ",");
    arrayOfNanoInts[0] = atoi(token);
//    Serial.print(arrayOfNanoInts[0]);
//    Serial.print(",");
    int i;
    for(i = 1;; i++){
      token = strtok(NULL, ",");
      if(token == NULL) break;
      arrayOfNanoInts[i] = atoi(token);
//      Serial.print(arrayOfNanoInts[i]);
//      if(i == 13) Serial.println("");
//      else Serial.print(",");
    }
    //Serial.println(i);

    if(i == 14){
      bool hatUp = !arrayOfNanoInts[6];
      bool hatRight = !arrayOfNanoInts[10];
      bool hatDown = !arrayOfNanoInts[8];
      bool hatLeft = !arrayOfNanoInts[7];
      if(!hatUp && !hatRight && !hatDown && !hatLeft) Joystick.setHatSwitch(0, -1);
      else if(hatUp && !hatRight && !hatDown && !hatLeft) Joystick.setHatSwitch(0, 0);
      else if(hatUp && hatRight && !hatDown && !hatLeft) Joystick.setHatSwitch(0, 45);
      else if(!hatUp && hatRight && !hatDown && !hatLeft) Joystick.setHatSwitch(0, 90);
      else if(!hatUp && hatRight && hatDown && !hatLeft) Joystick.setHatSwitch(0, 135);
      else if(!hatUp && !hatRight && hatDown && !hatLeft) Joystick.setHatSwitch(0, 180);
      else if(!hatUp && !hatRight && hatDown && hatLeft) Joystick.setHatSwitch(0, 225);
      else if(!hatUp && !hatRight && !hatDown && hatLeft) Joystick.setHatSwitch(0, 270);
      else if(hatUp && !hatRight && !hatDown && hatLeft) Joystick.setHatSwitch(0, 315);

      arrayOfNanoInts[0] = map(arrayOfNanoInts[0],830,230,0,1024);
      if(arrayOfNanoInts[0] < 0) arrayOfNanoInts[0] = 0;
      if(arrayOfNanoInts[0] > 1023) arrayOfNanoInts[0] = 1023;
      arrayOfNanoInts[1] = map(arrayOfNanoInts[1],830,230,0,1024);
      if(arrayOfNanoInts[1] < 0) arrayOfNanoInts[1] = 0;
      if(arrayOfNanoInts[1] > 1023) arrayOfNanoInts[1] = 1023;
      arrayOfNanoInts[2] = map(arrayOfNanoInts[2],255,0,0,1024);
      if(arrayOfNanoInts[2] < 0) arrayOfNanoInts[2] = 0;
      if(arrayOfNanoInts[2] > 1023) arrayOfNanoInts[2] = 1023;

      for(int index = 0; index < 14; index++){
        Serial.print(arrayOfNanoInts[index]);
        Serial.print(",");
      }
      Serial.print("\n");
  
      Joystick.setRxAxis(arrayOfNanoInts[0]);
      Joystick.setRyAxis(arrayOfNanoInts[1]);
      Joystick.setRudder(arrayOfNanoInts[2]);
      Joystick.setButton(11,!arrayOfNanoInts[3]);
      Joystick.setButton(12,!arrayOfNanoInts[4]);
      Joystick.setButton(13,!arrayOfNanoInts[5]);
      Joystick.setButton(14,!arrayOfNanoInts[9]);
      Joystick.setButton(15,!arrayOfNanoInts[11]);
      Joystick.setButton(16,!arrayOfNanoInts[12]);
      Joystick.setButton(17,!arrayOfNanoInts[13]);
    }
  }

  delay(25);
}
