/*********
 * ECE 231 Embedded Systems Lab Assignment 1
 * Due 11:59 pm Sunday 2/13/22
 * 
 * Orion McLain
 * 
 * Write a program to convert & print a user input decimal number
 * into its corresponding value in the user-specified base
 *  
 * SPECIFICATIONS
 * 1. Get two numbers from user, a decimal value and a base
 * 1.1 The decimal value shall be in the range 1 to 255 
 * 1.2 The allowable bases are 16, 10, 8, and 2
 * 2. Print the decimal value and its corresponding value in the specified base
 * 3. Print a message to the user if they specify a base other than one of the allowable bases
 * 4. Use a user-defined function to convert and print the user's decimal value to base 2
 * 5. Keep running until the user enters a value of 0
 * 
 * Elements involved: printf, scanf, while(), for(), arrays, /, %
 * *********/ 

#include <stdio.h>    // need for scanf, printf
int binaryConvert(int number);
int octalConvert(int number);
int hexConvert(int number);

// main scansa and checks user input, and calls the appropriate converter function from base input
int main(){
    int num;          // variable for user number input
    int base;         // variable for user base input, set to 0 to start
    
    while(1){   // all of main in infinite loop that breaks only when user inputs a 0
    
        // ------ get user input

        printf("Please enter number & base separated by a space (enter 0 0 to quit)..  ");   // message to prompt user input
        scanf("%d %d", &num, &base);            // first scan for user input

        if(num == 0 || base == 0){      // if user inputs a 0 for either, exit
            return(1);
        }

        while(base != 2 && base != 8 && base != 10 && base != 16){  // if user enters incorrect base, ask them to re-enter
            printf("Please enter a base of either 16, 10, 8, or 2 \n");  // error message + newline
            printf("Please enter number & base separated by a space (enter 0 0 to quit)..  ");   // repeat prompt message
            scanf("%d %d", &num, &base);     // get user input again

            if(num == 0 || base == 0){      // check if user wnats to exit again
                return(1);
            }
        }

        // ------  print message for the conversion, call functions to print number

        printf("%d in base %d =  ", num, base);   // print the beginning of the response message

        if(base == 10){
            printf("%d\n", num);  // no change in base, print input num
        } 
        if(base == 2){
            binaryConvert(num);  // call binary convert function to print binary
        }
        if(base == 8){
            octalConvert(num);   // call octal convert function to print octal
        }    
        if(base == 16){
            hexConvert(num);    // call hex convert function to print hex
        }
        
    }
}

/*************
 * binary converter function to convert inputted number to binary
 * 
 * use floor and modulo division to determine values for the 8 bit binary 
 * 
 * first mod determines last digit, second mod -> second to last digit
 * USING ARRAY TO FIND DIGITS
 * 
 * once we have array of digits, loop backwards through array and print each bit
 * ************/ 

int binaryConvert(int num){
    int binary[8];   // initialize binary int to store 8 bits (max possible)
    
    // ------ store digits of binary number

    for(int i = 0; i < 8; i++){   // loop 8 times to find digits for the 8 bits
        binary[i] = (num % 2);    // store remainder in the array 
        num = num / 2;            // floor divide to move to next remainder
    }

    // ------ print converted number digit by digit, end w/ newline

    for (int i = 7; i >= 0; i--){   // loop backwards through array to print digits in order
        printf("%d", binary[i]);
    }
    printf("\n");  // newline for next num and base

    return(0);
}


/*************
 * octal converter function to convert inputted number to octal
 * 
 * use floor and modulo division to determine values for the 3 bit octal 
 * 
 * first mod determines last digit, second mod -> second to last digit
 * USING ARRAY TO FIND DIGITS
 * 
 * once we have array of digits, loop backwards through array and print each digit
 * ************/ 

int octalConvert(int num){
    int octal[3];   // initialize binary int to 8 bits, all 0
    
    // ------ find octal digits

    for(int i = 0; i < 3; i++){  
        octal[i] = (num % 8);  // add bit digit to binary return number, 10^i offsets
        num = num / 8;            // move on to next digit
    }

    // ------ print converted number digit by digit, end with newline

    for (int i = 2; i >= 0; i--){  // loop backwards to print in order
        printf("%d", octal[i]);
    }
    printf("\n");  // newline for next num and base

    return(0);
}
 
/*************
 * hex converter function to convert inputted number to hex
 * 
 * use floor and modulo division to determine values for the 2 bit octal 
 * 
 * determine and store the mod for each digit
 * 
 * check if digit needs to be converted to letter (A, B, C, ...) and then print
 * ************/ 

int hexConvert(int num){
    int mod;   // variable to store remainder temporarily
    int digit1;  // store second remainder in digit1 as the first digit of the hex number
    int digit2;  // store first remainder in digit2 as the second digit of the hex number

    // ----------- use mod to store remainders in variables digit1 and digit2

    for(int i = 0; i < 2; i++){  
        
        mod = num % 16;    // store remainder in mod to store in digit later
        num = num / 16; 

        if(i == 0) {
            digit2 = mod;  // store remainder in digit2 if i = 0

        } else { 
            digit1 = mod;  // store remainder in digit1 if i = 1
        }
    } 
 
    // ----------- check remainder if it needs to be changed to a letter and then print 
    
    // Print first digit
    if(digit1 <= 9){   
        printf("%d", digit1);  // if remainder is 0-9, print it as is 

    } else if(digit1 == 10) {  // if remainder is 10, print A
        printf("A");

    } else if(digit1 == 11) {  // if remainder is 11, print B
        printf("B");

    } else if(digit1== 12) {   // if remainder is 12, print C
        printf("C");

    } else if(digit1 == 13) {  // if remainder is 13, print D
        printf("D");

    } else if(digit1 == 14) {  // if remainder is 14, print E
        printf("E");

    } else if(digit1 == 15) {  // if remainder is 15, print F
        printf("F");
    }
    
    // Print second digit, same printing principles
    if(digit2 <= 9){
        printf("%d", digit2);  

    } else if(digit2 == 10) {
        printf("A");

    } else if(digit2 == 11) {
        printf("B");

    } else if(digit2== 12) {
        printf("C");

    } else if(digit2 == 13) {
        printf("D");

    } else if(digit2 == 14) {
        printf("E");

    } else if(digit2 == 15) {
        printf("F");
    }
    printf("\n");  // after hex number is printed, go to new line
    return(0);
}
 

