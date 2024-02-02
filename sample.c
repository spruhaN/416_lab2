#include "globals.h"
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void motor(u08 num, int8_t speed);

int main(){
    init();

    while(1){
        // left motor positive forwards
        motor(0,0);
        // right motor negative forwards
        motor(1,0);
    }
}

void motor(u08 num, int8_t speed){
   int speed_calc = floor(.3*speed + 127);
   set_servo(num,speed_calc);
}