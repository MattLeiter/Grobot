/*
 * File:   delay.c
 * Author: Matthew
 *
 * Created on October 15, 2016, 5:01 PM
 */

#include "lcd.h"
#include "delay.h"
#include "tim.h"
#include "adc.h"
#include "variables.h"


extern unsigned int temp_count;


void Delay( unsigned int delay_count ) 
{
	temp_count = delay_count +1;
	asm volatile("outer: dec _temp_count");	
	asm volatile("cp0 _temp_count");
	asm volatile("bra z, done");
	asm volatile("do #3200, inner" );	
	asm volatile("nop");
	asm volatile("inner: nop");
	asm volatile("bra outer");
	asm volatile("done:");
}
	

void Delay_Us( unsigned int delayUs_count )
{
	temp_count = delayUs_count +1;
	asm volatile("outer1: dec _temp_count");	
	asm volatile("cp0 _temp_count");
	asm volatile("bra z, done1");
	asm volatile("do #1500, inner1" );	
	asm volatile("nop");
	asm volatile("inner1: nop");
	asm volatile("bra outer1");
	asm volatile("done1:");
}		

