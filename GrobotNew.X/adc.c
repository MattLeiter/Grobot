/*
 * File:   adc.c
 * Author: Matthew
 *
 * Created on October 15, 2016, 5:15 PM
 */
#include "delay.h"
#include "tim.h"
#include "lcd.h"
#include "adc.h"
#include "variables.h"

extern volatile unsigned long adc_result;
extern volatile unsigned char adc_lcd_update;


extern volatile unsigned char thousand ;//= 0 ;
extern volatile unsigned char hundred ;//= 0;
extern volatile unsigned char tens ;//= 0;
extern volatile unsigned char ones ;//= 0;
extern volatile unsigned char intr_count ;//= 0;


void ADC1_init(void)
{
    TRISA = 0x0600; 
    
    TRISB = 0x0001;
    
	/* Set for 12 bit mode, fractional output */
	AD1CON1bits.AD12B  = 1;
	AD1CON1bits.FORM   = 0;

	/* For Demo purposes, we are using Timer3 as clock source, might use it later, but mostly likely will
	   use interal counter */
	AD1CON1bits.SSRC   = 2;
	AD1CON1bits.ASAM   = 0;

	/* Select input selections for CH0 and convert CH0 (CH 1, 2, and 3 don't operate 12-bit mode) */
	AD1CON2bits.CSCNA = 1;
	AD1CON2bits.CHPS  = 0;
    AD1CON2bits.VCFG  = 3;

	/* This is used for DMA Addresses (will probably use later on) */
	AD1CON2bits.SMPI    = 0;  //For now set to 0	

	/* Set the the frequency of the system to be 7.87MHz */
    OSCCON = 0;

    /* ADC clock is derived from the System Clock. Conversion clock is:  1.27us, Conversion time: 15.25us*/
	AD1CON3bits.ADRC = 0;
	AD1CON3bits.ADCS = 9;

	/* Enable AN0, AN5, AN6 for channel scan */	
	AD1CSSH = 0x0000;
	AD1CSSLbits.CSS0=1;
//	AD1CSSLbits.CSS5=1;
//	AD1CSSLbits.CSS6=1;
 
	/* Set AN1 and AN6 Analog Input*/
	AD1PCFGH=0xFFFF;
	AD1PCFGL=0xFFFF;
	AD1PCFGLbits.PCFG0 = 0;
	//AD1PCFGLbits.PCFG6 = 0; 
	
    /* Clear the interrupt flag bit, enable A/D interrupt, and turn on the A/D converter */
    IFS0bits.AD1IF = 0;
    IEC0bits.AD1IE = 1;
    AD1CON1bits.ADON = 1;
    AD1CON1bits.SAMP = 1;

    
}


/*
// * ADC1Interrupt
// * This interrupt will display the value from the current scanned section
// */
void __attribute__((interrupt, no_auto_psv))_ADC1Interrupt(void)
{
    
    if(AD1CON1bits.DONE == 1){
        adc_result = ADC1BUF0;
        AD1CON1bits.SAMP = 1;
        
    }
    else if(AD1CON1bits.DONE == 0){
        adc_result = 5;
    }
//    
//    if(intr_count  == 200) {
//        	adc_result     = ADC1BUF0;  
//        
//        //lcd_cmd( 0x01 ); //clears
//        //puts_lcd((unsigned char *)"Print ", 6);
//
//        intr_count = 0;
//        
//        
//        /* Convert ADC value into parts*/
//    	hex2decADC(adc_result);
//	
//    	/* Display the ADC result */
//    	lcd_data(thousand + 0x30);
//    	lcd_data(hundred + 0x30);
//    	lcd_data(tens + 0x30);
//    	lcd_data(ones + 0x30);
//      
//        //adc_lcd_update = 1;
//    }
//   
//    intr_count++;
}



///*
// * hex2decADC
// * Converts up to the thousands
// */
//
void hex2decADC( unsigned int hexnum ) {
   
	while ( hexnum >= 1000 ) {
	  hexnum -= 1000;
	  thousand++;
	}

	while (hexnum >= 100) {
	  hexnum -= 100;
	  hundred++;
	}

	while (hexnum >= 10 ) {
	  hexnum -= 10;
	  tens++;
	}

	ones = hexnum;
}



void Update_ADC_LCD( void ) {
	/* Convert ADC value into parts*/
	hex2decADC(adc_result);
	
	/* Display the ADC result */
	lcd_data(thousand + 0x30);
	lcd_data(hundred + 0x30);
	lcd_data(tens + 0x30);
	lcd_data(ones + 0x30);	
}

