/*
 * init.c
 *
 *  Created on: Jan 25, 2024
 *      Author: 13364
 */
  // Global Variables

#include "macros.h"
#include "msp430.h"
#include "functions.h"

extern char display_line[4][11];
extern char *display[4];
extern volatile unsigned char update_display;


// Initialize Conditions
void Init_Conditions(void){
//------------------------------------------------------------------------------

  int i;
  for(i=0;i<11;i++){
    display_line[0][i] = RESET_STATE;
    display_line[1][i] = RESET_STATE;
    display_line[2][i] = RESET_STATE;
    display_line[3][i] = RESET_STATE;
  }
  display_line[0][10] = 0;
  display_line[1][10] = 0;
  display_line[2][10] = 0;
  display_line[3][10] = 0;

  display[0] = &display_line[0][0];
  display[1] = &display_line[1][0];
  display[2] = &display_line[2][0];
  display[3] = &display_line[3][0];
  update_display = 0;
  // Interrupts are disabled by default, enable them.
  _enable_interrupts();
}



