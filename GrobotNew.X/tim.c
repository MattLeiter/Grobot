/*
 * File:   tim.c
 * Author: Matthew
 *
 * Created on October 15, 2016, 5:08 PM
 */

/*
 * TIM_init()
 * Used for setting up the timer module 
 */

#include "xc.h"
#include "delay.h"
#include "lcd.h"
#include "tim.h"
#include "variables.h"



extern volatile unsigned char sec;
extern volatile unsigned char min;
extern volatile unsigned char hrs;
extern volatile unsigned char tim_lcd_update;
extern volatile unsigned char intr_count;



extern volatile unsigned char thousand;
extern volatile unsigned char hundred ;
extern volatile unsigned char tens ;
extern volatile unsigned char ones ;


void TIM_init() {
	
	/* Reset the timer module*/
	T1CON = 0;              

	/* Reset the interrupt flagg, enable the interrupt, and set priority to 4*/
 	IFS0bits.T1IF = 0;
	IPC0bits.T1IP = 4;
 	IEC0bits.T1IE = 1;

	/* Set the prescaler to 256 to lower clock to 30742Hz*/
	T1CONbits.TCKPS = 3;

	/* Set the Period Counter to 30742 to generate an interrupt every second */ 	  	
	PR1 = 0x7816;           

	/* Choose the internal oscillator FRC @ 7.87MHz */
    OSCCON = 0;

	/* Enable Timer 1 and start counter*/
	T1CONbits.TON = 1;      // Enable Timer1 and start the counter
}


/*
 * TIM3_init
 * Used to generate a conversion every 125ms 
 */
void TIM3_init() 
{
	/* Set the prescaler to 64 to lower clock to 123kHz*/
	T3CONbits.TCKPS = 2;

	/* Set the Period Counter to 15 to generate a conversion every 125ms */ 	  	
	PR3 = 0xFFFF;
	
	/* Reset the interrupt flag and enable the interrupt flag */    
    IFS0bits.T3IF = 0;
    IEC0bits.T3IE = 0;

    //Start Timer 3
    T3CONbits.TON = 1;
}




void Update_TIM_LCD( void )
{
	/* Convert hours to decimal then displays it */
   	hexdec( hrs );
	line_2();
    lcd_data(tens + 0x30);
    lcd_data(ones + 0x30);
    puts_lcd((unsigned char *)" : ",3);   

    /* Convert minutes to decimal then displays it */
    hexdec( min );
    lcd_data(tens + 0x30);
    lcd_data(ones + 0x30);
    puts_lcd((unsigned char *)" : ",3);   	 

	/* Convert sec to decimal then displays it */
  	hexdec( sec );
    lcd_data(tens + 0x30);
    lcd_data(ones + 0x30);
}
