/*
 * ports.c
 *
 *  Created on: Jan 25, 2024
 *      Author: 13364
 */
  // Global Variables
#include "ports.h"
#include  "msp430.h"
#include "functions.h"

//void Init_Ports(void);
//void Init_Port1(void);
//void Init_Port2(void);
//void Init_Port3(void);
//void Init_Port4(void);
//void Init_Port5(void);
//void Init_Port6(void);

void Init_Ports(void)
{
    Init_Port1();
    Init_Port2();
    Init_Port3();
    Init_Port4();
    Init_Port5();
    Init_Port6();


}
     void Init_Port1 (void){
        // Initial Setting for direction and Output
         P1DIR = 0x00; // Set P1 direction to input
         P1OUT = 0x00; // P1 set Low

         //Port 1.0
         P1SEL0 &= ~RED_LED; // Set RED_LED as GP I/O
         P1SEL1 &= ~RED_LED; // Set RED_LED as GP I/O
         P1OUT &= ~RED_LED; // Set Red LED On
         P1DIR |= RED_LED; // Set Red LED direction to output

         //Port 1.1
         P1SELC |= V_A1_SEEED; // ADC input for A1_SEEED

         //Port 1.2
         P1SELC |= V_DETECT_L; // ADC input for V_DETECT_L

         //Port 1.3
         P1SELC |= V_DETECT_R; // ADC input for V_DETECT_R

         //Port 1.4
         P1SELC |= V_A4_SEEED; // ADC input for V_A4_SEEED

         //Port 1.5
         P1SELC |= V_THUMB; // ADC input for V_THUMB

         //Port 1.6
         P1SEL0 |= UCA0TXD; // UCA0TXD pin
         P1SEL1 &= ~UCA0TXD; // UCA0TXD pin

         //Port 1.7
         P1SEL0 |= UCA0RXD; // UCA0RXD pin
         P1SEL1 &= ~UCA0RXD; // UCA0RXD pin

    }

    void Init_Port2(void){ // Configure Port 2
    //------------------------------------------------------------------------------

     // Initial Setting for direction and Output
     P2OUT = 0x00; // P2 set Low
     P2DIR = 0x00; // Set P2 direction to output

     //Port 2.0
     P2SEL0 &= ~SLOW_CLK; // SLOW_CLK GPIO operation
     P2SEL1 &= ~SLOW_CLK; // SLOW_CLK GPIO operation
     P2OUT &= ~SLOW_CLK; // Initial Value = Low / Off
     P2DIR |= SLOW_CLK; // Direction = output

     //Port 2.1
     P2SEL0 &= ~CHECK_BAT; // CHECK_BAT GPIO operation
     P2SEL1 &= ~CHECK_BAT; // CHECK_BAT GPIO operation
     P2OUT &= ~CHECK_BAT; // Initial Value = Low / Off
     P2DIR |= CHECK_BAT; // Direction = output

     //Port 2.2
     P2SEL0 &= ~IR_LED; // P2_2 GPIO operation
     P2SEL1 &= ~IR_LED; // P2_2 GPIO operation
     P2OUT &= ~IR_LED; // Initial Value = Low / Off
     P2DIR |= IR_LED; // Direction = Output

     //Port 2.3
     P2SEL0 &= ~SW2; // SW2 Operation
     P2SEL1 &= ~SW2; // SW2 Operation
     P2OUT |= SW2; // Configure pullup resistor
     P2DIR &= ~SW2; // Direction = input
     P2REN |= SW2; // Enable pullup resistor
     P2IES |= SW2;
     P2IFG &= ~SW2;
     P2IE |= SW2;

     //Port 2.4
     P2SEL0 &= ~IOT_RUN_RED; // IOT_RUN_CPU GPIO operation
     P2SEL1 &= ~IOT_RUN_RED; // IOT_RUN_CPU GPIO operation
     P2OUT &= ~IOT_RUN_RED; // Initial Value = Low / Off
     P2DIR |= IOT_RUN_RED; // Direction = out

     //Port 2.5
     P2SEL0 &= ~DAC_ENB; // DAC_ENB GPIO operation
     P2SEL1 &= ~DAC_ENB; // DAC_ENB GPIO operation
     P2OUT |= DAC_ENB; // Initial Value = High
     P2DIR |= DAC_ENB; // Direction = output

     //Port 2.6
     P2SEL0 &= ~LFXOUT; // LFXOUT Clock operation
     P2SEL1 |= LFXOUT; // LFXOUT Clock operation

     //Port 2.7
     P2SEL0 &= ~LFXIN; // LFXIN Clock operation
     P2SEL1 |= LFXIN; // LFXIN Clock operation

     //------------------------------------------------------------------------------
    }

    //void Init_Port3(char smclk);
    void Init_Port3(void){
        P3OUT = 0x00; // P3 set Low
        P3DIR = 0x00; // Set P3 direction to output

        // Port 3.0
        P3SEL0 &= ~TEST_PROBE; // TEST_PROBE GPIO operation
        P3SEL1 &= ~TEST_PROBE; // TEST_PROBE GPIO operation
        P3OUT &= ~TEST_PROBE; // Initial Value = Low / Off
        P3DIR |= TEST_PROBE; // Direction = output

        // Port 3.1
        P3SEL0 &= ~OA2N; // OA2N GPIO operation
        P3SEL1 &= ~OA2N; // OA2N GPIO operation
        P3OUT &= ~OA2N; // Initial Value = Low / Off
        P3DIR |= OA2N; // Direction = output

        // Port 3.2
        P3SEL0 &= ~OA2O; // OA2O GPIO operation
        P3SEL1 &= ~OA2O; // OA2O GPIO operation
        P3OUT &= ~OA2O; // Initial Value = Low / Off
        P3DIR |= OA2O; // Direction = output

        // Port 3.3
        P3SEL0 &= ~OA2P; // OA2P GPIO operation
        P3SEL1 &= ~OA2P; // OA2P GPIO operation
        P3OUT &= ~OA2P; // Initial Value = Low / Off
        P3DIR |= OA2P; // Direction = output

        // Port 3.4
        P3SEL0 |= SMCLK_OUT; // SMCLK_OUT GPIO operation
        P3SEL1 &= ~SMCLK_OUT; // SMCLK_OUT GPIO operation
        P3OUT &= ~SMCLK_OUT; // Initial Value = Low / Off
        P3DIR |= SMCLK_OUT; // Direction = output

        // Port 3.5
        P3SEL0 |= DAC_CNTL; // DAC_CNTL GPIO operation
        P3SEL1 |= DAC_CNTL; // DAC_CNTL GPIO operation
        P3OUT &= ~DAC_CNTL; // Initial Value = Low / Off
        P3DIR &= ~DAC_CNTL; // Direction = output  ---- Crosscheck once

        // Port 3.6
        P3SEL0 &= ~IOT_LINK_GRN; // IOT_LINK_GRN GPIO operation
        P3SEL1 &= ~IOT_LINK_GRN; // IOT_LINK_GRN GPIO operation
        P3OUT &= ~IOT_LINK_GRN; // Initial Value = Low / Off
        P3DIR |= IOT_LINK_GRN; // Direction = output

        // Port 3.7
        P3SEL0 &= ~IOT_EN; // IOT_LINK_GRN GPIO operation
        P3SEL1 &= ~IOT_EN; // IOT_LINK_GRN GPIO operation
        P3OUT &= ~IOT_EN; // Initial Value = Low / Off
        P3DIR |= IOT_EN; // Direction = output

    }

    void Init_Port4(void){ // Configure PORT 4
    //------------------------------------------------------------------------------
     P4OUT = 0x00; // P4 set Low
     P4DIR = 0x00; // Set P4 direction to output

     //Port 4.0
     P4SEL0 &= ~RESET_LCD; // RESET_LCD GPIO operation
     P4SEL1 &= ~RESET_LCD; // RESET_LCD GPIO operation
     P4OUT &= ~RESET_LCD; // Initial Value = Low / Off
     P4DIR |= RESET_LCD; // Direction = output

     //Port 4.1
     P4SEL0 &= ~SW1; // SW1 GPIO operation
     P4SEL1 &= ~SW1; // SW1 GPIO operation
     P4OUT |= SW1; // Configure pullup resistor
     P4DIR &= ~SW1; // Direction = input
     P4REN |= SW1; // Enable pullup resistor
     P4IES |= SW1;
     P4IFG &= ~SW1;
     P4IE |= SW1;


     //Port 4.2
     P4SEL0 |= UCA1TXD; // USCI_A1 UART operation
     P4SEL1 &= ~UCA1TXD; // USCI_A1 UART operation

     //Port 4.3
     P4SEL0 |= UCA1RXD; // USCI_A1 UART operation
     P4SEL1 &= ~UCA1RXD; // USCI_A1 UART operation

     //Port 4.4
     P4SEL0 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
     P4SEL1 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
     P4OUT |= UCB1_CS_LCD; // Set SPI_CS_LCD Off [High]
     P4DIR |= UCB1_CS_LCD; // Set SPI_CS_LCD direction to output

     //Port 4.5
     P4SEL0 |= UCB1CLK; // UCB1CLK SPI BUS operation
     P4SEL1 &= ~UCB1CLK; // UCB1CLK SPI BUS operation

     //Port 4.6
     P4SEL0 |= UCB1SIMO; // UCB1SIMO SPI BUS operation
     P4SEL1 &= ~UCB1SIMO; // UCB1SIMO SPI BUS operation

     //Port 4.7
     P4SEL0 |= UCB1SOMI; // UCB1SOMI SPI BUS operation
     P4SEL1 &= ~UCB1SOMI; // UCB1SOMI SPI BUS operation

     //------------------------------------------------------------------------------
    }


    void Init_Port5(void){
        P5DIR = 0x00; // Set P1 direction to input
        P5OUT = 0x00; // P1 set Low

        //Port 5.0
         P5SELC |= V_BAT; // ADC input for V_BAT

         //Port 5.1
         P5SELC |= V_5_0; // ADC input for V_BAT

         //Port 5.2
         P5SELC |= V_DAC; // ADC input for V_DAC

         //Port 5.3
         P5SELC |= V_3_3; // ADC input for V_3_3

         //Port 5.4
         P5SEL0 &= ~IOT_BOOT; // IOT_BOOT GPIO operation
         P5SEL1 &= ~IOT_BOOT; // IOT_BOOT GPIO operation
         P5OUT |= IOT_BOOT; // Set Output value inactive
         P5DIR |= IOT_BOOT; // Set direction to output

    }
    void Init_Port6(void){
        P6OUT = 0x00; // P6 set Low
        P6DIR = 0x00; // Set P6 direction to output

        // Port 6.0
        P6SEL0 |= LCD_BACKLITE; // LCD_BACKLITE GPIO operation
        P6SEL1 &= ~LCD_BACKLITE; // LCD_BACKLITE GPIO operation
        //P6OUT &= ~LCD_BACKLITE; // Initial Value = High/On
        P6DIR |= LCD_BACKLITE; // Direction = output

        // Port 6.1
        P6SEL0 |= R_FORWARD ; // R_FORWARD GPIO operation
        P6SEL1 &= ~R_FORWARD; // R_FORWARD GPIO operation
        //P6OUT &= ~R_FORWARD; // Initial Value = low/Off
        P6DIR |= R_FORWARD; // Direction = output

        // Port 6.2
        P6SEL0 |= L_FORWARD ; // L_FORWARD GPIO operation
        P6SEL1 &= ~L_FORWARD; // L_FORWARD GPIO operation
        //P6OUT &= ~L_FORWARD; // Initial Value = low/Off
        P6DIR |= L_FORWARD; // Direction = output

        // Port 6.3
        P6SEL0 |= R_REVERSE ; // R_REVERSE GPIO operation
        P6SEL1 &= ~R_REVERSE; // R_REVERSE GPIO operation
        //P6OUT &= ~R_REVERSE; // Initial Value = low/Off
        P6DIR |= R_REVERSE; // Direction = output

        // Port 6.4
        P6SEL0 |= L_REVERSE; // L_REVERSE GPIO operation
        P6SEL1 &= ~L_REVERSE; // L_REVERSE GPIO operation
        //P6OUT &= ~L_REVERSE; // Initial Value = low/Off
        P6DIR |= L_REVERSE; // Direction = output

        // Port 6.5
        P6SEL0 &= ~P6_5; // P6_5 GPIO operation
        P6SEL1 &= ~P6_5; // P6_5 GPIO operation
        P6OUT &= ~P6_5; // Initial Value = low/Off
        P6DIR |= P6_5; // Direction = output

        // Port 6.6
        P6SEL0 &= ~GRN_LED; // GRN_LED GPIO operation
        P6SEL1 &= ~GRN_LED; // GRN_LED GPIO operation
        P6OUT |= GRN_LED; // Initial Value = High/Off
        P6DIR |= GRN_LED; // Direction = output


    }



