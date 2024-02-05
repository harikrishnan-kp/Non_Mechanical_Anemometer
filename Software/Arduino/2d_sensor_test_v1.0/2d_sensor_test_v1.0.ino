#define echoPin1 2
#define trigPin1 3
#define trigPin2 4
#define echoPin2 5
int trigPin;



int duration, Sensor1, Sensor2;
void setup() {
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  digitalWrite(trigPin, LOW);
  Serial.println("timestamp,speedlevel,duration1,duration2");
  data();
  
}

void loop()
{
}
void data()
{
  for (int k = 0; k < 10; k += 1)
  {
    Sensor(trigPin1, echoPin1);
    Sensor1 = duration;
    Sensor(trigPin2, echoPin2);
    Sensor2 = duration;
    /*Sensor(trigPin3, echoPin3);
    Sensor3 = duration;
    Sensor(trigPin4, echoPin4);
    Sensor4 = duration;
*/
    Serial.print(k * 500);
    Serial.print(",");
    Serial.print(Sensor1);
    Serial.print(",");
    Serial.println(Sensor2);
    /*Serial.print(",");
    Serial.print(Sensor3);
    Serial.print(",");
    Serial.println(Sensor4);*/

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
