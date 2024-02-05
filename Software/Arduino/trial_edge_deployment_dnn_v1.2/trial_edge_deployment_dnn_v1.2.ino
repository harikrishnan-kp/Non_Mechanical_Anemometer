#define echoPin1 2
#define trigPin1 3
#define trigPin2 4
#define echoPin2 5
#define DHTPIN 13
#define DHTTYPE DHT22
#include "DHT.h"
#include "model9.h"
#define ARENA_SIZE 4096



int trigPin;
DHT dht(DHTPIN, DHTTYPE);
Eloquent::TinyML::TensorFlow::AllOpsTensorFlow<5, 1, ARENA_SIZE> tf;

int pulseDuration;
int duration1;
int duration2;
unsigned long duration;
float data[4];
long timeduration(int echopin);
void sensor(int trigPin, int echoPin);


void setup()
{
  Serial.begin(9600);
  dht.begin();
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  tf.begin(modelData);
}




void loop()
{
  //data_read();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int humidity= h*100;
  int temperature=t*100;
  sensor(trigPin1, echoPin1);
  duration1 = duration;
  sensor(trigPin2, echoPin2);
  duration2 = duration;
  float data[4] = {duration1, duration2, temperature, humidity};
  //float data[4] = {565.5,560,26.84,63.75};
  Serial.print(duration1);
  Serial.print(",");
  Serial.print(duration2);
  Serial.print(",");
  Serial.print(temperature);
  Serial.print(",");
  Serial.print(humidity);
  Serial.print(",");
  Serial.println(  tf.predict(data)  );
  delay(1000);
}



void data_read()
{
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  sensor(trigPin1, echoPin1);
  duration1 = duration;
  sensor(trigPin2, echoPin2);
  duration2 = duration;
  //float data[4] = {duration1, duration2, temperature, humidity};
  float data[4] = {565.5,560,26.84,63.75};
}


void sensor(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = timeduration(echoPin);
  delay(500);
}



// this function calculates the time difference between trigger time and echo reception time
// 745 micro seconds is the maximum posiible time on this particular hardware arrangement

long timeduration(int echopin)
{
  int state=0;
  unsigned long startTime = micros();
  while (digitalRead(echopin) != state  )
  {
    if (  micros() - startTime >= 745  )   return 0;
  }
  startTime = micros();
  while (  digitalRead(echopin) == state  )
  {
    if (  micros() - startTime >= 745  ) return 0;
  }
  return micros() - startTime;
}
