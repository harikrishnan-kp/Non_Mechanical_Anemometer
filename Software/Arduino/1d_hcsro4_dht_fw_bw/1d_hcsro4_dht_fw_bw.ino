#define echoPin1 2
#define trigPin1 3
#include "DHT.h"
#define DHTPIN 13
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

int trigPin;
int duration, Sensor1;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  digitalWrite(trigPin, LOW);
  Serial.println("timestamp,duration,temperature,humidity,speedlevel");
  data();


}

void loop()
{
}
void data()
{
  for (int k = 0; k < 1000; k += 1)
  {
    Sensor(trigPin1, echoPin1);
    Sensor1 = duration;
    float t = dht.readTemperature();
    float h = dht.readHumidity();

    Serial.print(k * 500);
    Serial.print(",");
    Serial.print(Sensor1);
    Serial.print(",");
    Serial.print(t);
    Serial.print(",");
    Serial.println(h);
  }

  Serial.print(".............data collection completed............");
}



void Sensor(int trigPin, int echoPin)
{

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  delay(500);

}
