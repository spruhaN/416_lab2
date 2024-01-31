// Name: Sarah Hallam, Aiden Jacob, and Spruha Nayak
// Assignment: Lab 2 part 
// Description: 

#include "globals.h"
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>


int main(void) {
   init();  //initialize board hardware

   // large error large correction
   // small error small correction
   while(1){
      // get left light value
      // get right light value 
      // if left light < light_min move left
      // if right light < light_min move right 
   }

   uint16_t position = qtr.readLineBlack(sensorValues);
   int error = 3500 - position;

   float Kp = 0.05;
   float Ki = 0.00001;
   float Kd = 0.8;
   int lastError = 0;

   int P;
   int I;
   int D;

   while(1){
      P = error;
      I = error + I;
      D  = error - lastError;
      lastError = error; 

      int motorSpeedChange = P*Kp  + I*Ki + D*Kd;
      int motorSpeedA = 100 + motorSpeedChange;
      int motorSpeedB  = 100 - motorSpeedChange;

      if (motorSpeedA > 125) {
         motorSpeedA =  125;
      }
      if (motorSpeedB > 125) {
         motorSpeedB = 125;
      }
      if (motorSpeedA < -75) {
         motorSpeedA = -75;
      }
      if (motorSpeedB < -75)  {
         motorSpeedB = -75;
      }
      motor(motorSpeedA, motorSpeedB);
   }
   return 0;
}