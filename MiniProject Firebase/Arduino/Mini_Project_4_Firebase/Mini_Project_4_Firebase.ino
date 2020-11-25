#include <FirebaseESP32.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <ESP32Servo.h>

#define FIREBASE_HOST "https://miniprojectfirebase-2a7aa.firebaseio.com/"
#define FIREBASE_AUTH "Ya9ViNaGHA1l4nnGU8afmv2HXiJOctTZIGyscakF"

//SSID dan Password Wifi
char ssid[] = "Tenda_597398";
char pass[] = "lunakucing";

//Pin yang dipakai
int pinServo = 19;
int pinSuhu = 26;

FirebaseData dataFB;
Servo servo;
int sudut = 0;
int suhu = 0;
int tampSuhu;
int sistem = 1;

DHT dht11(pinSuhu, DHT11);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  dht11.begin();
  servo.attach(pinServo); // Servo pin berada di pin 19
  servo.write(0); // Program Berjalan, servo bergerak 0 Derajat
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true); // mengijinkan jika koneksi wifi terputus

  connect(); // Mencoba connect ke wifi
}

void connect() {
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Sukses terkoneksi wifi!");
  Serial.println("IP Address:"); //alamat ip lokal
  Serial.println(WiFi.localIP());
}


void loop() {
  Firebase.getString(dataFB, "/Sistem");
  if (dataFB.intData() == 1) {
    sistem = 1;
  } else {
    sistem = 0;
  }

 // if (sistem == 1) {
    tampSuhu = dht11.readTemperature();
    if (!isnan(tampSuhu)) {
      suhu = tampSuhu;
      Firebase.setInt(dataFB, "/Suhu", suhu); // ketika dieksekusi nilai suhu akan diganti
    }
    if (Firebase.getInt(dataFB, "/Servo")) {
      servo.write(dataFB.intData());
    }
//  }
}
