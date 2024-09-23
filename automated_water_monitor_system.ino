#define BLYNK_TEMPLATE_ID "TMPL2XMWK4eBZ"
#define BLYNK_TEMPLATE_NAME "water guage"
#define BLYNK_AUTH_TOKEN "u8JBuezTZiyhmTxtPWUan-4nw-X1xtnb"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Ultrasonic.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Redmi Note 12 Pro";
char pass[] = "highspypunk";

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

  pinMode(bulb1, OUTPUT);
  pinMode(bulb2, OUTPUT);
  pinMode(bulb3, OUTPUT);
  pinMode(bulb4, OUTPUT);
  pinMode(relayPin, OUTPUT);

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Connecting to Blynk...");
  
  
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi connected");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());

  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Blynk.begin(auth, ssid, pass); 
}

void loop() {
  if (!Blynk.connected()) {
    Serial.println("Blynk not connected, trying to reconnect...");
    Blynk.connect(); 
  }

  Blynk.run(); 

  long distance = ultrasonic.read(); 
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" cm");

  
  int percentage = map(distance, 0, 20, 100, 0);
  Blynk.virtualWrite(V2, percentage); 
  
  
   if (distance > 15 && distance <= 20) {
    Blynk.virtualWrite(V7, 1);
    Blynk.virtualWrite(V6, 0);
    Blynk.virtualWrite(V5, 0);
    Blynk.virtualWrite(V4, 0);
    digitalWrite(bulb1, HIGH);
    digitalWrite(bulb2, LOW);
    digitalWrite(bulb3, LOW);
    digitalWrite(bulb4, LOW);
  } else if (distance > 10 && distance <= 15) {
    Blynk.virtualWrite(V7, 1);
    Blynk.virtualWrite(V6, 1);
    Blynk.virtualWrite(V5, 0);
    Blynk.virtualWrite(V4, 0);
    digitalWrite(bulb1, HIGH);
    digitalWrite(bulb2, HIGH);
    digitalWrite(bulb3, LOW);
    digitalWrite(bulb4, LOW);
  } else if (distance > 5 && distance <= 10) {

    digitalWrite(bulb1, HIGH);
    digitalWrite(bulb2, HIGH);
    digitalWrite(bulb3, HIGH);
    digitalWrite(bulb4, LOW);
    Blynk.virtualWrite(V7, 1);
    Blynk.virtualWrite(V6, 1);
    Blynk.virtualWrite(V5, 1);
    Blynk.virtualWrite(V4, 0);
  } else if (distance > 3 && distance <= 5) {
    digitalWrite(bulb1, HIGH);
    digitalWrite(bulb2, HIGH);
    digitalWrite(bulb3, HIGH);
    digitalWrite(bulb4, HIGH);
    delay(200);
    digitalWrite(bulb4, LOW);
    delay(100);
    Blynk.virtualWrite(V7, 1);
    Blynk.virtualWrite(V6, 1);
    Blynk.virtualWrite(V5, 1);
    Blynk.virtualWrite(V4, 1);
    delay(200);
    Blynk.virtualWrite(V4, 0);
    delay(100);
    
  } else if (distance <= 3 && distance > 0) {
    digitalWrite(bulb1, HIGH);
    digitalWrite(bulb2, HIGH);
    digitalWrite(bulb3, HIGH);
    digitalWrite(bulb4, HIGH);
    Blynk.virtualWrite(V7, 1);
    Blynk.virtualWrite(V6, 1);
    Blynk.virtualWrite(V5, 1);
    Blynk.virtualWrite(V4, 1);
    
  } else {
    digitalWrite(bulb1, LOW);
    digitalWrite(bulb2, LOW);
    digitalWrite(bulb3, LOW);
    digitalWrite(bulb4, LOW);
    Blynk.virtualWrite(V7, 0);
    Blynk.virtualWrite(V6, 0);
    Blynk.virtualWrite(V5, 0);
    Blynk.virtualWrite(V4, 0);
  }

  delay(1500); 
}
