
#include "TimerOne.h"
#include <EEPROM.h>
#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16,2);

const int buttonPin = 14;     // the number of the pushbutton pin
const int ledPin =  13;  

// variables will change:
int buttonState = 0;  

unsigned int time_100us_cnt;
unsigned char time_100us_flag;
unsigned int time_1ms_cnt;
unsigned char time_1ms_flag;
unsigned int time_10ms_cnt;
unsigned char time_10ms_flag;
unsigned int time_100ms_cnt;
unsigned char time_100ms_flag;
unsigned int time_500ms_cnt;
unsigned char time_500ms_flag;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as a n output.
  pinMode(13, OUTPUT);
  Timer1.initialize(100);                     // initialize timer1, interrupt 100 us
 // Timer1.pwm(9, 512);                       // setup pwm on pin 9, 50% duty cycle
  Timer1.attachInterrupt(interrupt_routine);  // attaches interrupt_routine() as a timer overflow interrupt
  lcd.begin();
  lcd.print("HELLO"); // print a simple message

// initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  
}

void interrupt_routine()
{
  {
  
  time_100us_cnt++; 
  time_100us_flag = 1;

  if (time_100us_cnt >= 10)
  {
    time_100us_cnt = 0;
    time_1ms_cnt++; 
    time_1ms_flag = 1;
    if (time_1ms_cnt >= 10)
    {
      time_1ms_cnt = 0;   
      time_10ms_cnt++;
          time_10ms_flag = 1;
      if (time_10ms_cnt >= 10)
        {
        time_10ms_cnt = 0;
              time_100ms_cnt++;
              time_100ms_flag = 1;
              if (time_100ms_cnt >= 5)
              {
                  time_100ms_cnt = 0;
          time_500ms_cnt++;
                  time_500ms_flag = 1;  
              }            
        }
    }
  }
}
  
}
void AppTask1ms()
{
  
}
void AppTask10ms()
{
  
}
void AppTask100ms()
{
  
}
void AppTask500ms()
{
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

// check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    //digitalWrite(ledPin, HIGH);
    digitalWrite(ledPin, LOW);
   // digitalWrite(13, digitalRead(13) ^ 1); 
  } else {
    // turn LED off:
   // digitalWrite(ledPin, LOW);
    digitalWrite(ledPin, HIGH);
   // digitalWrite(13, digitalRead(13) ^ 1); 
  }

  //digitalWrite(13, digitalRead(13) ^ 1); 
  
 // digitalWrite(13, digitalRead(13) ^ 1);  
}
void timer_task()
{
    if (time_1ms_flag)
    {
        AppTask1ms();
        time_1ms_flag = 0;
    }

    if (time_10ms_flag)
    {
        AppTask10ms();
        time_10ms_flag = 0;
    }

    if (time_100ms_flag)
    {
        AppTask100ms();
        time_100ms_flag = 0;
    }

    if (time_500ms_flag)
    {
        AppTask500ms();
        time_500ms_flag = 0;
    }

}

// the loop function runs over and over again forever
void loop()
{
  
    timer_task();            // task management
    
}
