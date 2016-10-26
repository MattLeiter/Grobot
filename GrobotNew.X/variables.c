/*
 * File:   variables.c
 * Author: Matthew
 *
 * Created on October 15, 2016, 8:37 PM
 */

#include "adc.h"
#include "delay.h"
#include "tim.h"
#include "lcd.h"



/* IF YOU ARE MAKING A VARIABLE HERE, MAKE IT IN VARIABLES.H 
 * AND DECLARE IT EXTERN
 */


volatile unsigned long adc_result = 0;
volatile unsigned char adc_lcd_update = 0;


// tim.h variables
volatile unsigned char sec = 0;
volatile unsigned char min = 0;
volatile unsigned char hrs = 0;
volatile unsigned char tim_lcd_update = 0;
volatile unsigned char intr_count = 0;


// delay.h variables
unsigned int temp_count = 0;


// lcd.h variables
volatile unsigned int thousand = 0;
volatile unsigned int hundred = 0;
volatile unsigned int tens = 0;
volatile unsigned int ones = 0;
volatile unsigned int scan = 0;


