
int incomingByte = 0;
bool isOn = false;
bool turnOff = false;

void setup() {

  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
}

void loop() {

  digitalWrite(6,LOW);
  digitalWrite(7,LOW);

  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) { 
   incomingByte = Serial.read();
   incomingByte = incomingByte - '0';
  }

  if (incomingByte == 0) {
    turnOff = true;
  }
  if (incomingByte != 0) {
    turnOff = false;
  }

  if (turnOff && isOn) {
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    isOn = false;
  }

  if (!turnOff && !isOn) {
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  isOn = true;
  }
}
