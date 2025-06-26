/*
 * led.c
 *
 *  Created on: Jan 25, 2024
 *      Author: 13364
 */
  // Global Variables
#include "msp430.h"
#include "macros.h"
#include "functions.h"


  // Initialize LED State
  void Init_LEDs(void){
  //------------------------------------------------------------------------------
  // LED Configurations
  //------------------------------------------------------------------------------
  // Turns on both LEDs
    P1OUT &= ~RED_LED;
    P6OUT &= ~GRN_LED;
  //------------------------------------------------------------------------------
  }


