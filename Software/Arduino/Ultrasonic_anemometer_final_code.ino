#include <NRF52_MBED_TimerInterrupt.h>
#include "NRF52_MBED_ISR_Timer.h"
#include "nRF52_MBED_PWM.h"

#include "RTClib.h"

#include <SPI.h>
#include <SD.h>

#define TIMER_INTERRUPT_DEBUG         0
#define _TIMERINTERRUPT_LOGLEVEL_     1

#define HW_TIMER_INTERVAL_MS          1
#define TIMER_INTERVAL_1S             1075L



#define sensor_select1                7
#define sensor_select2                8

#define Receiver_pin                  2
#define transimitter_pin              3
#define frequency                     40000

#define max_buffer_size               4
uint8_t buffer_index = 0;

uint16_t time_of_travel[max_buffer_size] = {0};


float dutyCycle = 50.0f;

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

mbed::PwmOut* pwm   = NULL;

RTC_DS1307 rtc;

File myFile;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("starting program");
  pinMode(transimitter_pin, OUTPUT);

  pinMode(Receiver_pin, INPUT_PULLUP);

  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  digitalWrite(7, A);
  digitalWrite(8, B);

  Serial.print("Initializing RTC...");
  if (! rtc.begin()) {
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

  attachInterrupt(digitalPinToInterrupt(Receiver_pin), wind_count, FALLING);

  ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_MS * 1000, TimerHandler);
  signal_start_time = micros();

  setPWM(pwm, transimitter_pin, frequency, dutyCycle);

  ISR_Timer.setInterval(TIMER_INTERVAL_1S,  ISR_Timer_Interrupt);
}



void loop() {
  if (timerFlag)
  {
    DateTime time = rtc.now();
    Time = time.timestamp(DateTime::TIMESTAMP_FULL);
    timerFlag = false;
    if (signal_receive_time < signal_start_time)
    {
      for (uint8_t i = 0; i < max_buffer_size; i++)
      {
        time_of_travel[i] = 0;
      }
      buffer_index = max_buffer_size;
      A = LOW; B = LOW;
      digitalWrite(7, A);
      digitalWrite(8, B);
    }
    else
    {
      time_of_travel[buffer_index] = signal_receive_time - signal_start_time;
      buffer_index = buffer_index + 1;
      chip_select();
    }
    if (buffer_index == max_buffer_size)
    {
      for (uint8_t i = 0; i < max_buffer_size; i++)
      {
        Serial.print(String(time_of_travel[i]) + ",");
      }
      Serial.print(Time);
      Serial.println("");
      buffer_index = 0;
    }
    status_flag = true;
    signal_start_time = micros();
    setPWM(pwm, transimitter_pin, frequency, dutyCycle);
    ITimer.restartTimer();
  }
}




void wind_count()
{
  if (status_flag == true)
  {
    signal_receive_time = micros();
    status_flag = false;
  }
  count++;
}

void TimerHandler()
{
  ISR_Timer.run();

}

void ISR_Timer_Interrupt()
{
  stopPWM(pwm, transimitter_pin);
  ITimer.stopTimer();
  pulse = count;
  count = 0;
  timerFlag = true;

}
void chip_select() {
  //selecting transceivers for next transmission and reception
  //need to examine the if else ladder.need clarification of its working and check error possibilities
  // CHECK POSSIBILITY of using comma separator
  if (A == LOW && B == LOW) {
    A = LOW;
    B = HIGH;
  }
  else if (A == LOW && B == HIGH) {
    A = HIGH;
    B = LOW;
  }
  else if (A == HIGH && B == LOW) {
    A = HIGH;
    B = HIGH;
  }
  else {
    A = LOW;
    B = LOW;
  }
  digitalWrite(7, A);
  digitalWrite(8, B);
}
