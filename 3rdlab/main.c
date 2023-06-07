#include "stm32f10x.h"
#include<stdio.h>

int main (void) {
    
    //------------------------------
    //      init the micro controller
    //------------------------------
    //enable the GPIO clock for port GPIOA
    RCC->APB2ENR |= 0x0004; // ...000100  // This line enables the clock for the GPIOA port. RCC stands for Reset and Clock Control, and it provides control over various system clocks and resets. 
	//Here, the APB2ENR register is accessed using the arrow operator (->), and the third bit (bit 2) is set by performing a bitwise OR operation with the value 0x0004.
    //Or we could use a more readable way:
    //RCC->APB2ENR |= 1<<2; // This ORs the 2nd bit (Note that bit numbers start from 0)
    
    //Let's set PA03 pin as output
    //We need to modify GPIOA_CRL register. To make it output with max speed 2Mhz:
    //Mode3[1:0] should be 10, CR3[1:0] might be 00, which is Push/Pull output.
    //Therefore, GPIOA_CRL[15:12] bits should be 0b0010=0x2 (Reference manual)
    //Note that we cannot use OR. We exacly want 0b0010.
    //Reset value of GPIOA is 0x4444 4444. Each 4 corresponds a pair of (Mode,CR)
    //So, the value to be loaded into the reg is 0x4444 2444
    GPIOA->CRL = 0x44444224;    //Leave every pin in reset mode except pin1 and pin2 . It is 
                                                        //set to PushPull output at max 2Mhz speed.
    //Or for a more readable but slow way we could do:
    //GPIOA->CRL = (GPIOA->CRL & ~(0xFF<<12)) | 2<<12;
    //now we are all set to go


/*This is an infinite loop that generates a specific pattern of signals on GPIOA pins. The loop contains four sections, each representing a different signal pattern (00, 01, 10, 11). 
In each section, there is a for loop that runs a certain number of iterations, causing a delay. 
After the delay, the GPIOA ODR register is set to a specific value, which determines the pattern of signals on the pins.
The delay is achieved by looping i from 0 to 0x100000, performing no operations inside the loop. This loop acts as a time delay, providing a certain amount of delay between each signal pattern.*/
    GPIOA->ODR=0x00000000;
    //forever do...
    int i;
    for(;;){
        
        //00
        for(i=0;i<0x100000;i++){ //i was 0 it  became 1 here and causes a delay
        }
        GPIOA->ODR=0x00000000;  //output pin is reset when its 1

        //01
        for(i=0;i<0x100000;i++){  //i was 1 and it became 2 here it just caused a delay
        }
        GPIOA->ODR=0x00000002;  //1st  pin is blinked 
        
        //10      
        for(i=0;i<0x100000;i++){ //i was 2 became 3 it just causes a delay
        }
        GPIOA->ODR=0x00000004; //2nd pin is blinked
        
        //11
        for(i=0;i<0x100000;i++){  //i was 3 became 4 it just causes a delay
        }
        GPIOA->ODR=0x00000006;  //1st and 2nd pin is blinked

    }//for    
		
    
    return 0;
}