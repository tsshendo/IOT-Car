/*
 * display.c
 *
 *  Created on: Jan 25, 2024
 *      Author: 13364
 */
  // Global Variables

#include "functions.h"
#include "LCD.h"
#include "msp430.h"

extern volatile unsigned char display_changed;
extern volatile unsigned int update_display;


void Display_Process(void){
  if(update_display){
    update_display = 0;
    if(display_changed){
      display_changed = 0;
      Display_Update(0,0,0,0);
    }
  }
}


