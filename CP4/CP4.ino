#include<ArduinoJson.h>
#include<DHT.h>
#include<Servo.h>

#define DHTPIN 10
#define DHTTYPE 11
#define ServoPin 9
#define LDRPIN A0

DHT dht(DHTPIN, DHTTYPE);
Servo myServo;

void setup() {
  myServo.attach(ServoPin);
  pinMode(ServoPin, OUTPUT);
  dht.begin();
  Serial.begin(9600);

}

void loop() {
  int tempC = dht.readTemperature();
  int umi = dht.readHumidity();
  int valorLDR = analogRead(LDRPIN);
  int tempF = (tempC * 1.8) + 32;

  StaticJsonDocument<100>json;

  json ["Temperatura"] = tempF;
  json ["Umidade"] = umi;
  json ["LDR"] = valorLDR;

  serializeJson (json, Serial);
  
  

  Serial.println();
  delay(3000);

  if(Serial.available()>0){
    char comando = Serial.read();
    if(comando == 'L'){
      myServo.write(180);
    }else if(comando == 'R'){
      myServo.write(0);
    }else if(comando == 'M'){
      myServo.write(90);
    }
  }
}

