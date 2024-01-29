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

   while(1){
      set_servo(0,127);
      set_servo(1,127);
      _delay_ms(100);
      int pin0 = analog(0);
      int pin1 = analog(1);
      int pin2 = analog(2);
      int pin3 = analog(3);
      lcd_cursor(0,0);
      print_num(pin0);
      lcd_cursor(0,1);
      print_num(pin1);
      lcd_cursor(5,0);
      print_num(pin2);
      lcd_cursor(5,1);
      print_num(pin3);
      _delay_ms(1000);
      clear_screen();
      // int pin2 = analog(2);
      // int pin3 = analog(3);
   }
   
   return 0;
}