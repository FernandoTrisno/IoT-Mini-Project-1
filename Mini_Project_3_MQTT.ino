#include <WiFi.h>
#include <WiFiClient.h>
#include <MQTT.h>
#include <MQTTClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <ESP32Servo.h>

//SSID dan Password Wifi
char ssid[] = "Tenda_597398";
char pass[] = "lunakucing";

//Pin yang dipakai
int pinServo = 21;
int pinSuhu = 26;

WiFiClient wifi;
MQTTClient client;
Servo servo;
int suhu =0;
String cekSuhu;
DHT dht11(pinSuhu, DHT11);
boolean statusTombol = true;
int cekOnOff=1;

  
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  dht11.begin();
  servo.attach(pinServo); // Servo pin berada di pin 21
  servo.write(30); // Program Berjalan, servo bergerak 30 Derajat
  client.begin("broker.shiftr.io", wifi);
  client.onMessage(messageReceived);
  

  connect(); // Mencoba connect ke wifi

}

void connect(){
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("ESP32", "6d3607d3", "3f9d55376e49a9f8")) { // 
    Serial.print(".");  
    delay(500);
  }

  Serial.println("\nconnected!");
   
  client.subscribe("/tombol"); // Untuk melihat di serial monitor
  client.subscribe("/suhu");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload); // Data yang masuk
  if (topic ==  "/tombol") {
    if (payload == "1") { // Jika Payload == 1
      Serial.print(" Tombol ON!!!");
      statusTombol = true; // Tombol On, Status menjadi True
      cekOnOff=1;
    } else {
      Serial.print(" Tombol OFF!!!");
      statusTombol = false; // Tombol Off, Stauts menjadi False
      cekOnOff=0;
    }
  }
}

void suhuToMove(){
  suhu = dht11.readTemperature();
  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.println("°C ");
  cekSuhu = String(suhu);
  if(suhu<=25){
    servo.write(45);
    Serial.println("Cek Suhu 1");
  }
  if(suhu >= 26 && suhu <27){
    servo.write(90);
    Serial.println("Cek Suhu 2");
  }if(suhu >= 27){
    servo.write(180);
    Serial.println("Cek Suhu 3");
  }
}

void loop() {
  client.loop();
  delay(10);
  if (!client.connected()) {
    connect();
  }
  if(statusTombol == true){
    suhuToMove();
    client.publish("/suhu",cekSuhu);
  }
  delay(1000); 
}
