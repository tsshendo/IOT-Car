/*
 * Interrupt.c
 *
 *  Created on: Feb 21, 2024
 *      Author: 13364
 */
// Includes
#include "msp430.h"
#include "ports.h"
#include "macros.h"
#include "functions.h"


// variables
int Time_Sequence;
int update_display;
int Time_Count;
int Time_Turn;
int seconds;
int circle_time=0;
int sec_count;
int last_time_count;
unsigned int Last_Time_Sequence; // a variable to identify Time_Sequence has changed
unsigned int debounce_count;
unsigned int debounce_count2;
int Debouncing;
int Debouncing2;

int auto_count;

// Proj 9 variables
int boot_time;
int boot_sequence=0;
extern unsigned int count_case;
int SW1_Pressed;
int SW2_Pressed;
int switch12=TRUE;
extern int command_complete;

// global variables
extern int ADC_Channel;
int ADC_Left_Detect; // = V_DETECT_L
int ADC_Right_Detect; //=V_DETECT_R
int ADC_Next_Val;
extern volatile int DAC_data;
extern volatile int case_no;
extern int message_done;
int tb1_counting;
extern int autonomous;

extern volatile char move;
extern volatile int move_forward;
extern int exit_count;
int forward_count;
int wait1;
int wait2;
int wait3;
int wait4;
int exit;
int find_time;
int intercept_count;
int adc_count;

// Create interrupt

#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
//------------------------------------------------------------------------------
// TimerB0 0 Interrupt handler
//----------------------------------------------------------------------------
//...... Add What you need happen in the interrupt ......

    Time_Sequence++;

        ADCCTL0 |= ADCENC; // Enable Conversions
        ADCCTL0 |= ADCSC; // Start next sample
        adc_count = OFF;

    Time_Count++;
    if (Time_Count %TRIANGLE_SET_DISTANCE==OFF) {
        update_display = TRUE;
        Time_Count = OFF;
    }

TB0CCR0 += TB0CCR0_INTERVAL; // Add Offset to TBCCR0
//----------------------------------------------------------------------------
}

#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){
//----------------------------------------------------------------------------
// TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
//----------------------------------------------------------------------------
switch(__even_in_range(TB0IV,14)){
case 0: break; // No interrupt
case 2: // CCR1 not used
//...... Add What you need happen in the interrupt ......
    P4IFG &= ~SW1;           //Clearing flags

    if(debounce_count++>=LEFT_COUNT_TIME){
        Debouncing=TRUE;
        debounce_count=OFF;
        P4IE|=SW1;
        TB0CCTL1 &= ~CCIE;
    }

TB0CCR1 += TB0CCR1_INTERVAL; // Add Offset to TBCCR1
break;
case 4: // CCR2 not used
//...... Add What you need happen in the interrupt ......
    P2IFG &= ~SW2;           //Clearing flags

        if(debounce_count2++>=LEFT_COUNT_TIME){
            Debouncing2=TRUE;
            debounce_count2=OFF;
            P2IE|=SW2;
            TB0CCTL1 &= ~CCIE;
        }
TB0CCR2 += TB0CCR2_INTERVAL; // Add Offset to TBCCR2
break;
case 14: // overflow
//...... Add What you need happen in the interrupt ......
    //TB0CTL &= ~TBIFG;
    if(DAC_data>2300){
        DAC_data=DAC_data-WAITING2START;
        SAC3DAT=DAC_data;
    }
    else{
    TB0CTL &= ~TBIE;
    }

break;
default: break;
}
//----------------------------------------------------------------------------
}

//----------------------------------------------------------------------------
// Timer1 interrupts
//----------------------------------------------------------------------------
#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void){
//------------------------------------------------------------------------------
// TimerB1 0 Interrupt handler
//----------------------------------------------------------------------------
//...... Add What you need happen in the interrupt ......
    sec_count++;
            if(sec_count++ >=TRAVEL_DISTANCE_FigEight){
                sec_count=OFF;
                message_done=OFF;
                if(case_no<8){
                    case_no++;
                }
            }
        if(exit_count==OKAY){
            exit++;
            if(exit++ >=TRAVEL_DISTANCE_CIRCLE){
                exit=OFF;
                exit_count=2;
            }
        }

        if(move==FOR2SEC){
            forward_count++;
            if(forward_count++ >TRAVEL_DISTANCE_FigEight){
                forward_count=OFF;
                move=STOP;
            }
        }

        if((move==LEFT)||(move == RIGHT)){
            tb1_counting++;
            if(tb1_counting++ >=TRIANGLE_SET_DISTANCE){
                tb1_counting=OFF;
                move=STOP;
            }
        }
    if(count_case==5){
        intercept_count++;
        if(intercept_count++ >=MINUTES){
            intercept_count=OFF;
            count_case=TOTAL_TRIANGLE_DISTANCE;
        }
    }
    if(count_case==TRIANGLE_STRAIGHT_DISTANCE){
            Time_Turn++;
            if(Time_Turn++ >=WAITING2START){
                Time_Turn=OFF;
                count_case=4;
            }
        }

    if(count_case==4){
            wait2++;
            if(wait2++ >=TRIANGLE_SET_DISTANCE){
                wait2=OFF;
                count_case=TRIANGLE_SET_DISTANCE;
            }
        }
    if(count_case==TOTAL_TRIANGLE_DISTANCE){
        wait3++;
        if(wait3++ >=WAITING2START){
            wait3=OFF;
            count_case=7;
        }
    }
    if(count_case==7){
            circle_time++;
            if(circle_time++ >=MINUTES){
                circle_time=OFF;
                count_case=8;
            }
        }

    if(count_case==TRIANGLE_SET_DISTANCE){
        wait4++;
        if(wait4++ >=WAITING2START){
            wait4=OFF;
            count_case=5;
        }
    }


TB1CCR0 += TB1CCR0_INTERVAL; // Add Offset to TBCCR0
//----------------------------------------------------------------------------
}

// Timer1_B1 ISR--------------------------------------------------------------
#pragma vector=TIMER1_B1_VECTOR
__interrupt void TIMER1_B1_ISR(void){
//----------------------------------------------------------------------------
// TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
//----------------------------------------------------------------------------
switch(__even_in_range(TB0IV,14)){
case 0: break; // No interrupt
case 2: // CCR1 used
//...... Add What you need happen in the interrupt .....

TB1CCR1 += TB1CCR1_INTERVAL; // Add Offset to TBCCR1
break;
case 4: // CCR2 not used
//...... Add What you need happen in the interrupt ......

//TB1CCR2 += TB1CCR2_INTERVAL; // Add Offset to TBCCR2
break;
case 14: // overflow
//...... Add What you need happen in the interrupt ......
    //TB1CTL &= ~TBIFG;


break;
default: break;
}
//----------------------------------------------------------------------------
}

//----------------------------------------------------------------------------
#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
 switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
 case ADCIV_NONE:
 break;
 case ADCIV_ADCOVIFG: // When a conversion result is written to the ADCMEM0
 // before its previous conversion result was read.
 break;
 case ADCIV_ADCTOVIFG: // ADC conversion-time overflow
 break;
 case ADCIV_ADCHIIFG: // Window comparator interrupt flags
 break;
 case ADCIV_ADCLOIFG: // Window comparator interrupt flag
 break;
 case ADCIV_ADCINIFG: // Window comparator interrupt flag
 break;
 case ADCIV_ADCIFG: // ADCMEM0 memory register with the conversion result
     ADCCTL0 &= ~ADCENC; // Disable ENC bit.
      switch (ADC_Channel++){
      case 0x00: // Channel A2 Interrupt
      ADC_Left_Detect = ADCMEM0; // Move result into Global Values
      //ADC_Left_Detect = ADC_Left_Detect >> 2; // Divide the result by 4
      if(move==AUTO||case_no==8){
      HEXtoBCD(ADC_Left_Detect);
      adc_line(4,5);
      }
      ADCMCTL0 &= ~ADCINCH_2; // Disable Last channel A2
      ADCMCTL0 |= ADCINCH_3; // Enable Next channel A3
      break;
      case 0x01: // Channel A3 Interrupt
      ADC_Right_Detect = ADCMEM0; // Move result into Global Values
      //ADC_Right_Detect = ADC_Right_Detect >> 2;
      if(move==AUTO||case_no==8){
      HEXtoBCD(ADC_Right_Detect);
      adc_line(4,0);
      }
      ADCMCTL0 &= ~ADCINCH_3; // Disable Last channel A3
      ADCMCTL0 |= ADCINCH_5; // Enable Next channel 5
      break;
      case 0x02:
      ADC_Next_Val = ADCMEM0; // Move result into Global Values
      //ADC_Next_Val = ADC_Next_Val >> 2;
//      HEXtoBCD(ADC_Next_Val);
////      adc_line(4,3);
      ADCMCTL0 &= ~ADCINCH_5; // Disable Last channel A5
      ADCMCTL0 |= ADCINCH_2; // Enable First channel 2
      ADC_Channel=OFF;
      break;
      default:
      break;
      }
      //ADCCTL0 |= ADCENC; // Enable Conversions
      //ADCCTL0 |= ADCSC; // Start next sample - Move to timerB0 interrupt
 break;
 default:
 break;
 }
}





