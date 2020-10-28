
const int ledPinMerah =  21;
const int ledPinKuning =  19;
const int ledPinHijau =  18;

unsigned long previousMillis = 0;     
int counter = 0;

// berapa second menyala
const long intervalMerah = 5000;
const long intervalKuning = 1000;
const long intervalHijau = 3000;   

void setup() {
  pinMode(ledPinMerah, OUTPUT);
  pinMode(ledPinKuning, OUTPUT);
  pinMode(ledPinHijau, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if(counter==0){
    digitalWrite(ledPinMerah, HIGH);
    digitalWrite(ledPinKuning, LOW);
    digitalWrite(ledPinHijau, LOW);
    counter+=1;
    previousMillis += intervalMerah;
  }
  else{
        if(counter == 1 && previousMillis - currentMillis == 0){
          digitalWrite(ledPinMerah, LOW);
          digitalWrite(ledPinKuning, HIGH);
          counter+=1;
          previousMillis += intervalKuning;
      }
        else if(counter == 2 && previousMillis - currentMillis == 0){
          digitalWrite(ledPinKuning, LOW);
          digitalWrite(ledPinHijau, HIGH);
          counter+=1;
          previousMillis += intervalHijau;
      }
        else if(counter == 3 && previousMillis - currentMillis == 0){ 
          digitalWrite(ledPinHijau, LOW);
          digitalWrite(ledPinMerah, HIGH);
          counter = 1;
          previousMillis += intervalMerah;
      }
  }
}
