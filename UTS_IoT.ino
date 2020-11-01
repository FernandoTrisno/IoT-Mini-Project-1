#include <BlynkSimpleEsp32.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <dummy.h>
#include <Blynk.h>
#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

#define BLYNK_PRINT Serial
//menginisialisasikan variable warna
#define BLYNK_RED       "#D3435C"
#define BLYNK_GREEN     "#23C48E"


//Pin yang dipakai
const int ledPinSuhu=  21; // LED Merah
const int ledPinCahaya =  19; // LED Hijau 
const int pinSuhu = 26;
const int pinCahaya = 32;

// Data data yang dipakai
int suhu = 0;
int ldr = 0;
int sliderCahaya = 0;
int sliderSuhu = 0;
int button; //V8
DHT dht11(pinSuhu, DHT11);

//Koneksi Blynk ke WiFi
char auth[] = "CznsiNld3uoKSzKWBNGfmXXCmK-SSWyM";
char ssid[] = "Tenda_597398";
char pass[] = "lunakucing";

//Widget yang dipakai
WidgetLED ledCahaya(V6);
WidgetLED ledSuhu(V7);


void setup() {
 Serial.begin(115200);
 Blynk.begin(auth, ssid, pass, IPAddress(192,168,0,103), 8080);
 //Set Led Output
  pinMode(ledPinSuhu, OUTPUT);
  pinMode(ledPinCahaya, OUTPUT);
 //Set LDR and DHT11 Input
  pinMode(pinCahaya, INPUT);
  pinMode(pinSuhu, INPUT);
 //Set Virtual LED ON
  ledCahaya.on();
  ledSuhu.on();
  
  dht11.begin();

}

//Membaca input dari Blynk (V4)
BLYNK_WRITE(V4){ 
  sliderCahaya = param.asInt() * 0.009768 + 10;
}

//Membaca input dari Blynk (V5)
BLYNK_WRITE(V5){
  sliderSuhu = param.asInt();
}

//Membaca input dari Blynk (V8)
BLYNK_WRITE(V8){
   button = param.asInt();
}


//Method detksi cahaya
void DeteksiCahaya(){
  int temp = analogRead(pinCahaya);
  ldr = (0.009758 * temp) + 10;
  Serial.print(F("Cahaya :"));
  Serial.print(ldr);
  Serial.print(" lux | ");
  Blynk.virtualWrite(V0,ldr);
  Blynk.virtualWrite(V2,ldr);
  Serial.print(sliderCahaya);
    if(ldr > sliderCahaya){
      Blynk.setProperty(V6,"color",BLYNK_RED);
      digitalWrite(ledPinCahaya, HIGH);
    }else{
      Blynk.setProperty(V6,"color",BLYNK_GREEN);
      digitalWrite(ledPinCahaya, LOW);
    }
}

// Method deteksi suhu
void DeteksiSuhu(){
  suhu = dht11.readTemperature();
  Serial.print(F("Suhu: "));
  Serial.print(suhu);
  Serial.print("°C | ");
   Serial.print(sliderSuhu);
  Serial.println();
  
  Blynk.virtualWrite(V1, suhu);
  Blynk.virtualWrite(V3, suhu);
      if(suhu > sliderSuhu){
      Blynk.setProperty(V7,"color",BLYNK_RED);
      digitalWrite(ledPinSuhu, HIGH);
    }else{
      Blynk.setProperty(V7,"color",BLYNK_GREEN);
      digitalWrite(ledPinSuhu, LOW);
    }
}


void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  if(button==1){
  DeteksiCahaya();
  DeteksiSuhu();
  }
  delay(250);
}
