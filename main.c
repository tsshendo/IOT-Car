//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//  Jim Carlson
//  Jan 2023
//  Built with Code Composer Version: CCS12.4.0.00007_win64
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include  "LCD.h"
#include  "ports.h"
#include "macros.h"
#include <string.h>


// Function Prototypes
void main(void);
void Init_Conditions(void);
void Display_Process(void);
void Init_LEDs(void);
void Init_Ports(void);
void Init_Serial_UCA0(char speed);
void Init_Serial_UCA1(char speed);

  // Global Variables
volatile char slow_input_down;
extern char display_line[4][11];
extern char *display[4];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
unsigned int test_value;
char chosen_direction;
char change;
unsigned int wheel_move;
char forward;
int movement_no;
//char event = CIRCLE;
//char state= WAIT;
unsigned int Last_Time_Sequence; // a variable to identify Time_Sequence has changed
unsigned int cycle_time; // is a new time base used to control making shapes
unsigned int time_change; // is an identifier that a change has occurred
extern volatile int Time_Count;
int last_time_count;
extern int run_cases;
extern unsigned int ADC_Left_Detect; // = V_DETECT_L
extern unsigned int ADC_Right_Detect; //=V_DETECT_R
unsigned int ADC_Left_Detect_Proxy;
unsigned int ADC_Right_Detect_Proxy;
int ADC_Left_Detect_White;
int ADC_Right_Detect_White;
extern int seconds;

// New timer counter
int timestamp;
char Next_State = 'A';
char first_time_in_case;
int time_val;
unsigned int delay_start;
extern volatile int circle_time;
extern volatile int time_proj6;
int count_case=0;
int seconds_rec;

// Proj 9
extern int boot_sequence;
extern int boot_time;
// IOT Variable declarations
// Serial
volatile unsigned char IOT_2_PC[SMALL_RING_SIZE];
volatile unsigned int iot_rx_wr;
unsigned int iot_rx_rd; // Only used in Main
unsigned int direct_iot; // Only used it Interrupt
volatile unsigned char PC_2_IOT[SMALL_RING_SIZE];
volatile unsigned int usb_rx_wr;
unsigned int usb_rx_rd; // Only used in Main
unsigned int direct_usb; // Only used it Interrupt
int ip_address_found;

char process_buffer[25]; // Size for appropriate Command Length
char pb_index; // Index for process_buffer
extern int message_done;
extern char IOT_Ring_Rx[10];
extern char USB_Ring_Rx[10];
extern char iot_TX_buf[10];
extern char inter_buffer[10];
extern char temp_usb_buf[10];
int case_no=1;
extern int sec_count;
unsigned int i;
int x;
int time_proxy;
int autonomous;
char arrived_inc='0';
int exit_count=1;
// Movement case configurations
char move;
int move_forward;
extern volatile int auto_count;


void main(void){
//    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------

    PM5CTL0 &= ~LOCKLPM5;


// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings

  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_Timers();                       // Initialize Timers
  Init_LCD();                          // Initialize LCD
  Init_ADC();
  Init_REF();
  Init_DAC();
  Init_Serial_UCA0(0);
  Init_Serial_UCA1(0);



//P2OUT &= ~RESET_LCD;
  // Place the contents of what you want on the display, in between the quotes
// Limited to 10 characters per line
  strcpy(display_line[0], " WAITING  ");
  //strcpy(display_line[1], "          ");
  //strcpy(display_line[2], "          ");
  //strcpy(display_line[3], "          ");
  display_changed = TRUE;
  Display_Update(0,0,0,0);

  wheel_move = 0;
  forward = TRUE;

//------------------------------------------------------------------------------
// Beginning of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run
    //Switches_Process();                // Check for switch state change
    Display_Process();                 // Update Display
    LCD_BACKLITE_DIMING = OFF;
    //P2OUT |= IR_LED; // Turning IR LED on

    UCA0BRW = 4 ; // 115,200 baud
    UCA0MCTLW = 0x5551 ;

    IOT_Process();

    switch(case_no){
    case 1:
        P3OUT &= ~IOT_EN; // Initial Value = Low / Off
        autonomous=FALSE;
        break;
    case 2:
        P3OUT |= IOT_EN; // Initial Value = ON
        P2OUT |= IOT_RUN_RED; // Initial Value = Low / Off
        break;
    case 3:
        if(message_done==OFF){
            strcpy(iot_TX_buf,"AT+CIPMUX=1\r\n");
            UCA0IE |= UCTXIE;
            P1OUT &= ~RED_LED; // Set Red LED On
            message_done=OKAY;
        }
        break;
    case 4:
        if(message_done==OFF){
            strcpy(iot_TX_buf,"AT+CIPSERVER=1,8437\r\n");
            UCA0IE |= UCTXIE;
            message_done=OKAY;
            P1OUT |= RED_LED; // Set Red LED On
        }
        break;
    case 5:
        if(message_done==OFF){
            strcpy(iot_TX_buf,"AT+CWJAP?\r\n");
            UCA0IE |= UCTXIE;
            message_done=OKAY;
            strcpy(display_line[0], "   ncsu   ");
            display_changed = TRUE;
            P1OUT &= ~RED_LED; // Set Red LED On
        }
        break;
    case 6:
        if(message_done==OFF){
            strcpy(iot_TX_buf,"AT+CIFSR\r\n");
            UCA0IE |= UCTXIE;
            strcpy(display_line[1], "  GOT IP  ");
            display_changed = TRUE;
            P1OUT |= RED_LED; // Set Red LED On
            message_done=OKAY;
        }
    case 7:
        P1OUT &= ~RED_LED; // Set Red LED On
        if(process_buffer[iot_rx_wr] == 'P'){
            for(i=0;i<16;i++){
                    if((process_buffer[i] !=0x0D)& (process_buffer[i]!=0x0A)){
                        display_line[2][i]=process_buffer[i];
                    }
                    if(i>10){
                        if((process_buffer[i] !=0x0D)& (process_buffer[i]!=0x0A)){
                            display_line[3][i-9]=process_buffer[i];
                        }
                    }
                    display_changed = TRUE;
                }
            }
        break;
    case 8:
        P1OUT |= RED_LED; // Set Red LED On
        P2OUT |= IR_LED; // Turning IR LED on
        strcpy(display_line[2], "          ");
        strcpy(display_line[3], "          ");
        display_changed = TRUE;
        break;
    case 9:
        strcpy(display_line[2], " TANISHQ  ");
        display_changed = TRUE;
        P1OUT &= ~RED_LED; // Set Red LED On
        P2OUT &= ~IR_LED; // Turning IR LED on
        P3OUT |= IOT_LINK_GRN; // Initial Value = Low / Off
        seconds=0;
        switch(move){
        case FRONT:
            // forward movement
            strcpy(display_line[1], " CMND: ^F ");
            display_changed = TRUE;
            LEFT_FORWARD_SPEED= SLOW;  // 2 IS LEFT FORWARD
            RIGHT_FORWARD_SPEED=SLOW;  // 3 IS RIGHT FORWARD
            LEFT_REVERSE_SPEED= OFF;  // 4 IS LEFT REVERSE
            RIGHT_REVERSE_SPEED=OFF;  // 5 IS RIGHT REVERSE
            break;
        case BACK:
            // reverse movement
            strcpy(display_line[1], " CMND: ^B ");
            display_changed = TRUE;
            LEFT_FORWARD_SPEED= OFF;  // 2 IS LEFT FORWARD
            RIGHT_FORWARD_SPEED=OFF;  // 3 IS RIGHT FORWARD
            LEFT_REVERSE_SPEED= FAST;  // 4 IS LEFT REVERSE
            RIGHT_REVERSE_SPEED=SLOW;  // 5 IS RIGHT REVERSE
            break;
        case LEFT:
            // left movement
            strcpy(display_line[1], " CMND: ^L ");
            display_changed = TRUE;
            LEFT_FORWARD_SPEED= OFF;  // 2 IS LEFT FORWARD
            RIGHT_FORWARD_SPEED=SLOW;  // 3 IS RIGHT FORWARD
            LEFT_REVERSE_SPEED= FAST;  // 4 IS LEFT REVERSE
            RIGHT_REVERSE_SPEED=OFF;  // 5 IS RIGHT REVERSE
            break;
        case RIGHT:
            //Right Case - 90 deg
            strcpy(display_line[1], " CMND: ^R ");
            display_changed = TRUE;
            LEFT_FORWARD_SPEED= SLOW;  // 2 IS LEFT FORWARD
            RIGHT_FORWARD_SPEED=OFF;  // 3 IS RIGHT FORWARD
            LEFT_REVERSE_SPEED= OFF;  // 4 IS LEFT REVERSE
            RIGHT_REVERSE_SPEED=SLOW;  // 5 IS RIGHT REVERSE
            break;
        case ARRIVED:
            Movement_Off();
            arrived_inc++;
            strcpy(display_line[0], "ARRIVED 00");
            strcpy(display_line[1], " CMND: ^I ");
            display_line[0][9]=arrived_inc;
            display_changed = TRUE;
            move='Z';
            break;
        case FOR2SEC:
            strcpy(display_line[1], " CMND: ^M ");
            display_changed = TRUE;
            LEFT_FORWARD_SPEED= SLOW;  // 2 IS LEFT FORWARD
            RIGHT_FORWARD_SPEED=SLOW;  // 3 IS RIGHT FORWARD
            LEFT_REVERSE_SPEED= OFF;  // 4 IS LEFT REVERSE
            RIGHT_REVERSE_SPEED=OFF;  // 5 IS RIGHT REVERSE
            break;
        case DECREMENT:
            Movement_Off();
            arrived_inc--;
            strcpy(display_line[0], "ARRIVED 00");
            strcpy(display_line[1], " CMND: ^D ");
            display_line[0][9]=arrived_inc;
            display_changed = TRUE;
            move='Z';
            break;
        case EXIT:
            exit_count=OKAY;
            switch(exit_count){
            case 1:
                strcpy(display_line[0], " BL EXIT  " );
                display_changed = TRUE;
                LEFT_FORWARD_SPEED= FAST;  // 2 IS LEFT FORWARD
                RIGHT_FORWARD_SPEED=FAST;  // 3 IS RIGHT FORWARD
                LEFT_REVERSE_SPEED= OFF;  // 4 IS LEFT REVERSE
                RIGHT_REVERSE_SPEED=OFF;  // 5 IS RIGHT REVERSE
                break;
            case 2:
                Movement_Off();
                strcpy(display_line[0], " BL STOP  " );
                strcpy(display_line[1], " ECE 306  " );
                strcpy(display_line[3], "   OUT    ");
                display_changed = TRUE;
                break;
                default: break;
            }
            break;
            case STOP:
                // Stop case Motors off
                Movement_Off();
                break;
        case AUTO:
            P2OUT |= IR_LED; // Turning IR LED on
            strcpy(display_line[1], " CMND: ^A ");
            display_changed = TRUE;
            switch(count_case){
            case 0:
                strcpy(display_line[1], "INITIALIZE");
                display_changed = TRUE;
                Movement_Off();
                P2OUT |= IR_LED; // Turning IR LED on
                count_case=OKAY;
                break;
            case 1:
                strcpy(display_line[0], " BL START ");
                display_changed = TRUE;
                P2OUT |= IR_LED; // Turning IR LED on
                if((ADC_Left_Detect>ADC_Left_Detect_White) && (ADC_Right_Detect>ADC_Right_Detect_White)){
                    RIGHT_FORWARD_SPEED =PERCENT_80;
                    LEFT_FORWARD_SPEED =SLOW;
                    RIGHT_REVERSE_SPEED =OFF;
                    LEFT_REVERSE_SPEED = OFF;
                }
                else if((ADC_Left_Detect<ADC_Left_Detect_White) && (ADC_Right_Detect<ADC_Right_Detect_White)){
                    count_case=2;
                }
                move=AUTO;
                break;
            case 2:
                strcpy(display_line[0],"INTERCEPT ");
                display_changed = TRUE;
                if((ADC_Left_Detect<ADC_Left_Detect_Proxy) && (ADC_Right_Detect<ADC_Right_Detect_Proxy)){
                    RIGHT_FORWARD_SPEED =SLOW;
                    LEFT_FORWARD_SPEED =SLOW;
                    RIGHT_REVERSE_SPEED =OFF;
                    LEFT_REVERSE_SPEED = OFF;
                }
                if((ADC_Left_Detect>ADC_Left_Detect_Proxy) || (ADC_Right_Detect>ADC_Right_Detect_Proxy)){
                    strcpy(display_line[0], "INTERCEPT ");
                    display_changed = TRUE;
                    Movement_Off();
                    count_case=3;
                }
                move=AUTO;
                break;
            case 3:
                // find line
                strcpy(display_line[0], " INTERCEPT");
                display_changed = TRUE;
                Movement_Off();
                move=AUTO;
                break;

            case 4:
                strcpy(display_line[0], " BL TURN  ");
                display_changed = TRUE;
                LEFT_FORWARD_SPEED =SLOW;
                RIGHT_FORWARD_SPEED =OFF;
                RIGHT_REVERSE_SPEED =SLOW;
                LEFT_REVERSE_SPEED = OFF;
                move=AUTO;
                break;
            case 10:
                strcpy(display_line[0],"BL TRAVEL ");
                display_changed = TRUE;
                Movement_Off();
                move=AUTO;
                break;

            case 5:
                strcpy(display_line[0], "BL TRAVEL ");
                display_changed = TRUE;
                if((ADC_Left_Detect<ADC_Left_Detect_Proxy) && (ADC_Right_Detect>ADC_Right_Detect_Proxy)){
                    RIGHT_FORWARD_SPEED =OFF;
                    LEFT_FORWARD_SPEED = SLOW;
                    RIGHT_REVERSE_SPEED =OFF;
                    LEFT_REVERSE_SPEED = OFF;
                }
                else if((ADC_Left_Detect>ADC_Left_Detect_Proxy) && (ADC_Right_Detect<ADC_Right_Detect_Proxy)){
                    RIGHT_FORWARD_SPEED =SLOW;
                    LEFT_FORWARD_SPEED = OFF;
                    RIGHT_REVERSE_SPEED =OFF;
                    LEFT_REVERSE_SPEED = OFF;
                }
                else if((ADC_Left_Detect>ADC_Left_Detect_Proxy) && (ADC_Right_Detect>ADC_Right_Detect_Proxy)) {
                    RIGHT_FORWARD_SPEED =SLOW;
                    LEFT_FORWARD_SPEED = SLOW;
                    RIGHT_REVERSE_SPEED =OFF;
                    LEFT_REVERSE_SPEED = OFF;
                }
                else if((ADC_Left_Detect<ADC_Left_Detect_Proxy) && (ADC_Right_Detect<ADC_Right_Detect_Proxy)) {
                    RIGHT_REVERSE_SPEED =SLOW;
                    LEFT_REVERSE_SPEED = SLOW;
                    RIGHT_FORWARD_SPEED =OFF;
                    LEFT_FORWARD_SPEED = OFF;
                }
                move=AUTO;
                break;
                case 6:
                    strcpy(display_line[0],  "BL CIRCLE ");
                    display_changed = TRUE;
                    Movement_Off();
                    move=AUTO;
                    break;
                case 7:
                    P2OUT |= IR_LED; // Turning IR LED on
                    strcpy(display_line[0], "BL CIRCLE ");
                    display_changed = TRUE;
                    if((ADC_Left_Detect<ADC_Left_Detect_Proxy) && (ADC_Right_Detect>ADC_Right_Detect_Proxy)){
                        RIGHT_FORWARD_SPEED =OFF;
                        LEFT_FORWARD_SPEED = SLOW;
                        RIGHT_REVERSE_SPEED =OFF;
                        LEFT_REVERSE_SPEED = OFF;
                    }
                    else if((ADC_Left_Detect>ADC_Left_Detect_Proxy) && (ADC_Right_Detect<ADC_Right_Detect_Proxy)){
                        RIGHT_FORWARD_SPEED =SLOW;
                        LEFT_FORWARD_SPEED = OFF;
                        RIGHT_REVERSE_SPEED =OFF;
                        LEFT_REVERSE_SPEED = OFF;
                    }
                    else if((ADC_Left_Detect>ADC_Left_Detect_Proxy) && (ADC_Right_Detect>ADC_Right_Detect_Proxy)) {
                        RIGHT_FORWARD_SPEED =SLOW;
                        LEFT_FORWARD_SPEED = SLOW;
                        RIGHT_REVERSE_SPEED =OFF;
                        LEFT_REVERSE_SPEED = OFF;
                    }
                    else if((ADC_Left_Detect<ADC_Left_Detect_Proxy) && (ADC_Right_Detect<ADC_Right_Detect_Proxy)) {
                        RIGHT_REVERSE_SPEED =SLOW;
                        LEFT_REVERSE_SPEED = SLOW;
                        RIGHT_FORWARD_SPEED =OFF;
                        LEFT_FORWARD_SPEED = OFF;
                    }
                    break;
                case 8:
                    Movement_Off();
                    break;
                default: break;
                }
            break;
        default: break;
        }
        break;
    default: break;
    }


    //P3OUT ^= TEST_PROBE;               // Change State of TEST_PROBE OFF
//------------------------------------------------------------------------------

}
}
