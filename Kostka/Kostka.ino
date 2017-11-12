/*
dice is a simple solution for my kids
 modes
 0 * two dices 90 seconds
 
 */
int lastPort = 20;
int gameMode = 0; 
long randNumber;
short dice1 = 6;
short dice2 = 6;
short dice3 = 6;


int dice1StartPin = 2;
int dice2StartPin = 8;
int dice3StartPin = 14;

byte diceValues_array[18];     

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
bool buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


unsigned long lastDrawTime = 0;  // the last time the output pin was toggled
unsigned long shutdownDelay = 60000;    // the debounce time; increase if the output flickers

bool started = false;


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  for(int i=2;i<lastPort;i++){
    pinMode(i, OUTPUT);     
  }
  for(int i = 0;i<18;i++){
    diceValues_array[i]=true;
  }
  randomSeed(analogRead(A6));
}

// the loop routine runs over and over again forever:
void loop() {
  if(!started)  start();
  readAnalogPin();
  switchOff();
}



void start()
{
  started=true;  
  for(int a = 1;a<7;a++){
    for(int i = 1;i<7;i++){  
      diceValues_array[i-1] = a>=i; 
    }  

    for(int i = 1;i<7;i++){  
      diceValues_array[6+i] = a>=i; 
    }  

    for(int i = 1;i<7;i++){  
      diceValues_array[13+i] = a>=i;
    }

    setLedsOn();

    delay(150);           
    setLedsOff();
    delay(10);           
  }

  for(int i = 0;i<18;i++){
    diceValues_array[i]=false;
  }

  draw();
}

void switchOff(){

  if ((millis() - lastDrawTime) > shutdownDelay) {
lastDrawTime = millis();
    setLedsOff();

  }
}

void readAnalogPin(){
  // read the state of the switch into a local variable:
  bool reading = analogRead(A6)>600; 

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      // draw new numbers on high
      if (buttonState == LOW) {
        Serial.println("setting draw();");
        started=false;
        lastDrawTime = millis();
      }

      buttonState = reading;
    }
  }

  // set the LED:
  //   digitalWrite(ledPin, ledState);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;

}

void draw(){

  setLedsOff();

  dice1 =  random(1, 7);
  dice2 =  random(1, 7);
  dice3 =  random(1, 7);

  Serial.print("setting draw dice1;");  
  Serial.println(dice1);
  Serial.print("setting draw dice2;");  
  Serial.println(dice2);
  Serial.print("setting draw dice2;");  
  Serial.println(dice3);

  for(int i = 0;i<6;i++){
    diceValues_array[i] = i+1>=dice1;
  }  
  for(int i = 0;i<6;i++){
    diceValues_array[6+i] = i+1>=dice2;
  }  
  for(int i = 0;i<6;i++){
    diceValues_array[12+i] = i+1>=dice3;
  }

  setLedsOn();
  delay(150);
  setLedsOff();
  delay(150);
  setLedsOn();
  delay(150);
  setLedsOff();
  delay(150);
  setLedsOn();

}


void setDice(short dice, int diceStartPin){

  Serial.print("Setting dice value: ");
  Serial.println(dice);

  Serial.print("Setting dice first port: ");
  Serial.println(diceStartPin);


}


void setLedsOff(){
  for(int i =2;i<lastPort;i++){        
    digitalWrite(i, LOW);   // turn the LED on (HIGH is the voltage level)
  }
}

void getRandom(){
  // print a random number from 10 to 19
  randNumber = random(10, 20);
  Serial.println(randNumber);
}

void setLedsOn(){
  Serial.println("----");
  for(int i = 0;i<18;i++){    
    digitalWrite(i+2, diceValues_array[i]);   // turn the LED on (HIGH is the voltage level)
    Serial.print(i); 

    Serial.print(":"); 
    Serial.print(diceValues_array[i]); 
    Serial.print("--"); 
  }
  Serial.println("----");
}









