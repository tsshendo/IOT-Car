//******************************************************************************
//
//  Description: This file contains the Function prototypes
//
//  Jim Carlson
//  Aug 2013
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************
// Functions

// Main
void main(void);

// Initialization
void Init_Conditions(void);

// Interrupts
void enable_interrupts(void);
__interrupt void Timer0_B0_ISR(void);
__interrupt void switchP2_interrupt(void);
__interrupt void switchP4_interrupt(void);
// Analog to Digital Converter

// Clocks
void Init_Clocks(void);

// LED Configurations
void Init_LEDs(void);
void IR_LED_control(char selection);
void Backlite_control(char selection);

  // LCD
void Display_Process(void);
void Display_Update(char p_L1,char p_L2,char p_L3,char p_L4);
void enable_display_update(void);
void update_string(char *string_data, int string);
void Init_LCD(void);
void lcd_clear(void);
void lcd_putc(char c);
void lcd_puts(char *s);

void lcd_power_on(void);
void lcd_write_line1(void);
void lcd_write_line2(void);
//void lcd_draw_time_page(void);
//void lcd_power_off(void);
void lcd_enter_sleep(void);
void lcd_exit_sleep(void);
//void lcd_write(unsigned char c);
//void out_lcd(unsigned char c);

void Write_LCD_Ins(char instruction);
void Write_LCD_Data(char data);
void ClrDisplay(void);
void ClrDisplay_Buffer_0(void);
void ClrDisplay_Buffer_1(void);
void ClrDisplay_Buffer_2(void);
void ClrDisplay_Buffer_3(void);

void SetPostion(char pos);
void DisplayOnOff(char data);
void lcd_BIG_mid(void);
void lcd_BIG_bot(void);
void lcd_120(void);

void lcd_4line(void);
void lcd_out(char *s, char line, char position);
void lcd_rotate(char view);

//void lcd_write(char data, char command);
void lcd_write(unsigned char c);
void lcd_write_line1(void);
void lcd_write_line2(void);
void lcd_write_line3(void);

void lcd_command( char data);
void LCD_test(void);
void LCD_iot_meassage_print(int nema_index);

// Menu
void Menu_Process(void);

// Ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
//void Init_Port3(char smclk);
void Init_Port3(void);
void Init_Port4(void);
void Init_Port5(void);
void Init_Port6(void);

// SPI
void Init_SPI_B1(void);
void SPI_B1_write(char byte);
void spi_rs_data(void);
void spi_rs_command(void);
void spi_LCD_idle(void);
void spi_LCD_active(void);
void SPI_test(void);
void WriteIns(char instruction);
void WriteData(char data);

// Switches
void Init_Switches(void);
void switch_control(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void disable_switch_SW1(void);
void disable_switch_SW2(void);
void Switches_Process(void);
void Init_Switch(void);
void Switch_Process(void);
void Switch1_Process(void);
void Switch2_Process(void);
void menu_act(void);
void menu_select(void);

// Timers
void Init_Timers(void);
void Init_Timer_B0(void);
void Init_Timer_B1(void);
void Init_Timer_B2(void);
void Init_Timer_B3(void);

void usleep(unsigned int usec);
void usleep10(unsigned int usec);
void five_msec_sleep(unsigned int msec);
void measure_delay(void);
void out_control_words(void);

// Project 4 Function Declaration

void wait_case(void);
void start_case(void);
void run_circle_case(void);
void Run_Fig8_case(void);
void Run_Triangle_case(void);
void run_case(void);
void end_case(void);
void Run_Straight(void);
void Run_Circle(void);
void Run_Fig_Eight(void);
void Run_Triangle (void);

void Switch1_Process(void);
void Switch2_Process(void);

// Movement Cases
void movement(void);
void Forward_On(void);
void Forward_Move(void);
void Forward_Off(void);
void Movement_Off(void);
void Smoke_Case(void);
void Reverse_On(void);
void Spin_Clock(void);
void Spin_AntiClock(void);

// Display numbers
void HEXtoBCD(int hex_value);
void adc_line(char line, char location);
void IR_Readings(void);
void Init_ADC(void);
void wait_case2(void);

// DAC Controls
void Init_REF(void);
void Init_DAC(void);

// serial communication

void Init_Serial_UCA0(char speed);
void Init_Serial_UCA1(char speed);
void USCI_A0_transmit(void);
void USCI_A1_transmit(void);
void IOT_Process(void);
void wait(void);
