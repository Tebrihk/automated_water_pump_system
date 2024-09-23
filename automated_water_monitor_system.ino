#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Ultrasonic.h>


LiquidCrystal_I2C lcd(0x27, 16, 2); 
Ultrasonic ultrasonic(5, 18); 


const int bulb1 = 23;
const int bulb2 = 16;
const int bulb3 = 17;
const int bulb4 = 19;
const int relayPin = 13; 

void setup() {
  Wire.begin(22, 21); 
  Serial.begin(9600);

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("thrixxy tech");

  
  pinMode(bulb1, OUTPUT);
  pinMode(bulb2, OUTPUT);
  pinMode(bulb3, OUTPUT);
  pinMode(bulb4, OUTPUT);
  pinMode(relayPin, OUTPUT); 
}

void loop() {
  long distance = ultrasonic.read();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" cm");
 
  
  if (distance > 15 && distance <= 20) {
    digitalWrite(bulb1, HIGH);
    digitalWrite(bulb2, LOW);
    digitalWrite(bulb3, LOW);
    digitalWrite(bulb4, LOW);
    digitalWrite(relayPin, HIGH); 
  } else if (distance > 10 && distance <= 15) {
    digitalWrite(bulb1, HIGH);
    digitalWrite(bulb2, HIGH);
    digitalWrite(bulb3, LOW);
    digitalWrite(bulb4, LOW);
    digitalWrite(relayPin, HIGH); 
  } else if (distance > 5 && distance <= 10) {
    digitalWrite(bulb1, HIGH);
    digitalWrite(bulb2, HIGH);
    digitalWrite(bulb3, HIGH);
    digitalWrite(bulb4, LOW);
    digitalWrite(relayPin, HIGH); 
  } else if (distance > 3 && distance <= 5) {
    digitalWrite(bulb1, HIGH);
    digitalWrite(bulb2, HIGH);
    digitalWrite(bulb3, HIGH);
    digitalWrite(bulb4, HIGH);
    delay(200);
    digitalWrite(bulb4, LOW);
    delay(100);
    digitalWrite(relayPin, HIGH); 
    
  } else if (distance <= 3 && distance > 0) {
    digitalWrite(bulb1, HIGH);
    digitalWrite(bulb2, HIGH);
    digitalWrite(bulb3, HIGH);
    digitalWrite(bulb4, HIGH);
    digitalWrite(relayPin, LOW); 
  } else {
    digitalWrite(bulb1, LOW);
    digitalWrite(bulb2, LOW);
    digitalWrite(bulb3, LOW);
    digitalWrite(bulb4, LOW);
    digitalWrite(relayPin, LOW); 
  }

  if (!(distance <= 3 && distance > 0)) {
    delay(1500);
  }
}
