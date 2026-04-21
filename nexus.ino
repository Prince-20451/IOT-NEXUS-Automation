#define BLYNK_TEMPLATE_ID "TMPL6kW7ZfmJb"
#define BLYNK_TEMPLATE_NAME "nexus"
#define BLYNK_AUTH_TOKEN "4vceRs56FKGDLIGBHDAllVbIEmWnUICG"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char ssid[] = "Prince";
char pass[] = "123456789";

#define DHTPIN D2
#define DHTTYPE DHT11

#define PIR D5
#define GREEN_LED D6
#define RED_LED D7
#define BUZZER D1

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;


void sendData() {
  int motion = digitalRead(PIR);
  float temp = dht.readTemperature();

  if (isnan(temp)) {
    Serial.println("DHT Error!");
    return;
  }

  Serial.print("Temp: ");
  Serial.println(temp);

 
  Blynk.virtualWrite(V0, temp);

  
  digitalWrite(GREEN_LED, motion);

  
  if (temp >= 28) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, HIGH);

    Blynk.virtualWrite(V1, 1);

  
    Blynk.logEvent("high_temp", "High Temperature in Server Room!");

  } else {
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER, LOW);

    Blynk.virtualWrite(V1, 0);
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(PIR, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  dht.begin();

  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  
  timer.setInterval(2000L, sendData);

  delay(5000); // PIR stabilize
}

void loop() {
  Blynk.run();
  timer.run();
}
