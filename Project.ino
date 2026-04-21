#include <DHT.h>

#define DHTPIN D2
#define DHTTYPE DHT11

#define PIR D5
#define GREEN_LED D6
#define RED_LED D7
#define BUZZER D1

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  pinMode(PIR, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // 🔴 Force everything OFF at start
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  dht.begin();

  // 🧠 Give PIR time to stabilize
  delay(5000);
}

void loop() {
  int motion = digitalRead(PIR);
  float temp = dht.readTemperature();

  // Handle DHT error
  if (isnan(temp)) {
    Serial.println("DHT Error!");
    return;
  }

  Serial.print("Motion: ");
  Serial.print(motion);
  Serial.print(" Temp: ");
  Serial.println(temp);

  // 🟢 Motion → Green LED
  if (motion == LOW) {
    digitalWrite(GREEN_LED, LOW);
  } else {
    digitalWrite(GREEN_LED, HIGH);
  }

  // 🔴 High Temp → Red LED + Buzzer
  if (temp >= 26) {
    digitalWrite(RED_LED, HIGH);

    // ⚠️ Try ONE of these depending on your buzzer
    digitalWrite(BUZZER, HIGH);  // if normal
    // digitalWrite(BUZZER, LOW); // if inverted (most likely for your module)

  } else {
    digitalWrite(RED_LED, LOW);

    digitalWrite(BUZZER, LOW);   // OFF
    // digitalWrite(BUZZER, HIGH); // if inverted
  }

  delay(2000);
}