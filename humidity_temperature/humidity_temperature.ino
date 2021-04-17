#include "DHT.h"

#define DHTPIN 7   // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11 
DHT dht(DHTPIN, DHTTYPE);
const int redLED = 11;               // Adds a led light (in that case, it is yellow) to pin 9.
const int greenLED = 12;                // Adds a led light (in that case, it is blue) to pin 10.
const int blueLED = 13;
//Soil sensor
int soilsensor=8;
int waterpump=9;
int val; //this variable stores the value received from soil moisture sensor

void setup() {
  Serial.begin(9600); 
  Serial.println("Humidity and temperature");
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9,OUTPUT); //pump
  pinMode(8,INPUT); ///Set pin 8 as input pin, to receive data from Soil moisture sensor
  
  while (! Serial);// wait for serial port to connect. Needed for native USB
  Serial.println("Speed 0 to 255");

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();

  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  if((t < 28) && (t >= 24.7))  {                           // See if the temperature is bigger than 22C.
    digitalWrite(redLED, HIGH);    // The yellow led will turn on.
    digitalWrite(blueLED, LOW);       // The blue led will turn off.
    digitalWrite(greenLED, LOW); 
    delay(1000);
  }
  if(t< 20){                      // If the temperature is smaller than 22C.
    digitalWrite(blueLED, HIGH);      // The blue led will turn on.
    digitalWrite(redLED, LOW);     // The yellow led will turn off.
    digitalWrite(greenLED, LOW);
    delay(1000);// The white led will turn off.
  }
 if((t < 24.7) && (t >= 20)) {                    // If the temperature is equal than 22C.
    digitalWrite(greenLED, HIGH);     // The white led will turn on.
    digitalWrite(redLED, LOW);     // The yellow led will turn off.
    digitalWrite(blueLED, LOW);
    delay(1000);// The blue led will turn off.
 }
  Serial.print("\nHumidity: "); 
  Serial.print(h);
  Serial.print("% "); 
  Serial.print("\nTemperature: "); 
  Serial.print(t);
  Serial.print("C ");
  
  if (Serial.available()) {//loop to operate motor
  int speed = Serial.parseInt(); // to read the number entered as text in the Serial Monitor 
   if (speed >= 0 && speed <= 255){
    analogWrite(waterpump, speed);// tuns on the motor at specified speed 
}
}
  val = digitalRead(8);  //Read data from soil moisture sensor  
  if(val == LOW) {
  digitalWrite(9,LOW); //if soil moisture sensor provides LOW value send LOW value to motor pump and motor pump goes off
}
  else {
  digitalWrite(9,HIGH); //if soil moisture sensor provides HIGH value send HIGH value to motor pump and motor pump get on
}
  delay(400); //Wait for few second and then continue the loop. 
}

 
