/*********
 * ECE 231 LAB 3 Thermometer Sensor + Display in F and C
 * Orion McLain 
 * Last updated 4/3/2022
 * 
 * This code will work with a arduino circuit with a temperature sensor, 4 digit 7 segment display, and a button
 * 
 * When the circuit is on, the 7 segment display will show the temperature of the room in degrees farenheit
 * If/when the button is pressed, the 7 segment display will switch to showing the temperature in degrees celcius
 * 
 * Part 1 -- send to monitor using UART
 * Part 2 -- display on the 7 segment display 
 * *********/ 

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

#define Dig1 1  //  PB1
#define Dig2 2  //  PB2
#define Dig3 3  //  PB3
#define Dig4 4  //  PB4
#define a 0  //  PC0
#define b 1  //  PC1
#define c 2  //  PC2
#define d 3  //  PC3
#define e 4  //  PD4
#define f 5  //  PD5
#define g 6  //  PD6
#define decimal 7  // PD7 
#define button 2 // button on PD2
#define farenheit 10 // index in ledDigits[]
#define celcius 11 // index in ledDigits[]

int main(void){
    DDRB = 0xFF; // Digit enable pins 
    DDRC = 0x0F; // Segments a-d on pins PC0-PC3 
    DDRD = 0xF0; // Semgments e-g and dp on pins PD4-PD7

    PORTD = 1<<button;  // Set internal pullup resistor on D2 for push button

    unsigned char ledDigits[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x71, 0x39};  // 0-9, then F at 10, C at 11
    unsigned char digit1, digit2, digit3; // temp display digits
    unsigned int digitalValue; // digital reading from the TM36
    unsigned int tempC; // temperature in celcius
    unsigned int tempF; // temperature in farenheit

    ADMUX = 0x45;   // set ADC for Vref = 5V and select input ADC5 (A5) 
    ADCSRA = 0x87;   // enable ADC and set speed to 125 KHz

    while(1){
        // read temperature sensor -> get voltage -> calculate temp
        ADCSRA |= (1<<ADSC);  // start up ADC
        while ((ADCSRA & (1<<ADIF)) ==0);   // once previous line is done converting
            digitalValue = ADCL | (ADCH<<8);  // read the ADC digital value
        
        tempC = digitalValue*0.4883 - 50;  // use digitalValue to calculate degrees in celcius
        

        if((PIND & (1<<button)) == 0){ // when button is pressed, display in Celsius
            unsigned int displayC = tempC*10;  // shift tempC left one decimal place to calculate digits
            
            digit1 = displayC/100;  // leftmost digit is "hundreds" place
            digit2 = (displayC/10)%10;  // middle digit is "tens" place 
            digit3 = displayC%10; // right digit is "ones" place

            PORTC = ledDigits[digit1];
            PORTD = ledDigits[digit1];
            PORTB =~ (1<<Dig1);  // enable digit1 
            _delay_ms(1);

            PORTC = ledDigits[digit2];
            PORTD = ledDigits[digit2]| (1<<decimal);
            PORTB =~ (1<<Dig2);  // enable digit2
            _delay_ms(1);

            PORTC = ledDigits[digit3];
            PORTD = ledDigits[digit3];
            PORTB =~ (1<<Dig3);  // enable digit 3
            _delay_ms(1);

            PORTC = ledDigits[celcius];
            PORTD = ledDigits[celcius];
            PORTB =~ (1<<Dig4);  // enable digit 4
            _delay_ms(1);
        }      
    
        else {    // otherwise button is not pressed, display in Farenheit
            tempF = (tempC*1.8) + 32.0; // calculate tempF from tempC, scale up 10 to display
            unsigned int displayF = tempF*10;

            digit1 = displayF/100;  // leftmost digit is "hundreds" place
            digit2 = (displayF/10)%10;  // middle digit is "tens" place 
            digit3 = displayF%10; // right digit is "ones" place
            
            PORTC = ledDigits[digit1];
            PORTD = ledDigits[digit1];
            PORTB =~ (1<<Dig1);
            _delay_ms(1);

            PORTC = ledDigits[digit2];
            PORTD = ledDigits[digit2] | (1<<decimal);
            PORTB =~ (1<<Dig2);
            _delay_ms(1);

            PORTC = ledDigits[digit3];
            PORTD = ledDigits[digit3];
            PORTB =~ (1<<Dig3);
            _delay_ms(1);

            PORTC = ledDigits[farenheit];
            PORTD = ledDigits[farenheit];
            PORTB =~ (1<<Dig4);
            _delay_ms(1);
        }

    }
    return(0);

}
 



