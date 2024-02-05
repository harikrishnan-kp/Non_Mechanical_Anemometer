const int Reed_pin = 2;
unsigned long previousTime = 0;
volatile int count = 0;
float ws=0; 

void setup()
{
  Serial.begin(9600);
  pinMode(Reed_pin, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(Reed_pin), wind_count, FALLING);

}





/* 
 The following loop prints the cumulated value of the interrupts occured
 during a time duration of half a second ( 500 milli seconds ) and also
 resets the counting function and value variable to zero. "count" is the
 counting function and "ws" is the value variable.
*/

void loop()
{
  if(previousTime > millis())
  previousTime = 0;
  
  else if ((millis() - previousTime) > 500)
  {
    previousTime = millis();
    Serial.println(ws);
    count=0;
    ws =0;

  } 
}





/*
  This function is the ISR interrupt service routine function
  which will be executed whenever an interrupt event occurs.
  In this case the reed switch  inside the cup anemometer will be 
  switched on frequently during wind. Interrupt pin is set to "pull up" mode,
  so when ever the reed switch is closed the voltage will drop. So the interrupt
  function is set to read a falling voltage and this function counts the no. of 
  interrupt events and cumulated value is stored in the "ws" variable. To convert the
  count into actual wind speed it is multiplied by 2.4 (km/hr). Since the this
  2.4 convertion factor is for 1 count per second.Here our count timing is half a second.
  so we take half of the final value.ie, "ws = count*(2.4/2)"
*/

void wind_count()
{
    count++;
    ws = count*(2.4/2);      
}
