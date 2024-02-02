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
void gradually_inc();
void gradually_dec();
void gradually_inc_rev();
void gradually_dec_rev();



int main(void) {
   init();  //initialize board hardware
   motor(0,0);
   motor(1,0);

   gradually_inc();
   gradually_dec();

   gradually_inc_rev();
   gradually_dec_rev();

   return 0;
}

// num(0 is left and 1 is right)
// speed -100 - 100
// where - for 
void motor(u08 num, int8_t speed){
   int speed_calc = floor(.3*speed + 127);
   set_servo(num,speed_calc);
   if (num == 0){
      lcd_cursor(0,0);
      print_num(speed_calc);
   }
}

// gradually spins the motors to full speed forward
void gradually_inc(){
   int val = 0;
   motor(0,0);
   while(val < 100){
      motor(0,val);
      motor(1,-1 * val);
      val+=1;
      _delay_ms(100);
      clear_screen();
   }
}

// gradually slows the motors to a stop
void gradually_dec(){
   int val = 100;
   while(val > 0){
      motor(0,val);
      motor(1,-1 * val);
      val-=1;
      _delay_ms(100);
      clear_screen();
   }
}
// does the same in the reverse motor direction and continuously repeats

// gradually spins the motors to full speed forward
void gradually_inc_rev(){
   int val = 0;
   motor(0,0);
   while(val < 100){
      //print_num(val);
      motor(0,-1 * val);
      motor(1,val);
      val+=1;
      _delay_ms(100);
      clear_screen();
   }
}

// gradually slows the motors to a stop
void gradually_dec_rev(){
   int val = 100;
   while(val > 0){
      //print_num(val);
      motor(0,-1 * val);
      motor(1,val);
      val-=1;
      _delay_ms(100);
      clear_screen();
   }
}
// while the program is running, print the motor speed on the screen



