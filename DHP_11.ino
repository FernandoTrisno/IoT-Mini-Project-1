#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

const int ledPinMerah =  21;
const int ledPinKuning =  19;
const int ledPinHijau =  18;
const int button = 32;
const int pinSuhu =26;
double temp = 0 ;
bool stateON = false;

DHT dht11(pinSuhu, DHT11);

 

void setup() {
 Serial.begin(115200);
 //Set Led Output
  pinMode(ledPinMerah, OUTPUT);
  pinMode(ledPinKuning, OUTPUT);
  pinMode(ledPinHijau, OUTPUT);
 //Set Button and DHT11 Input
  pinMode(button, INPUT);
  pinMode(pinSuhu, INPUT);
  dht11.begin();

}

void loop() {
  if (digitalRead(button)) {
    if (stateON) {
      stateON = false;
      Serial.println("===============State OFF===============");
    } else {
      stateON = true;
      Serial.println("===============State ON ===============");
    }
    delay(1000);
  }
  if (stateON) {
    float suhu = dht11.readTemperature();
    if (!isnan(suhu)) {
      temp = suhu;
    }

     Serial.print(suhu); Serial.println(" *C, ");

    if (temp < 31) {
        digitalWrite(ledPinMerah, LOW);
        digitalWrite(ledPinKuning, LOW);
        digitalWrite(ledPinHijau, HIGH);
      } else if (temp >=32 && temp <=33) {
        digitalWrite(ledPinMerah, LOW);
        digitalWrite(ledPinKuning, HIGH);
        digitalWrite(ledPinHijau, HIGH);
      } else if(temp>34){
        digitalWrite(ledPinMerah, HIGH);
        digitalWrite(ledPinKuning, HIGH);
        digitalWrite(ledPinHijau, HIGH);
      }
    } else {
      digitalWrite(ledPinMerah, LOW);
      digitalWrite(ledPinKuning, LOW);
      digitalWrite(ledPinHijau, LOW);
    }
 }
  
