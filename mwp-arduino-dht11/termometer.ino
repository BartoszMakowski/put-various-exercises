#include "DHT.h"

#define DHTTYPE DHT11
const int LED1 = 8;
const int LED2 = 9;
const int LED3 = 10;
const int BEEP = 11;

const int BUTTON = 7;
const int DHT_DATA = 2;
int F;
float humidity, temp;
bool beep_status;
DHT dht(DHT_DATA, DHTTYPE);

void setup() {
  pinMode(LED1, OUTPUT); 
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(BEEP, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(BEEP, LOW);
  
  pinMode(BUTTON, INPUT);
  F=0;
  beep_status=0;
  dht.begin();
  Serial.begin(9600);
}

void loop() {
  if (F==0){ //
    if (digitalRead(BUTTON)){ // PRZYCISK - ?
      digitalWrite(LED1, HIGH); // LED1 - ON
      F = 1;      
    }
  }
  if (F==1){
    humidity = dht.readHumidity(); // mierz_wilgotnosc()
    Serial.println("\n");
    Serial.println(humidity);
    if (humidity >=20 and humidity <= 95){ // HUMIDITY_OK ?
       digitalWrite(LED2, HIGH); // LED2 - ON
       F = 2;      
    }
    delay(250);    
  }
  if (F==2){
    temp = dht.readTemperature(); // mierz_temperature()
    if (temp >=0 and temp <= 50){ // TEMP_OK ?
       digitalWrite(LED3, HIGH); // LED3 - ON
       F = 3;      
    }
    delay(250);    
  }
  if (F==3){
    delay(300);
    beep_status = !beep_status;
    digitalWrite(BEEP, beep_status);  // BEEP - ON->OFF/OFF->ON
    if (!beep_status) {
      F = 4;      
    }
    delay(250); 
  }
  if (F==4){
    Serial.write("Temperatura: ");  // wypisywanie pomiarow
    Serial.print(temp);
    Serial.write("Wilgotnosc: ");
    Serial.print(humidity);
    digitalWrite(LED1, LOW); // LED1 - OFF
    digitalWrite(LED2, LOW); // LED2 - OFF
    digitalWrite(LED3, LOW); // LED3 - OFF
    F = 0;
    delay(250);
  }
  Serial.write("\nAktualny etap: ");  // dane diagnostyczne
  Serial.print(F);
  delay(500); 
}
