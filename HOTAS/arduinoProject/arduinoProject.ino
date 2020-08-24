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
  11, 0, //Buttons,  Hats
  true, true, false, //X, Y, Z
  false, false, false, //Rx, Ry, Rz, 
  false, true, //Rudder, Throttle
  false, false, false //Accelerator, Brake, Steering
  );

void setup() {
  Serial.begin(9600);
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

// Constant that maps the phyical pin to the joystick button.
const int pinToButtonMap = 4;

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
  
  //int XAxisAnalog = map(analogRead(0), 0, 1024, -127, 128);
  //int YAxisAnalog = map(analogRead(1), 0, 1024, -127, 128);
  //int ZAxisAnalog = map(analogRead(2), 0, 1024, -127, 128);

  int XAxisAnalog = map(analogRead(1), 0, 1024, 1024, 0);
  int YAxisAnalog = map(analogRead(0), 0, 1024, 1024, 0);
  int ThrottleAnalog = map(analogRead(2), 0, 1024, 1024, 0);

  //Serial.print(XAxisAnalog);
  //Serial.print(",");
  //Serial.print(YAxisAnalog);
  //Serial.print(",");
  //Serial.println(ThrottleAnalog);
  
  Joystick.setXAxis(XAxisAnalog);
  Joystick.setYAxis(YAxisAnalog);
  Joystick.setThrottle(ThrottleAnalog);

  delay(50);
}
