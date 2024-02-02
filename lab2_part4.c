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

void motor(u08 num, int8_t speed);

int constrain(int value, int minVal, int maxVal);

void updatePID(float ideal_pos, float actual_pos);

void adjustMotors(float output);

float readLineSensors();

void print_value(int val, int val2);

void handleCorner(int motor_set,int left, int right);

// NEED TO BE ALTERED!!!
float Kp = .4;
float Ki = .00001 ;
float Kd = 0;

float integral = 0.0;
float prev_err = 0.0;

int main(void) {
   init();

   while(1){
      //motor (1,0);
      //motor(0,0);

      // read sensors 
      int left_val = analog(2);
      int right_val = analog(3);
      //print_value(left_val,right_val);
      // pos
      int curr_pos = (right_val - left_val);
      float ideal_pos = 0; // ideal


      //  change motor values
      //updatePID(ideal_pos, curr_pos);
   // 6, 6
   // 163, 6
      if (left_val > 150 && (right_val > 4 && right_val < 10)){ // turn left
         //left turn, left motor on
         print_num(1);
         handleCorner(0, left_val, right_val);
      }else if (right_val > 150 && (left_val > 4 && left_val < 10)){ // turn right
         handleCorner(1, left_val, right_val);
      }else{
         updatePID(ideal_pos, curr_pos);
      }
    

   // intersection + corners
   }
}


void handleCorner(int motor_set, int left, int right){
   int opp = 1;
   int curr_left  = left;
   int curr_right = right;
   
   // black > 150 
   // white < 10
   // 1 will be passed for left turn
   if (motor_set == 1){
      print_num(7);
      opp = -1;
      while (curr_right < 150){ //?
         curr_left = analog(2);
         curr_right = analog(3);

         motor(motor_set, opp * 100);
         motor((motor_set+1)%2, 5);
      }
   }else{
      print_num(8);
      while (curr_left < 150){ //?
         curr_left = analog(2);
         curr_right = analog(3);

         motor(motor_set, opp * 100);
         motor((motor_set+1)%2, 5);
      }
   }
   clear_screen();
}


void updatePID(float ideal_pos, float actual_pos) {
   // how diff it is from 0(ideal white - white)
    float error = ideal_pos - actual_pos;
    // print_value(er);
    //not using rn
   integral = error + integral;
   float derivative  = error - prev_err;
   prev_err = error; 

    float output =( Kp * error) + (Ki * integral) + (Kd * derivative);

    adjustMotors(output);
}


// adjusting motors to calc pid val
void adjustMotors(float output) {
   //int baseSpeed = 50;
   //print_value(output,0);
   int left_motor = 20 - output;
   int right_motor = -20 - output;

   //print_num(output);
   //_delay_ms(100);
   // can it handle -'s ??and these are in opposite directions
   //print_value(left_motor, right_motor);
   left_motor = constrain(left_motor, 0, 100);
   right_motor = constrain(right_motor, -100, 0);

   motor(0, left_motor);
   motor(1, right_motor);
   //clear_screen();
}


int constrain(int value, int minVal, int maxVal) {
    if (value < minVal) {
        return minVal;
    } else if (value > maxVal) {
        return maxVal;
    } else {
        return value;
    }
}

void motor(u08 num, int8_t speed){
   int speed_calc = floor(.3*speed + 127);
   set_servo(num,speed_calc);
}

void print_value(int val, int val2){
   char buffer [33];
   char buffer2 [33];
   itoa(val, buffer, 10);
   itoa(val2, buffer2, 10);
   strcat(buffer, ". ");
   strcat(buffer2, ". ");
   lcd_cursor(0,0);
   print_string(buffer);
   lcd_cursor(0,1);
   print_string(buffer2);
   //_delay_ms(1000);
   clear_screen();
}