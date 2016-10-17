#include "xc.h"
#include <p33FJ256GP710.h>

#include "lcd.h"
#include "delay.h"
#include "tim.h"
#include "adc.h"
#include "variables.h"

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt( void );


int main(void) {
	/* Initialize the ADC and Timer Module */
	//TIM_init();  //This is to test the timer module
    Init_LCD();
    
	/* The ADC relies on Timer3, so both must be initialized */
	ADC1_init();
	TIM3_init();  

	while(1){

		/*if(tim_lcd_update) {
			Update_TIM_LCD();
			tim_lcd_update = 0;
		} else if(adc_lcd_update == 1){
            puts_lcd((unsigned char *)"ADC: ", 5);   
			Update_ADC_LCD();
			adc_lcd_update = 0;
		}*/
	}  
    return 0;

}








		
/* 
   For Explorer 16 board, here are the data and control signal definitions
   RS -> RB15
   E  -> RD4
   RW -> RD5
   DATA -> RE0 - RE7   
*/








//12-bit step: 0.00122

// 1.1437e-5
//0160