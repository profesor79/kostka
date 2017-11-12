/*
  AnalogReadSerial
 Reads an analog input on pin 0, prints the result to the serial monitor.
 Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */
int lastPort = 20;
long randNumber;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  for(int i=2;i<lastPort;i++){
    pinMode(i, OUTPUT);     
  }

  randomSeed(analogRead(A6));
}

// the loop routine runs over and over again forever:
void loop() {
  readPins();
  start();
}

void start()
{
  for(int i = 0;i<5;i++){
  setLedsOn();
  delay(1000);           
  setLedsOff();
  delay(10);           

  }
}

void setLedsOff(){
  for(int i =2;i<lastPort;i++){

    delay(10);           
    digitalWrite(i, LOW);   // turn the LED on (HIGH is the voltage level)

  }

}

void getRandom(){
  // print a random number from 10 to 19
  randNumber = random(10, 20);
  Serial.println(randNumber);


}

void setLedsOn(){
  for(int i =2;i<lastPort;i++){
    digitalWrite(i, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(50);           
  }
}

void readPins(){
  int sensorValue = analogRead(A6);  

  Serial.print(sensorValue);
  Serial.println(" a6 reading");

  sensorValue = analogRead(A7);
  Serial.println(" a7 reading");

}

