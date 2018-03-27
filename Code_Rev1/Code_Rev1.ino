
bool set1a = LOW; //recieve pins
bool set1b = LOW;
bool set2a = LOW;
bool set2b = LOW;
bool set3a = LOW;
bool set3b = LOW;
bool set4a = LOW;
bool set4b = LOW;
bool set5 = LOW;
bool oldpin[9][6];

int set;
int sendPin = 42;

void keyboardDecode(int pin) { //takes our input pin and compares it to every set, sends midi data
  int pinArray = pin - 36; //pin 0 - 48
  if((set1a == HIGH) && ( set1a != oldpin[0][pinArray % 6])) {
    noteOn(144, pin - 6, 127);  // (cmd, pitch, velocity)
    oldpin[0][pinArray % 6] = 1;
  } 
  else if((set1a == LOW) && oldpin[0][pinArray % 6])  {
    noteOn(144, pin - 6, 0);
    oldpin[0][pinArray % 6] = 0;
  }
  //delay(1);
  if((set1b == HIGH) && (set1b != oldpin[1][pinArray % 6])) {
    noteOn(144, pin, 127);
    oldpin[1][pinArray % 6] = 1;
  } 
  else if((set1b == LOW) && oldpin[1][pinArray % 6]) {
    noteOn(144, pin, 0);
    oldpin[1][pinArray % 6] = 0;
  }
  //delay(1);
  if((set2a == HIGH) && (set2a != oldpin[2][pinArray % 6])) {
    noteOn(144, pin + 6, 127);
    oldpin[2][pinArray % 6] = 1;
  } 
  else if((set2a == LOW) && oldpin[2][pinArray % 6]) {
    noteOn(144, pin + 6, 0);
    oldpin[2][pinArray % 6] = 0;
  }
  //delay(1);
  if((set2b == HIGH) &&(set2b != oldpin[3][pinArray % 6])) {
    noteOn(144, pin + 12, 127);
    oldpin[3][pinArray % 6] = 1;
  } 
  else if((set2b == LOW) && oldpin[3][pinArray % 6]) {
    noteOn(144, pin + 12, 0);
    oldpin[3][pinArray % 6] = 0;
  }
  //delay(1);
  if((set3a == HIGH) && (set3a != oldpin[4][pinArray % 6])) {
    noteOn(144, pin + 18, 127);
    oldpin[4][pinArray % 6] = 1;
  } 
  else if((set3a == LOW) && oldpin[4][pinArray % 6]) {
    noteOn(144, pin + 18, 0);
    oldpin[4][pinArray % 6] = 0;
  }
  //delay(1);
  if((set3b == HIGH) && (set3b != oldpin[5][pinArray % 6])) {
    noteOn(144, pin + 24, 127);
    oldpin[5][pinArray % 6] = 1;
  } 
  else if((set3b == LOW) && oldpin[5][pinArray % 6]) {
    noteOn(144, pin + 24, 0);
    oldpin[5][pinArray % 6] = 0;
  }
  //delay(1);
  if((set4a == HIGH) && (set4a != oldpin[6][pinArray % 6])) {
    noteOn(144, pin + 30, 127);
    oldpin[6][pinArray % 6] = 1;
  } 
  else if ((set4a == LOW) && oldpin[6][pinArray % 6]) {
    noteOn(144, pin + 30, 0);
    oldpin[6][pinArray % 6] = 0;
  }
  //delay(1);
  if((set4b == HIGH) && (set4b != oldpin[7][pinArray % 6])) {
    noteOn(144, pin + 36, 127);
    oldpin[7][pinArray % 6] = 1;
  } 
  else if((set4b == LOW) && oldpin[7][pinArray % 6]) {
    noteOn(144, pin + 36, 0);
    oldpin[7][pinArray % 6] = 0;
  }
  //delay(1);
  if((set5 == HIGH) && (set5  != oldpin[8][pinArray % 6])) {
    noteOn(144, 84, 127);
    oldpin[8][pinArray % 6] = 1;
  } 
  else if((set5 == LOW) && oldpin[8][pinArray % 6]) {
    noteOn(144, 84, 0);
    oldpin[8][pinArray % 6] = 0;
  }
}

void noteOn(int cmd, int pitch, int velocity) { //send midi data function
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

void reset() {
  for(int i = 0; i < 100; i++) {
    noteOn(144,i, 0);
  }
}
void setup() {
  Serial.begin(38400);
  for(int i = 42; i <= 47; i++) //set all of our outputs for keyboard
    pinMode(i, OUTPUT);
    
  for(int i = 39; i <=41; i++) //set inputs, they are divided over outputs
    pinMode(i, INPUT);

  for(int i = 48; i <=53; i++)
    pinMode(i, INPUT);
}

void loop() {
digitalWrite(sendPin, HIGH); //sweep through sendpins 42-47
set1a = digitalRead(39);     //read in our inputs for each 6 keys
set1b = digitalRead(40);
set2a = digitalRead(41);
set2b = digitalRead(53);
set3a = digitalRead(52);
set3b = digitalRead(51);
set4a = digitalRead(50);
set4b = digitalRead(49);
set5 = digitalRead(48);
//delay(10);
//reset();

keyboardDecode(sendPin);

digitalWrite(sendPin, LOW);
if(sendPin == 47) //reset to 42
  sendPin = 41;
  
sendPin++;
}

