/******************
 * Orion McLain 5/7/2022
 * ECE 231 - Embedded Systems
 * 
 * Lab 5 - Ultrasound range sensor with audible and visual indications of range
 * Using ATmega328p on a breadboard powered by a battery
 * Uses 0.96" OLED display and a piezo-electric speaker
 * 
 * Specs: 
 *   -  System shall measure range to objects placed >5cm and <200cm from ultrasound sensor
 *   -  System shall display range in both cm and inches on the OLED display
 *   -  Power the system using a 9V battery
 * 
 * Much code is from lecture slides/demos
 * ***************/

#include <avr/io.h> 
#include <util/delay.h>
// #include <uart.h>
// #include <stdlib>        // defines itoa() function
#include "i2c.h"         // for OLED
#include "SSD1306.h"     // for OLED

#define TRIG PB1                // trig pin on PB1
#define ECHO PB0                // echo pin on PB0
#define RANGE_PER_CLOCK 1.098   // 1.098 cm range per clock cycle


void timer0_init(void);
void send_to_monitor(unsigned char, unsigned char, float);
void OLED_display(float distance);

int main(void){

    unsigned int tRisingEdge, tFallingEdge;   // define variables to store the rising and falling edge of the echo pulse
    unsigned int echoWidth;   // to store the echo pulse width 
    float range;

    DDRB = 1<<TRIG;        // set trig as output pin
    PORTB &= ~(1<<TRIG);   // initialize trig pin to low

    // uart_init();           // start uart
    OLED_Init();           // start OLED
    timer0_init();         // start timer

    while(1){

        TCNT0 = 0;             // load counter with 0
        PORTB |= 1<<TRIG;      // set trig pin high
        _delay_us(10);         // send trig pulse for 10 us
        PORTB &= ~(1<<TRIG);   // set trig pin low after full pulse

        // when the echo pin is set to high, find the time of the rising edge
        while((PINB & (1<<ECHO)) == 0){ 
            tRisingEdge = TCNT0; 
            }
        
        // once the echo pin is low, find the time of the falling edge
        while(!(PINB & (1<<ECHO)) == 0){ 
            tFallingEdge = TCNT0; 
            }
        
        if (tFallingEdge > tRisingEdge){
            echoWidth = tFallingEdge - tRisingEdge; 
            // send_to_monitor(tRisingEdge, tFallingEdge, range);
            range = echoWidth * RANGE_PER_CLOCK;
            if ((range > 5) & (range < 200)){
                OLED_display(range);
            }  else {
                OLED_Clear();
            }
        }
        _delay_ms(500);  // delay before looping back through
    }
    return(1);   // never reaches
}


// intialize timer0: normal mode, divide clock by 1024
void timer0_init(void){
    TCCR0A = 0;  // timer mode 1 - normal - count up
    TCCR0B = 5;  // 1024 prescaler -- divide clock by 1024
    TCNT0 = 0;   // Start the timer at 0
}

void OLED_display(float distance){
    
    OLED_GoToLine(1);
    OLED_DisplayString("Distance: ");
    OLED_DisplayNumber(10, distance, 3);
    OLED_DisplayString("cm, ");
    OLED_DisplayNumber(10, distance/2.54, 2);
    OLED_DisplayString("in");
}
    
/*
// send info to the serial monitor via the UART
void send_to_monitor(unsigned char t1, unsigned char t2, float range){
    char buffer[10]; 
    send_string("Rising edge: ");
    utoa(t1, buffer, 10);          // send delay count to comm port
    send_string(buffer);
    // send_string(" clocks; ")
    send_string(" Falling edge: ");
    utoa(t2, buffer, 10);          // send delay count to comm port
    send_string(buffer);
    // send_string(" clocks; ")

    send_string(" Echo pulse width: ");
    utoa(t2 - t1, buffer, 10);
    send_string(buffer);
    send_string(" clock pulses.      Target Range = ");
    dtostrf(range, 3, 0, buffer);             // send delay count in cm 
    send_string(buffer);
    send_string(" cm ");
    dtostrf(range/2.54, 3, 0, buffer);        // send delay count converted to inches
    send_string(buffer);
    send_string(" inch ");
    uart_send(13);   // tx carraige return
    uart_send(10);   // tx new line

}
*/
