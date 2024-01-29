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


int motor(u08 num, int8_t speed);

int main(void) {
   init();  //initialize board hardware
   int val0 = 0;
   int val1 = 0;

   //while(1){
      val0 = motor(0,-100);
      val1 = motor(1,-100);
      // print_num(val0);
      // clear_screen();
   //}
   return 0;
}

// num(0 is left and 1 is right)
// speed -100 - 100
int motor(u08 num, int8_t speed){
   //if ((num == 1 || num == 0) && (speed<= 100 && speed >= -100)){
      // conversion
      speed = floor(.3*speed + 127);
      print_num(speed);
      clear_screen();
      // set_servo(num, speed);
      return speed;
   //}else{
      //return -1;
   //}
   //return speed;
}

int gradually_inc(){
   int val = 0;
   while(1){
      motor(0,val);
      motor(1,val);
      if (val < 100){
         val++;
      }
   }
}


