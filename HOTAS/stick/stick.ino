void setup() {
  Serial.begin(9600);
  // Initialize Button Pins
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
}

void loop() {
  int PitchAxisAnalog = analogRead(5);
  int RollAxisAnalog = analogRead(6);
  int YawAxisAnalog = analogRead(7);
  bool button1 = digitalRead(2);
  bool button2 = digitalRead(3);
  bool button3 = digitalRead(4);
  bool button4 = digitalRead(5);
  bool button5 = digitalRead(6);
  bool button6 = digitalRead(7);
  bool button7 = digitalRead(8);
  bool button8 = digitalRead(9);
  bool button9 = digitalRead(10);
  bool button10 = digitalRead(11);
  bool button11 = digitalRead(12);

  char stringToSend[100];
  sprintf(stringToSend, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",analogRead(5),analogRead(6),analogRead(7),button1,button2,button3,button4,button5,button6,button7,button8,button9,button10,button11);
  Serial.write(stringToSend);
  
  delay(50);
}
