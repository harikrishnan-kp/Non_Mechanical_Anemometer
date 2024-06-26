#include <math.h>
#include <NRF52_MBED_TimerInterrupt.h>
#include "NRF52_MBED_ISR_Timer.h"
#include "nRF52_MBED_PWM.h"
#include "RTClib.h"
#include <SPI.h>
#include <SD.h>

//debug and log levels for the timer interrupt library.
#define TIMER_INTERRUPT_DEBUG         0
#define _TIMERINTERRUPT_LOGLEVEL_     1


//hardware timer intervals.
#define HW_TIMER_INTERVAL_MS          1
#define TIMER_INTERVAL_1S             1075L

#define sensor_select1                7
#define sensor_select2                8

#define Receiver_pin                  2
#define transimitter_pin              3
#define frequency                     40000

#define max_buffer_size               4
uint8_t buffer_index = 0;
uint16_t time_of_travel[max_buffer_size] ;

float dutyCycle = 50.0f;
//Flags for handling the timer interrupt and status of measurements.
volatile bool timerFlag = false;
volatile bool status_flag = true;

volatile uint16_t count = 0;
volatile uint64_t signal_start_time = 0;
volatile uint64_t signal_receive_time = 0;



uint16_t pulse = 0;
// chip select
uint8_t A = LOW, B = LOW;
String Time;

NRF52_MBED_Timer ITimer(NRF_TIMER_2);
NRF52_MBED_ISRTimer ISR_Timer;

mbed::PwmOut* pwm = NULL;

RTC_DS1307 rtc;

File myFile;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Starting program");
  pinMode(transimitter_pin, OUTPUT);
  pinMode(Receiver_pin, INPUT_PULLUP);
  pinMode(sensor_select1, OUTPUT);
  pinMode(sensor_select2, OUTPUT);
  digitalWrite(sensor_select1, A);
  digitalWrite(sensor_select2, B);

  Serial.print("Initializing RTC...");
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1);
  }
  Serial.println("RTC initialization done.");

  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("SD card initialization failed!");
    while (1);
  }
  Serial.println("SD card initialization done.");
  //Serial.println("Date,Tns,Tsn,Tew,Twe,Vx,Vy,Vx2,Vy2,Vwind");
  Serial.println("Date,Tns,Tsn,Tew,Twe,Vwind,Direction");

  attachInterrupt(digitalPinToInterrupt(Receiver_pin), wind_count, FALLING);

  ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_MS * 1000, TimerHandler);
  signal_start_time = micros();

  setPWM(pwm, transimitter_pin, frequency, dutyCycle);
  ISR_Timer.setInterval(TIMER_INTERVAL_1S, ISR_Timer_Interrupt);
}

void loop() {
  if (timerFlag) {
    DateTime time = rtc.now();
    Time = time.timestamp(DateTime::TIMESTAMP_FULL);
    timerFlag = false;

    if (signal_receive_time < signal_start_time) {
      memset(time_of_travel, 0, sizeof(time_of_travel));
      buffer_index = max_buffer_size;
      A = LOW;
      B = LOW;
      digitalWrite(sensor_select1, A);
      digitalWrite(sensor_select2, B);
    } else {
      time_of_travel[buffer_index] = signal_receive_time - signal_start_time;
      buffer_index++;
      chip_select();
    }

    if (buffer_index == max_buffer_size) {
      myFile = SD.open("data.txt", FILE_WRITE);
      myFile.print(Time);
      myFile.print(",");
      Serial.print(Time);
      Serial.print(",");

      if (myFile) {
        
        //time duration 
        
        for (int i = 0; i < max_buffer_size; i++) {
          Serial.print(time_of_travel[i]);
          Serial.print(",");
          myFile.print(time_of_travel[i]);
          myFile.print(",");
          
        }
        //Velocity in X direction

        float Vx = 100000.0 * (float)(time_of_travel[0] - time_of_travel[1]) / (float)(time_of_travel[0] * time_of_travel[1]);
        /*Serial.print(Vx, 10);
        Serial.print(",");*/
        


        //Velocity in Y direction

        float Vy = 100000.0 * (float)(time_of_travel[2] - time_of_travel[3]) / (float)(time_of_travel[2] * time_of_travel[3]);
       /* Serial.print(Vy, 10);
        Serial.print(",");*/

        //Square value of Vx and Vy

        float Vx2 = Vx * Vx;
        float Vy2 = Vy * Vy;
        /*Serial.print(Vx2,10);
        Serial.print(",");
        Serial.print(Vy2,10);
        Serial.print(",");*/

        //Wind Velocity calculation(Square root of Vx2+Vy2)

        float Vwind=sqrt(Vx2+Vy2);
        Serial.print(Vwind,8);
        Serial.print(",");
        myFile.print(Vwind,8);
        myFile.print(",");

        //wind direction (arctan(Vy/Vx) in radian)
        float Vdirection=atan(Vy/Vx);
        //Serial.print(Vdirection,8);

        //wind direction in degrees(Vdirection * RAD_TO_DEG;).  conversion needed.
         float Direction_deg = Vdirection * RAD_TO_DEG;
         
         Serial.print(Direction_deg,8);


        myFile.println();
        Serial.println();
        myFile.close();
      } else {
        Serial.println("Error opening file for writing");
      }
      buffer_index = 0;
    }

    status_flag = true;
    signal_start_time = micros();
    setPWM(pwm, transimitter_pin, frequency, dutyCycle);
    ITimer.restartTimer();
  }
}

void wind_count() {
  if (status_flag) {
    signal_receive_time = micros();
    status_flag = false;
  }
  count++;
}

void TimerHandler() {
  ISR_Timer.run();
}

void ISR_Timer_Interrupt() {
  stopPWM(pwm, transimitter_pin);
  ITimer.stopTimer();
  pulse = count;
  count = 0;
  timerFlag = true;
}

void chip_select() {
  // Rotate through 4 states: (LOW, LOW), (LOW, HIGH), (HIGH, LOW), (HIGH, HIGH)
  if (A == LOW && B == LOW) {
    A = LOW;
    B = HIGH;
  } else if (A == LOW && B == HIGH) {
    A = HIGH;
    B = LOW;
  } else if (A == HIGH && B == LOW) {
    A = HIGH;
    B = HIGH;
  } else {
    A = LOW;
    B = LOW;
  }
  digitalWrite(sensor_select1, A);
  digitalWrite(sensor_select2, B);
}
