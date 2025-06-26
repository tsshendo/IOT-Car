/*
 * movement.c
 *
 *  Created on: Feb 2, 2024
 *      Author: 13364
 */
#include  "ports.h"
#include "macros.h"
#include  "msp430.h"
#include "functions.h"
#include <string.h>
#include "stdint.h"

// Global Variables
extern volatile unsigned int Last_Time_Sequence; // a variable to identify Time_Sequence has changed
extern volatile unsigned int cycle_time; // is a new time base used to control making shapes
extern volatile unsigned int time_change; // is an identifier that a change has occurred
extern unsigned int Time_Count;
int loop;

// Display functions and variables
extern char display_line[4][11];
extern char *display[4];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;

///////////////////////////////////////////////////////////////////////////////

// Function description
void movement(void){
        P6OUT |= L_FORWARD;
         P6OUT |= R_FORWARD;
        }

void Forward_On(void){
    strcpy(display_line[1], "   CASE   ");
    strcpy(display_line[2], "  FORWARD ");
    display_changed = TRUE;
    RIGHT_FORWARD_SPEED =PERCENT_80; // P6.1 Right Forward PWM ON amount
    LEFT_FORWARD_SPEED = PERCENT_80; // P6.3 Left Forward PWM ON amount
    LCD_BACKLITE_DIMING = PERCENT_80;

    }

void Forward_Off(void){
        P6OUT &= ~L_FORWARD;
         P6OUT &= ~R_FORWARD;
        }

// Function called to Turn all movement off
void Movement_Off(void ){
    RIGHT_FORWARD_SPEED =WHEEL_OFF;
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_REVERSE_SPEED =WHEEL_OFF;
    LEFT_REVERSE_SPEED = WHEEL_OFF;
}


// When both reverse and forward is active for the same motor.
void Smoke_Case(void){
    if(P6IN & L_FORWARD){
        if(P6IN & L_REVERSE){
            Movement_Off(); // Turns off everything if Forward and Reverse active
        }
    }
    if(P6IN & R_FORWARD){
        if(P6IN & R_REVERSE){
            Movement_Off(); // Turns off everything if Forward and Reverse active
        }
    }
}

//Travel forward for 1 second, pause for 1 second
//Travel forward for 1 second, pause for 1 second
// Forward On, Movement_Off

//Travel reverse for 2 seconds, pause for 1 second
void Reverse_On(void){
    strcpy(display_line[1], "   CASE   ");
    strcpy(display_line[2], "  REVERSE ");
    display_changed = TRUE;
    P6OUT &= ~L_FORWARD;
    P6OUT &= ~R_FORWARD;
    P6OUT |= R_REVERSE;
    P6OUT |= L_REVERSE;
}

//Spin in place turning clockwise for 3 second, pause for 2 second
void Spin_Clock(void){
    strcpy(display_line[1], "   SPIN   ");
    strcpy(display_line[2], "   CLOCK  ");
    display_changed = TRUE;
    P6OUT |= L_FORWARD;
    P6OUT &= ~R_FORWARD;
    P6OUT |= R_REVERSE;
    P6OUT &= ~L_REVERSE;
}
//Spin in place turning counterclockwise for 3 second, pause for 2 second
void Spin_AntiClock(void){
    strcpy(display_line[1], "   ANTI   ");
    strcpy(display_line[2], "   CLOCK  ");
    display_changed = TRUE;
    P6OUT &= ~L_FORWARD;
    P6OUT |= R_FORWARD;
    P6OUT &= ~R_REVERSE;
    P6OUT |= L_REVERSE;
}


