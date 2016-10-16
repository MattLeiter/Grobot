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

extern volatile unsigned char adc_result = 0;
extern volatile unsigned char adc_lcd_update = 0;


// tim.h variables
extern volatile unsigned char sec = 0;
extern volatile unsigned char min = 0;
extern volatile unsigned char hrs = 0;
extern volatile unsigned char tim_lcd_update = 0;
extern volatile unsigned char intr_count = 0;


// delay.h variables
extern unsigned int temp_count = 0;


// lcd.h variables
extern volatile unsigned char thousand = 0;
extern volatile unsigned char hundred = 0;
extern volatile unsigned char tens = 0;
extern volatile unsigned char ones = 0;


