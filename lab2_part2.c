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

int main(void) {
   init();  //initialize board hardware

   // set button press to 0
   // get initial light readings
   int init_left = analog(0) + DIFF;
   int init_right = analog(1) + DIFF;
   motor(0,0);
   motor(1,0);
   int button = 0;
   int prev = 0;

   while(1){
      int curr = get_btn();
      if (curr && !prev) {
        button = 1 - button;
      }
      prev = curr;

      // get curr values
      int motor_adj = -1;
      int curr_left = analog(0);
      int curr_right = analog(1);
      int main_motor = 5;

      // if curr light on either side is >> store the one which is larger then move
      if (curr_left > curr_right && curr_left > init_left){
         main_motor = 0;
      }else if(curr_left < curr_right && curr_right > init_right){
         main_motor = 1;
      }
      if (main_motor != 5){
         int opp = 1;
         
         if(button == 1){
            main_motor = (main_motor + 1)%2;
         }
         if(main_motor ==1){
            opp = -1;
         }
         motor(main_motor, opp * 100);
         motor((main_motor+1)%2, opp * -40);
         lcd_cursor(0,0);
         print_num(main_motor);
      }else{
         motor(0,0);
         motor(1,0);
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