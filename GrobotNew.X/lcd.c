/*
 * File:   newmainXC161.c
 * Author: Matthew
 *
 * Created on October 15, 2016, 4:20 PM
 */
#include "lcd.h"
#include "delay.h"
#include "tim.h"
#include "adc.h"
#include "variables.h"


extern volatile unsigned char sec;
extern volatile unsigned char min;
extern volatile unsigned char hrs;
extern volatile unsigned char tim_lcd_update;
extern volatile unsigned char intr_count;


extern volatile unsigned char thousand;
extern volatile unsigned char hundred;
extern volatile unsigned char tens;
extern volatile unsigned char ones;



#define cursor_right()  lcd_cmd( 0x14 )
#define cursor_left()   lcd_cmd( 0x10 )
#define display_shift() lcd_cmd( 0x1C )
#define home_clr()      lcd_cmd( 0x01 ) 
#define home_it()       lcd_cmd( 0x02 ) 
#define line_2()        lcd_cmd( 0xC0 )



void Init_LCD( void )             // initialize LCD display
{

	// 15mS delay after Vdd reaches nnVdc before proceeding with LCD initialization
	// not always required and is based on system Vdd rise rate
	Delay(Delay_15mS_Cnt);                  // 15ms delay
			
	/* set initial states for the data and control pins */
	LATE &= 0xFF00;	
    RW = 0;                       // R/W state set low
	RS = 0;                       // RS state set low
	E = 0;                        // E state set low

	/* set data and control pins to outputs */
	TRISE &= 0xFF00;
 	RW_TRIS = 0;                  // RW pin set as output
	RS_TRIS = 0;                  // RS pin set as output
	E_TRIS = 0;                   // E pin set as output

	/* 1st LCD initialization sequence */
	DATA &= 0xFF00;
    DATA |= 0x0038;
    E = 1;	
    Nop();
    Nop();
    Nop();
    E = 0;                        // toggle E signal
   	Delay(Delay_5mS_Cnt);         // 5ms delay
      
	/* 2nd LCD initialization sequence */
	DATA &= 0xFF00;
    DATA |= 0x0038;
    E = 1;	
    Nop();
    Nop();
    Nop();	
    E = 0;                        // toggle E signal
    Delay_Us( Delay200uS_count ); // 200uS delay

	/* 3rd LCD initialization sequence */
	DATA &= 0xFF00;
    DATA |= 0x0038;
    E = 1;		
    Nop();
    Nop();
    Nop();	
    E = 0;                        // toggle E signal
    Delay_Us( Delay200uS_count ); // 200uS delay

    lcd_cmd( 0x38 );              // function set
    lcd_cmd( 0x0C );              // Display on/off control, cursor blink off (0x0C)
    lcd_cmd( 0x06 );			  // entry mode set (0x06)
}


void lcd_cmd( char cmd )          // subroutiune for lcd commands
{
//	TRISD &= 0xFF00;              // ensure RD0 - RD7 are outputs
	DATA &= 0xFF00;               // prepare RD0 - RD7
    DATA |= cmd;                  // command byte to lcd
	RW = 0;                       // ensure RW is 0
    RS = 0;
    E = 1;                        // toggle E line
    Nop();
    Nop();
    Nop();
    E = 0;
   	Delay(Delay_5mS_Cnt);         // 5ms delay
}


void lcd_data( char data )        // subroutine for lcd data
{
//	TRISD &= 0xFF00;              // ensure RD0 - RD7 are outputs
	RW = 0;       				 // ensure RW is 0
    RS = 1;                       // assert register select to 1
	DATA &= 0xFF00;               // prepare RD0 - RD7
    DATA |= data;                 // data byte to lcd
    E = 1;				
 	Nop();
    Nop();
    Nop();
    E = 0;                       // toggle E signal
    RS = 0;                      // negate register select to 0
    Delay_Us( Delay200uS_count ); // 200uS delay
    Delay_Us( Delay200uS_count ); // 200uS delay
}

void puts_lcd( unsigned char *data, unsigned char count ) 
{
  	while ( count )
	{
		lcd_data( *data++ );
		count --;
	}	
}

void hexdec( char count )
{
	tens  = 0;
	ones = 0;
 
	while ( count >= 10 )
	{
		count -= 10;
		tens++;
	}

	ones = count;
}



void __attribute__((interrupt, no_auto_psv)) _T1Interrupt( void )
{		
	/* Seconds can't go past 59 */
	if(sec < 59) {
		sec++;
	} else {
			
		/* Reset sec and check min */
		sec = 0x00;
		if(min < 59 ) {
			min++;
		} else {
				
			/* Reset min and check hrs*/
			min = 0x00;
			if (hrs < 23) {
				hrs ++;
			} else {
				hrs = 0x00;
			}		  
		}
	}	

	/* Reset Timer 1 interrupt flag */
 	IFS0bits.T1IF = 0;

 	/* set flag to update LCD */
	tim_lcd_update = 1;
}
