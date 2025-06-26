/*
 * Init_DAC.c
 *
 *  Created on: Mar 6, 2024
 *      Author: 13364
 */

# include <msp430.h>
#include "ports.h"


int DAC_data;

void Init_DAC(void){
 DAC_data = 4000;       // Value between 0x000 and 0x0FFF
SAC3DAT = DAC_data;     // Initial DAC data
 SAC3DAC = DACSREF_1;   // Select int Vref as DAC reference
 SAC3DAC |= DACLSEL_0;  // DAC latch loads when DACDAT written
// SAC3DAC |= DACIE;    // generate an interrupt
 SAC3DAC |= DACEN;      // Enable DAC

 SAC3OA = NMUXEN;       // SAC Negative input MUX controL
 SAC3OA |= PMUXEN;      // SAC Positive input MUX control
 SAC3OA |= PSEL_1;      // 12-bit reference DAC source selected
 SAC3OA |= NSEL_1;      // Select negative pin input
 SAC3OA |= OAPM;        // Select low speed and low power mode
 SAC3PGA = MSEL_1;      // Set OA as buffer mode
 SAC3OA |= SACEN;       // Enable SAC
 SAC3OA |= OAEN;        // Enable OA
}



void Init_REF(void){
// Configure reference module
 PMMCTL0_H = PMMPW_H; // Unlock the PMM registers
 PMMCTL2 = INTREFEN; // Enable internal reference
 PMMCTL2 |= REFVSEL_2; // Select 2.5V reference
// while(!(PMMCTL2 & REFGENRDY)); // Poll till internal reference settles
// Using a while statement is not usually recommended without an exit strategy.
// This while statement is the suggested operation to allow the reference to settle.
}
