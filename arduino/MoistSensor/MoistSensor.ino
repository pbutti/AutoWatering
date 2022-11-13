//To calibrate put the sensor in dry air and in a glass of water. Water is 100%, air is unknown in my case.
const int AirValue = 563;
const int WaterValue = 304;

int moistureValue = 0;
int moisturePercent = 0;

// Turn off / on sensor
bool turnOff = false;
bool isOn = true;

int incomingByte = 0; // for incoming serial data

void setup() {
  // put your setup code here, to run once:
  // Open serial port
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);
  isOn = true;
}

void loop() {
  // put your main code here, to run repeatedly:
  moistureValue = analogRead(A0);
  //Delay 10ms to let the ADC recover
  delay(10);
  //Serial.println(moistureValue);
  moisturePercent = map(moistureValue, AirValue, WaterValue, 0,100);
  if (moisturePercent >= 100) {
    moisturePercent = 100;
  } 
  if (moisturePercent <=0) {
    moisturePercent = 0;
  }

  Serial.println(moisturePercent);

  delay(1000);

  if (Serial.available() > 0) {
    incomingByte = Serial.read(); // for incoming serial data
    incomingByte = incomingByte - '0';
    if (incomingByte == 0) {
      turnOff = true;
    }
    if (incomingByte != 0) {
      turnOff = false;
    }
  } 

  if (turnOff && isOn) {
    Serial.println("Turning Off moist sensor");
    digitalWrite(2,LOW);
    isOn = false;
  }

  if (!turnOff && !isOn) {
    Serial.println("Turning On moist sensor");
    digitalWrite(2,HIGH);
    isOn = true;
  }


}
