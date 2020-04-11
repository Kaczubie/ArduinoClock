#include <virtuabotixRTC.h> //Library used
#include "SevSeg.h"

SevSeg sevseg; //Initiate a seven segment controller object
virtuabotixRTC myRTC(6, 7, 8); //If you change the wiring change the pins here also
int menu = 0;
int time_pressed = 0;
int time_pressed_up = 0;
int time_pressed_down = 0;
int loop_counter;
int hour = 0;
int minute = 0;
void setup() {
   myRTC.setDS1302Time(15, 01, 21, 7, 14, 1, 2018); //Here you write your actual time/date as shown above 
  Serial.begin(9600);
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {A0, A1, A2, 9, 10, 11, 12, 13};
  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(70);
  // Set the current date, and time in the following format:
   // seconds, minutes, hours, day of the week, day of the month, month, year
 pinMode(A3,INPUT_PULLUP);
 pinMode(A4,INPUT_PULLUP); 
 pinMode(A5,INPUT_PULLUP); 
  }

void loop() {
  loop_counter +=1;
  if (loop_counter == 100){
    loop_counter =0;
    checkMenuButton();
  }

  if (menu == 0){
    dispTime();
  }
  else if (menu == 1){
    dispMin();
  }
   else if (menu == 2){
    
    dispHour();
  }
  else if (menu > 2){
    dispTime();
    menu = 0;
  }
}
void dispTime(){
  myRTC.updateTime();
  sevseg.setNumber(myRTC.hours*100+myRTC.minutes, 2);
  sevseg.refreshDisplay(); // Must run repeatedly

}


void dispMin(){
  int i = 0;
  myRTC.updateTime();
  minute = myRTC.minutes;
  for( i = 0; i < 1000; i++){
    checkMenuButton();
    checkButtonMinute();
    sevseg.setNumber(myRTC.hours*100+myRTC.minutes, 2);
    sevseg.refreshDisplay(); // Must run repeatedly
  }
  for( i = 0; i < 1000; i++){
    checkMenuButton();
    checkButtonMinute();
    sevseg.blank();
    sevseg.refreshDisplay(); // Must run repeatedly
  }
}
void dispHour(){
  int i = 0;
  myRTC.updateTime();
  hour = myRTC.hours;
  for( i = 0; i < 1000; i++){
    checkMenuButton();
    checkButtonHour();
    sevseg.setNumber(myRTC.hours*100+myRTC.minutes, 2);
    sevseg.refreshDisplay(); // Must run repeatedly
  }
  for( i = 0; i < 1000; i++){
    checkMenuButton();
    checkButtonHour();
    
   sevseg.setNumber(myRTC.minutes);
   sevseg.refreshDisplay(); // Must run repeatedly
  }
}
void checkMenuButton(){
  if(!digitalRead(A3))
  {
   time_pressed=+1;
  }
  else if (time_pressed > 0)
  {
    menu += 1;
    time_pressed = 0;
  }
  else{
    time_pressed = 0;
  }
}
void checkButtonHour(){
  if(!digitalRead(A4))
  {
   time_pressed_up=+1;
  }
  else if (time_pressed_up > 0)
  {
    hour += 1;
    if (hour > 23){
      hour = 0;
    }
    myRTC.setDS1302Time(0, myRTC.minutes, hour, 0, 0, 0, 0);
    time_pressed_up = 0;
  }
  else{
    time_pressed_up = 0;
  }
    if(!digitalRead(A5))
  {
   time_pressed_down=+1;
  }
  else if (time_pressed_down > 0)
  {
    
    if (hour == 0){
      hour = 23;
    }
    else{
      hour -= 1;
    }
    myRTC.setDS1302Time(0, myRTC.minutes, hour, 0, 0, 0, 0);
    time_pressed_down = 0;
  }
  else{
    time_pressed_down = 0;
  }
}
void checkButtonMinute(){
   
  if(!digitalRead(A4))
  {
   time_pressed_up=+1;
  }
  else if (time_pressed_up > 0)
  {
    minute += 1;
    if (minute > 59){
      minute = 0;
    }
    myRTC.setDS1302Time(0, minute, myRTC.hours, 0, 0, 0, 0);
    time_pressed_up = 0;
  }
  else{
    time_pressed_up = 0;
  }
   if(!digitalRead(A5))
  {
   time_pressed_down=+1;
  }
  else if (time_pressed_down > 0)
  {
    
    if (minute == 0){
      minute = 59;
    }
    else{
      minute -= 1;
    }
    myRTC.setDS1302Time(0, minute, myRTC.hours, 0, 0, 0, 0);
    time_pressed_down = 0;
  }
  else{
    time_pressed_down = 0;
  }
}
