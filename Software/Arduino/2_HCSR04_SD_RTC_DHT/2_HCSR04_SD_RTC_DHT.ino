
#define echoPin1 2
#define trigPin1 3
#define trigPin2 5
#define echoPin2 6
#define DHTPIN 8
#define DHTTYPE DHT22
#include "DHT.h"
#include <RTClib.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
DHT dht(DHTPIN, DHTTYPE);

int trigPin;
int duration, Sensor1, Sensor2;
File myFile;
//RTC_DS1307 rtc;

RTC_DS3231 rtc;              // Create an RTC_DS3231 object


void setup()
{ Serial.begin(9600);
  Wire.begin();  
  dht.begin();
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  digitalWrite(trigPin, LOW);


  SD.begin();
  while (!Serial);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  else {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
 // if (! rtc.isrunning()) {
   // Serial.println("RTC is NOT running!");
 // }
  Serial.print("Initializing SD card...");
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  /*Serial.begin(9600);
  Wire.begin();  
  dht.begin();
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  digitalWrite(trigPin, LOW);*/
  Serial.println("Date,Time,timestamp,duration1,duration2,temperature,humidity,speedlevel");
  myFile.println("Date,Time,timestamp,duration1,duration2,temperature,humidity,speedlevel");
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
    Sensor(trigPin2, echoPin2);
    Sensor2 = duration;
    float t = dht.readTemperature();
    float h = dht.readHumidity();

    myFile = SD.open("test1.txt", FILE_WRITE);
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
      Serial.print(k * 500);
      Serial.print(",");
      Serial.print(Sensor1);
      Serial.print(",");
      Serial.print(Sensor2);
      Serial.print(",");
      Serial.print(t);
      Serial.print(",");
      Serial.println(h);
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
      myFile.print(k * 500);
      myFile.print(",");
      myFile.print(Sensor1);
      myFile.print(",");
      myFile.print(Sensor2);
      myFile.print(",");
      myFile.print(t);
      myFile.print(",");
      myFile.println(h);



    }

    /*Serial.print(".............data collection completed............");
    myFile.print(".............data collection completed............");*/
  }
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
