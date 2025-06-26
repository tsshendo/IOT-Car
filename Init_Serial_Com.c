/*
 * Init_Serial_Com.c
 *
 *  Created on: Mar 24, 2024
 *      Author: 13364
 */

#include "msp430.h"
#include "ports.h"
#include "functions.h"
#include "macros.h"
#include <string.h>

// IOT Variable declarations
// Serial
volatile unsigned char IOT_2_PC[SMALL_RING_SIZE];
extern volatile unsigned int iot_rx_wr;
unsigned int iot_rx_rd; // Only used in Main
unsigned int direct_iot; // Only used it Interrupt
volatile unsigned char PC_2_IOT[SMALL_RING_SIZE];
volatile unsigned int usb_rx_wr;
unsigned int usb_rx_rd; // Only used in Main
unsigned int direct_usb; // Only used it Interrupt
int ip_address_found;

char process_buffer[25]; // Size for appropriate Command Length
char pb_index; // Index for process_buffer
int i;
int line;
int nextline;
int iot_tx;
char iot_TX_buf[16];
char IOT_Ring_Rx[16];
char USB_Ring_Rx[16];
char AT[16];
char IOT_Data[4][16];
char ip_mac[16];
char ip_address[16];
int boot_state;
int character;
int test_Value;

//
int i;
unsigned int iot_rx_wr_temp;
// Display variables
extern char display_line[4][11];
extern char *display[4];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
int IOT_parse;
int iot_index;
// UCA0 is used for IOT module to transmit and receive

void Init_Serial_UCA0(char speed){
//------------------------------------------------------------------------------
// TX error (%) RX error (%)
// BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
// 8000000 4800 1 104 2 0xD6 -0.08 0.04 -0.10 0.14
// 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
// 8000000 19200 1 26 0 0xB6 -0.08 0.16 -0.28 0.20
// 8000000 57600 1 8 10 0xF7 -0.32 0.32 -1.00 0.36
// 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
// 8000000 460800 0 17 0 0x4A -2.72 2.56 -3.76 7.28
//------------------------------------------------------------------------------
// Configure eUSCI_A0 for UART mode
 UCA0CTLW0 = 0;
 UCA0CTLW0 |= UCSWRST ; // Put eUSCI in reset
 UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
 UCA0CTLW0 &= ~UCMSB; // MSB, LSB select
 UCA0CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
 UCA0CTLW0 &= ~UCPEN; // No Parity
 UCA0CTLW0 &= ~UCSYNC;
 UCA0CTLW0 &= ~UC7BIT;
 UCA0CTLW0 |= UCMODE_0;
// BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
// 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
// UCA?MCTLW = UCSx + UCFx + UCOS16
 UCA0BRW = 4 ; // 115,200 baud
 UCA0MCTLW = 0x5551 ;
 UCA0CTLW0 &= ~UCSWRST ; // release from reset
//UCA0TXBUF = 0x00; // Prime the Pump
 UCA0IE |= UCRXIE; // Enable RX interrupt
//------------------------------------------------------------------------------
}

// UCA1 is used for the USB connected to a laptop to transmit and receive
void Init_Serial_UCA1(char speed){
//------------------------------------------------------------------------------
// TX error (%) RX error (%)
// BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
// 8000000 4800 1 104 2 0xD6 -0.08 0.04 -0.10 0.14
// 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
// 8000000 19200 1 26 0 0xB6 -0.08 0.16 -0.28 0.20
// 8000000 57600 1 8 10 0xF7 -0.32 0.32 -1.00 0.36
// 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
// 8000000 460800 0 17 0 0x4A -2.72 2.56 -3.76 7.28
//------------------------------------------------------------------------------
// Configure eUSCI_A0 for UART mode
 UCA1CTLW0 = 0;
 UCA1CTLW0 |= UCSWRST ; // Put eUSCI in reset
 UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
 UCA1CTLW0 &= ~UCMSB; // MSB, LSB select
 UCA1CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
 UCA1CTLW0 &= ~UCPEN; // No Parity
 UCA1CTLW0 &= ~UCSYNC;
 UCA1CTLW0 &= ~UC7BIT;
 UCA1CTLW0 |= UCMODE_0;
// BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
// 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
// UCA?MCTLW = UCSx + UCFx + UCOS16
 UCA1BRW = 4 ; // 115,200 baud
 UCA1MCTLW = 0x5551 ;       // Set Baud rate
 UCA1CTLW0 &= ~UCSWRST ; // release from reset
//UCA1TXBUF = 0x00; // Prime the Pump
 UCA1IE |= UCRXIE; // Enable RX interrupt
//------------------------------------------------------------------------------
}


void USCI_A0_transmit(void){ // Transmit Function for USCI_A0
// Contents must be in process_buffer
// End of Transmission is identified by NULL character in process_buffer
// process_buffer includes Carriage Return and Line Feed
pb_index = 0; // Set Array index to first location
UCA0IE |= UCTXIE; // Enable TX interrupt
}

void USCI_A1_transmit(void){ // Transmit Function for USCI_A0
// Contents must be in process_buffer
// End of Transmission is identified by NULL character in process_buffer
// process_buffer includes Carriage Return and Line Feed
pb_index = 0; // Set Array index to first location
UCA1IE |= UCTXIE; // Enable TX interrupt
}

void IOT_Process(void){ // Process IOT messages
     iot_rx_wr_temp = iot_rx_wr;
     if(iot_rx_wr_temp != iot_rx_rd){ // Determine if IOT is available
     IOT_Data[line][character] = IOT_Ring_Rx[iot_rx_rd++];
     if(iot_rx_rd >= sizeof(IOT_Ring_Rx)){
     iot_rx_rd = BEGINNING;
     }
     }
     if(IOT_Data[line][character] == 0x0A){
     character = 0;
    line++;
     if(line >= 4){
     line = 0;
     }
     nextline = line + 1;
     if(nextline >= 4){
     nextline = 0;
     }
     }
     else{
         switch(character){
          case 0:
          if(IOT_Data[line][character] == '+'){ // Got "+"
          test_Value++;
          if(test_Value){
              P1OUT |= RED_LED; // Set Red LED On;
          }
          IOT_parse = 1;
          }
          break;
          case 1:
              P6OUT |= GRN_LED;
          break;
          case 4:
          if(IOT_Data[line][character] == 'y'){ // Got read"y"
          for(i=0; i<sizeof(AT); i++){
          iot_TX_buf[i] = AT[i];
          }
          UCA0IE |= UCTXIE;
          boot_state = 1;
          P1OUT |= RED_LED;
          P6OUT &= ~GRN_LED;
          }
          break;
          case 5:
           if(IOT_Data[line][character] == 'G'){ // Got IP
           for(i=0; i<sizeof(ip_mac); i++){
           iot_TX_buf[i] = ip_mac[i];
           }
           iot_tx = 0;
           UCA0IE |= UCTXIE;
           }
           break;
           case 6:
           break;
           case 10:
           if(IOT_Data[line][character] == 'I'){
           ip_address_found = 1;
           strcpy(display_line[0], "IP Address");
           for(i=0; i<sizeof(ip_address); i++){
           ip_address[i] = 0;
           }
           display_changed = TRUE;
           iot_index = 0;
           }
           break;
           default: break;
           }




    }
    }



