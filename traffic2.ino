#define interruptPin  20        //IR sensor 'OUT' wired to pin 20
volatile int state = LOW;       //volatile bc being changed by something beyond the code(ISR)

#define redLight      9         //traffic set 1 
#define yellowLight   8         //traffic set 1
#define greenLight    7         //traffic set 1

#define redLight2     4         //CT
#define yellowLight2  3         //CT
#define greenLight2   2         //CT
//--------------------------------
void setup() { 
  Serial.begin(115200);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), ISR_BUTTON, CHANGE); 

  byte allLed[6] = { 9, 8, 7, 4, 3, 2 };        //array containing all pin locations //byte to save space
  for (byte i = 0; i < sizeof(allLed); i++) {   //by cycling the pin numbers, each get equal brightness
    pinMode(allLed[i], OUTPUT);                 //output is the LEDs
  }
}
//---------------------------------
void loop() {

  state;
  smartTrafficLight();
  
}
/*-----------ISR_BUTTON-------------
/*keeping ISR method short to keeps program efficient
/*sensor (global var) defined as LOW
/*incrementing the sensor from 0 (LOW) to 1 (HIGH)
/*triggering the smarttrafficLight method
/*---------------------------------*/
void ISR_BUTTON() {                     
  
   state++;                           
                         
}
//---------------------------------
static void smartTrafficLight() {

  int state = digitalRead(interruptPin);

  if (state == HIGH) {                  //if no object is sensed...
    digitalWrite(greenLight,  HIGH);    //'Highway' green light on
    digitalWrite(redLight2,   HIGH);    //CT RED LIGHT
  }
  else {                                 //if a car is sensed...
    delay(5000);                         //wait 5 seconds to change
    digitalWrite(greenLight,  LOW);      //turn off green light
    digitalWrite(yellowLight, HIGH);     //changes to yellow
    delay(2000);                         //yellow on for 2 seconds
    digitalWrite(yellowLight, LOW);      //yellow off
    digitalWrite(redLight,    HIGH);     //red light on
    delay(2000);                         //waiting 2 second to turn CT green

    //cross traffic (CT) lights
    digitalWrite(redLight2,   LOW);      //turning off red
    digitalWrite(greenLight2, HIGH);     //CT GREEN
    delay(3000);                         //CT green for 3 seconds
    digitalWrite(greenLight2, LOW);      //turn off green
    digitalWrite(yellowLight2,HIGH);     //once else cycle is finished, CT yellow changes
    delay(2000);                         //CT yellow light on for 2 seconds
    digitalWrite(yellowLight2,LOW);      //CT yellow light off
    digitalWrite(redLight2,   HIGH);     //CT redlight on
    delay(2000);                         //waiting 2 seconds to change 

    digitalWrite(redLight,    LOW);      //'Highway' red light turns off
  }
}
//--------------------------------
