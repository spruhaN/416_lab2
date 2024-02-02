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

#define DIFF 10 

void motor(u08 num, int8_t speed);
// more light on one side send according/opp motor to slow down
int main(void) {
   init();  //initialize board hardware

   // set button press to 0
   // get initial light readings
   int init_left = analog(0) + DIFF;
   int init_right = analog(1) + DIFF;

   motor(0,50);
   motor(1,-50);

   int button = 0;
   int prev = 0;

   while(1){
      // flips button states between full presses 
      int curr = get_btn();
      if (curr && !prev) {
        button = 1 - button;
      }
      prev = curr;

      // get curr values
      int curr_left = analog(0);
      int curr_right = analog(1);
      int adj_motor = 5;

      // stores light adj motor
      if (curr_left > curr_right && curr_left > init_left){
         adj_motor = 0;
      }else if(curr_left < curr_right && curr_right > init_right){
         adj_motor = 1;
      }

      // if light
      if (adj_motor != 5){
         int opp = 1;
         // if button is triggered flip 3a <-> 3b
         if(button == 1){
            adj_motor = (adj_motor + 1)%2;
         }
         // changes mtor direction
         if(adj_motor ==1){
            opp = -1;
         }

         //slows down motor
         motor(adj_motor, opp * 10);
         // makes otherside quicker
         motor((adj_motor+1)%2, opp * -50);

         // print main motor and button
         lcd_cursor(0,0);
         print_num(adj_motor);
         lcd_cursor(0,1);
         print_num(button);
      }else{
         motor(0,50);
         motor(1,-50);
      }
      _delay_ms(100);
      
      clear_screen();
   }
   
   return 0;
}

void motor(u08 num, int8_t speed){
   int speed_calc = floor(.3*speed + 127);
   set_servo(num,speed_calc);
}