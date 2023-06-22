/**************
 * ECE 231 Lab 4 Changing LED intensity using an 
 * ATmega328p on a breadboard powered by a battery
 * 
 * Orion McLain 4/21/2022
 * 
 * For this lab we will design and build an embedded system
 * that causes an LED to glow at three different brightnesses
 * 
 * 2 button switches + LED
 *   -  When no button is pressed, LED is off
 *   -  When 1st button is pressed, LED glows at "dim" brightness
 *   -  When 2nd button is pressed, LED glows at "medium" brightness
 *   -  When both buttons are pressed, LED glows at "full" brightness
 * 
 * System is to be powered by a 9V battery
***************/
#include <avr/io.h>
#include <util/delay.h>
#define MYDELAY 1000

int main(void){
    
    DDRB = 1<<PB3;  // set LED on PB3
    DDRD = 1<<PD0 | 1<<PD1;  // button 1 on PD0, button 2 on PD1
    PORTD = 1<<PD0 | 1<<PD1;  // Set pullup on PD0 and PD5

    // initialize timer0 for FASTPWM, /64 prescaler
    TCCR1A = 0x81;    
    TCCR1B = 0x03;     

    while(1){
        while (PIND & (1<<PIND0 | 1<<PIND1) == 0){    // both buttons pressed, "full brightness"
            
            OCR0A = 230; 

        }

        while (PIND & (1<<PIND0) == 0){   // first button pressed, "dim brightness"
            
            OCR0A = 32;

        }

        while (PIND & (1<<PIND1) == 0){   // second button pressed, "medium brightness"
            
            OCR0A = 128; 

        }
        OCR0A = 255;
    }

    return 0;
}