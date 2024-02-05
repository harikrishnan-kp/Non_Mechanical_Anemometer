#define echoPin1 2
#define trigPin1 3
#define trigPin2 4
#define echoPin2 5
#define DHTPIN 9
#define DHTTYPE DHT22
const int Reed_pin = 6;

#include "DHT.h"
#include <RTClib.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>


int trigPin;
DHT dht(DHTPIN, DHTTYPE);
File myFile;
RTC_DS1307 rtc;


int pulseDuration;
int duration1;
int duration2;
unsigned long duration;
unsigned long previousTime = 0;
volatile int count = 0;
float ws = 0;
long timeduration(int echopin);
void sensor(int trigPin, int echoPin);



void setup()
{
  Serial.begin(9600);
  dht.begin();
  SD.begin();

  while (!Serial);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  else {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(Reed_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Reed_pin), wind_count, FALLING);
  myFile.println("Date,Time,duration1,duration2,temperature,humidity,windcount,output");
  Serial.println("Date,Time,duration1,duration2,temperature,humidity,windcount,output");

}


void loop()
{

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  sensor(trigPin1, echoPin1);
  duration1 = duration;
  sensor(trigPin2, echoPin2);
  duration2 = duration;

  if (previousTime > millis())
    previousTime = 0;

  else if ((millis() - previousTime) > 500)
  {
    previousTime = millis();
    count = 0;
    ws = 0;

  }

  myFile = SD.open("wind.txt", FILE_WRITE);
  if (myFile) {

    tmElements_t tm;

    if (RTC.read(tm)) {

      Serial.print(tm.Day);
      Serial.print('/');
      Serial.print(tm.Month);
      Serial.print('/');
      Serial.print(tmYearToCalendar(tm.Year));
      Serial.print(",");
      Serial.print(tm.Hour);
      Serial.print(":");
      Serial.print(tm.Minute);
      Serial.print(":");
      Serial.print(tm.Second);
      Serial.print(',');
      Serial.print(duration1);
      Serial.print(",");
      Serial.print(duration2);
      Serial.print(",");
      Serial.print(temperature);
      Serial.print(",");
      Serial.print(humidity);
      Serial.print(",");
      Serial.println(ws);

      myFile.print(tm.Day);
      myFile.print('/');
      myFile.print(tm.Month);
      myFile.print('/');
      myFile.print(tmYearToCalendar(tm.Year));
      myFile.print(",");
      myFile.print(tm.Hour);
      myFile.print(":");
      myFile.print(tm.Minute);
      myFile.print(":");
      myFile.print(tm.Second);
      myFile.print(',');
      myFile.print(duration1);
      myFile.print(",");
      myFile.print(duration2);
      myFile.print(",");
      myFile.print(temperature);
      myFile.print(",");
      myFile.print(humidity);
      myFile.print(",");
      myFile.println(ws);
      myFile.close();
     // delay(500);
    }
    else {
      if (RTC.chipPresent()) {
        Serial.println("The DS1307 is stopped.  Please run the SetTime");
        Serial.println("example to initialize the time and begin running.");
        Serial.println();
      } else {
        Serial.println("DS1307 read error!  Please check the circuitry.");
        Serial.println();
      }
      delay(500);
    }
  }
}



void data_read()
{
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  sensor(trigPin1, echoPin1);
  duration1 = duration;
  sensor(trigPin2, echoPin2);
  duration2 = duration;
}


void sensor(int trigPin, int echoPin)
{
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
}

void wind_count()
{
  count++;
  ws = count * (2.4 / 2);
}
