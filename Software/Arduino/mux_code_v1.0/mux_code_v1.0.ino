#define S1 7
#define S2 6

void setup(){pinMode(4,OUTPUT);pinMode(5,OUTPUT);pinMode(6,OUTPUT);pinMode(7,OUTPUT);}


void loop()
{
tone(4,40000);digitalWrite(5,LOW); // setting the transmission
digitalWrite(S1,LOW);digitalWrite(S2,LOW);   // X axis activated +X direction

//delay(5000);
//digitalWrite(S1,LOW);digitalWrite(S2,HIGH);  // X axis activated -X direction

//delay(5000);
//digitalWrite(S1,HIGH);digitalWrite(S2,LOW);  // Y axis activated +Y direction

//delay(5000);
//digitalWrite(S1,HIGH);digitalWrite(S2,HIGH); // Y axis activated -Y direction
}
