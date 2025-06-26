/*
 * ADC.c
 *
 *  Created on: Feb 29, 2024
 *      Author: 13364
 */

#include "msp430.h"
#include "ports.h"
#include "macros.h"
#include "functions.h"

char Thousands;
char Hundreds;
char Tens;
char Ones;

// global variables
int ADC_Channel;
extern unsigned int ADC_Left_Detect; // = V_DETECT_L
extern unsigned int ADC_Right_Detect; //=V_DETECT_R
char adc_char[];
int i;

extern char display_line[4][11];
extern char *display[4];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile int Time_Count;

//-----------------------------------------------------------------
// Hex to BCD Conversion
// Convert a Hex number to a BCD for display on an LCD or monitor
//
//-----------------------------------------------------------------
void HEXtoBCD(int hex_value){
 int value=0;
 for(i=0; i < 4; i++) {
     adc_char[i] = '0';
}

 while (hex_value > 999){
 hex_value = hex_value - 1000;
 value = value + 1;
 adc_char[0] = 0x30 + value;
 }
 value = 0;
 while (hex_value > 99){
 hex_value = hex_value - 100;
 value = value + 1;
 adc_char[1] = 0x30 + value;
 }
 value = 0;
 while (hex_value > 9){
 hex_value = hex_value - 10;
 value = value + 1;
 adc_char[2] = 0x30 + value;
 }
 adc_char[3] = 0x30 + hex_value;
}
//-------------------------------------------------------------

void adc_line(char line, char location){
//-------------------------------------------------------------
 int i;
 unsigned int real_line;
 real_line = line - 1;
 for(i=0; i < 4; i++) {
 display_line[real_line][i+location] = adc_char[i];

 }
 display_changed = TRUE;
}
//-------------------------------------------------------------


//------------------------------------------------------------------------------
void Init_ADC(void){
//------------------------------------------------------------------------------
// V_DETECT_L (0x04) // Pin 2 A2
// V_DETECT_R (0x08) // Pin 3 A3
// V_THUMB (0x20) // Pin 5 A5
//------------------------------------------------------------------------------
// ADCCTL0 Register
 ADCCTL0 = 0; // Reset
 ADCCTL0 |= ADCSHT_2; // 16 ADC clocks
 ADCCTL0 |= ADCMSC; // MSC
 ADCCTL0 |= ADCON; // ADC ON
// ADCCTL1 Register
 ADCCTL1 = 0; // Reset
 ADCCTL1 |= ADCSHS_0; // 00b = ADCSC bit
 ADCCTL1 |= ADCSHP; // ADC sample-and-hold SAMPCON signal from sampling timer.
 ADCCTL1 &= ~ADCISSH; // ADC invert signal sample-and-hold.
 ADCCTL1 |= ADCDIV_0; // ADC clock divider - 000b = Divide by 1
 ADCCTL1 |= ADCSSEL_0; // ADC clock MODCLK
 ADCCTL1 |= ADCCONSEQ_0; // ADC conversion sequence 00b = Single-channel single-conversion
// ADCCTL1 & ADCBUSY identifies a conversion is in process
// ADCCTL2 Register
 ADCCTL2 = OFF; // Reset
 ADCCTL2 |= ADCPDIV0; // ADC pre-divider 00b = Pre-divide by 1
 ADCCTL2 |= ADCRES_2; // ADC resolution 10b = 12 bit (14 clock cycle conversion time)
 ADCCTL2 &= ~ADCDF; // ADC data read-back format 0b = Binary unsigned.
 ADCCTL2 &= ~ADCSR; // ADC sampling rate 0b = ADC buffer supports up to 200 ksps
// ADCMCTL0 Register
 ADCMCTL0 |= ADCSREF_0; // VREF - 000b = {VR+ = AVCC and VR– = AVSS }
 ADCMCTL0 |= ADCINCH_5; // V_THUMB (0x20) Pin 5 A5
 ADCIE |= ADCIE0; // Enable ADC conv complete interrupt
 ADCCTL0 |= ADCENC; // ADC enable conversion.
 ADCCTL0 |= ADCSC; // ADC start conversion.
}

