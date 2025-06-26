/*
 * Interrupts_IOT.c
 *
 *  Created on: Mar 24, 2024
 *      Author: 13364
 */
#include "msp430.h"
#include "ports.h"
#include "functions.h"
#include "macros.h"
#include <string.h>


// Globals
extern char display_line[4][11];
extern volatile unsigned char display_changed;

// Serial
volatile unsigned char IOT_2_PC[SMALL_RING_SIZE];
volatile unsigned int iot_rx_wr;
unsigned int iot_rx_rd;
unsigned int direct_iot;

volatile unsigned char PC_2_IOT[SMALL_RING_SIZE];
volatile unsigned int usb_rx_wr;
unsigned int usb_rx_rd;
unsigned int direct_usb;
int ip_address_found;
extern volatile char iot_TX_buf[16];
extern volatile char IOT_Ring_Rx[16];
extern volatile char USB_Ring_Rx[16];
char inter_buffer[16];
char temp_usb_buf[16];

char process_buffer[16]; // Size for appropriate Command Length
char pb_index; // Index for process_buffer

extern volatile int iot_tx;
int message_done;
extern int case_no;
extern char move;
int i;
// UCA0 uses IOT Module
extern int sec_count;
int command_val=0;

#pragma vector = EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){ //This interrupt is the interrupt relating to serial communication port UCA0
 //------------------------------------------------------------------------------
 // Interrupt name: eUSCI_A0_ISR
 // Description: This interrupt transmits and receives through UCA0
 //------------------------------------------------------------------------------
 char iot_receive;
// int temp_char;
// int i;
 switch(__even_in_range(UCA0IV,0x08)){
 case 0: break; //Vector 0 - no interrupt
 case 2:{ // Vector 2 – Rx0IFG
 iot_receive = UCA0RXBUF;
 UCA1TXBUF = iot_receive; //  Add to Ring Buffer
 process_buffer[iot_rx_wr++] = iot_receive; //  Add to Ring Buffer
 if(iot_rx_wr >= sizeof(process_buffer)){
 iot_rx_wr = BEGINNING;
 }
 if(process_buffer[iot_rx_wr] == '^'){
     move=process_buffer[iot_rx_wr+1];
 }

 //UCA0TXBUF = iot_receive;
 }break;
 case 4:{ // Vector 4 – Tx0IFG
 UCA0TXBUF = iot_TX_buf[iot_tx];
 iot_TX_buf[iot_tx++] = 0;
 if(iot_TX_buf[iot_tx] == 0x00){
     iot_tx = 0;
     UCA0IE &= ~UCTXIE;
 }
 }break;
 default: break;
 }
}
//------------------------------------------------------------------------------

// UCA1 uses PC (USB)

#pragma vector = EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){ //This interrupt is the interrupt relating to serial communication port UCA1
 //------------------------------------------------------------------------------
 // Interrupt name: eUSCI_A1_ISR
 // Description: This interrupt transmits and receives through UCA1
 //------------------------------------------------------------------------------
 char usb_value;
 switch(__even_in_range(UCA1IV,0x08)){
 case 0:
     break; //Vector 0 - no interrupt
 case 2:{ // Vector 2 - Rx1IFG
 usb_value = UCA1RXBUF;
 UCA0TXBUF = usb_value; // Add to Ring Buffer
 USB_Ring_Rx[usb_rx_wr++] = usb_value; // Add to Ring Buffer
  if(usb_rx_wr >= sizeof(USB_Ring_Rx)){
  usb_rx_wr = BEGINNING;
  }

 }break;
 case 4:{ // Vector 4 - TX1IFG
     UCA1TXBUF = IOT_Ring_Rx[direct_usb];
     IOT_Ring_Rx[direct_usb++] = 0;
      if(IOT_Ring_Rx[direct_usb] == 0x00){
          UCA1IE &= ~UCTXIE;
          iot_tx = 0;
      }

 }break;
 default:
 break;
 }
 //------------------------------------------------------------------------------
}




