/*
  This code should work to get warning cross the buzzer when something be closer than 0.5 meter
  Circuit is ultrasonic sensor and buzzer +5v and Arduino uno is used
  a_atef45@yahoo.com
  www.zerosnones.net
  +201153300223
*/
// Define pins for ultrasonic and buzzer

#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
int const trigPin = D10;
int const echoPin = D11;
long duration, distance; 


void setup()
{
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT); // trig pin will have pulses output
  pinMode(echoPin, INPUT); // echo pin should be input to get pulse width
 mp3_set_serial (Serial); //set Serial for DFPlayer-mini mp3 module 
  mp3_set_volume (15); // buzz pin is output to control buzzering
}

void loop()
{
  // Duration will be the input pulse width and distance will be the distance to the obstacle in centimeters
 digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
//Calculate the distance (in cm) based on the speed of sound.
distance = duration/58.2;
Serial.println(distance);
//Delay 50ms before next reading.
delay(50);
  // if distance less than 0.5 meter and more than 0 (0 or less means over range) 
    if (distance <= 50 && distance >= 0) {
        mp3_play ();
  delay (195000);
      
    } else {
     mp3_stop();
     delay(1000); 
      
    }
    // Waiting 60 ms won't hurt any one
    delay(60);
}
