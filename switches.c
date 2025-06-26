/*
 * switches.c
 *
 *  Created on: Feb 8, 2024
 *      Author: 13364
 */

#include "ports.h"
#include "macros.h"
#include "msp430.h"
#include "functions.h"
#include <string.h>


// Variables

int debounce_count;
int SW1_Pressed;
int Debouncing;
int run_cases = FALSE;

extern char display_line[4][11];
extern char *display[4];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;

extern unsigned int ADC_Left_Detect; // = V_DETECT_L
extern unsigned int ADC_Right_Detect; //=V_DETECT_R
extern unsigned int ADC_Left_Detect_Proxy;
extern unsigned int ADC_Right_Detect_Proxy;
extern unsigned int ADC_Right_Detect_White;
extern unsigned int ADC_Left_Detect_White;

extern volatile char IOT_Ring_Rx[16];
extern volatile char USB_Ring_Rx[16];
extern volatile char process_buffer[16];
extern volatile char iot_TX_buf[16];
extern volatile char usb_value[16];
int direct_usb;
//int case_no=0;
extern int usb_rx_wr;
int iot_rx_wr;
int iot_tx;
extern int case_no;
int press_no;
int alternate;


//------------------------------------------------------------------------------
// Port 4 interrupt. For switches, they are disabled for the duration
// of the debounce timer. Flag is set that user space can check.

//include #pragma vector = [Assigned Vector];
#pragma vector=PORT4_VECTOR;
//Create Interrupt Service Routine Function with “__interrupt”
__interrupt void switchP4_interrupt(void) {
    // Switch 1
    if (P4IFG & SW1) {
        P4IE &= ~SW1;            //1. Disable Switch 1
        P4IFG &= ~SW1;           //Clearing flags

        ADC_Left_Detect_White=ADC_Left_Detect;
        ADC_Right_Detect_White=ADC_Right_Detect;

        TB0CCTL1 &= ~CCIFG;       //3. Clear TimerB0 Interrupt Flag for Capture Compare Register 1
        TB0CCR1= TB0CCR1_INTERVAL;     //4. Add Interval to TB0R for TB0CCR1
        TB0CCTL1 |= CCIE ;        //5. Enable TimerB0_1
        P4IE |= SW1;
    }
}
//------------------------------------------------------------------------------
#pragma vector=PORT2_VECTOR;
//Create Interrupt Service Routine Function with “__interrupt”
__interrupt void switchP2_interrupt(void) {
    // Switch 2
    if (P2IFG & SW2) {
            P2IE &= ~SW2;            //1. Disable Switch 2
            P2IFG &= ~SW2;
            case_no=9;
            ADC_Left_Detect_Proxy=ADC_Left_Detect;
            ADC_Right_Detect_Proxy=ADC_Right_Detect;
            TB0CCTL1 &= ~CCIFG;       //3. Clear TimerB0 Interrupt Flag for Capture Compare Register 1
            TB0CCR1=  TB0CCR2_INTERVAL;     //4. Add Interval to TB0R for TB0CCR1
            TB0CCTL1 |= CCIE ;        //5. Enable TimerB0_1
            P2IE |= SW2;

}
}

