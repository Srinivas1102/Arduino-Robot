
#include <Servo.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#include "LedControl.h"
const unsigned int TRIG_PIN=24;
const  int ecHO_PIN=25;
LedControl lc = LedControl(13,11,12,4); //Pin 13 = DIN, Pin 12 = CLK, Pin 11 = CS
Servo myservo; 
byte neutral_eye[8] = {B00011000,B00100100,B01000010,B10011001,B10011001,B01000010,B00100100,B00011000};
byte closed_eye[8] = {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};
                                      

// happy mouth           //part 1 
byte happy_mouth[16] = {    
                         //part 2
                          B00011000,B00011100,B00010110,B00010011,B00010001,B00010001,B00010001,B00010001,
                           B00010001,B00010001,B00010001,B00010001,B00010010,B00010110,B00011100,B00011000};
                         
                                                  
// sad mouth            //part 1
byte closed_mouth[16] = {   B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
                         //part 2
                         B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000 };

             
void setup()
{
   mp3_set_serial (Serial);  
  mp3_set_volume (15); 
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ecHO_PIN, INPUT);
  lc.shutdown(0,false);
  lc.setIntensity(0,1);
  lc.clearDisplay(0);
  lc.shutdown(1,false);
  lc.setIntensity(1,1);
  lc.clearDisplay(1);
  lc.shutdown(2,false);
  lc.setIntensity(2,1);
  lc.clearDisplay(2);
  lc.shutdown(3,false);
  lc.setIntensity(3,1);
  lc.clearDisplay(3);
 myservo.attach(9); 
  Serial.begin(9600);
  
}
void loop()
{
   digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  

 const unsigned long duration= pulseIn(ecHO_PIN, HIGH);
 int distance= duration/29/2;
Serial.println(distance);
 if(duration==0)
 {
   Serial.println("Warning: no pulse from sensor");
 } 
   else if ( distance<= 100 && distance >= 0)
   {     
    display_eyes(neutral_eye, neutral_eye);
    display_mouth(happy_mouth);
     mp3_play ();
     ser();
    delay(5000);
   }
    else{
      display_eyes(closed_eye,closed_eye);
    display_mouth(closed_mouth);
      mp3_stop();
     delay(1000); 
 }
delay(60);
}
void ser()
{
  myservo.writeMicroseconds (1500);
  delay (5000);
  myservo.write(0); 
  delay(3000);
}
void display_eyes(byte right_eye[], byte left_eye[]) {
  for(int i=0;i<8;i++) {
   lc.setRow(0,i,left_eye[i]);
   lc.setRow(1,i,right_eye[i]);
  } 
}


void display_mouth(byte mouth[]) {
  for(int i=0;i<8;i++) {
    lc.setRow(2,i,mouth[i]);
    lc.setRow(3,i,mouth[i+8]);
   
  }
}
