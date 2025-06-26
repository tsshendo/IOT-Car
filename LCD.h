//------------------------------------------------------------------------------
// Macro Configurations for the LCD
//------------------------------------------------------------------------------
// LCD
void enable_display_update(void);
void update_string(char *string_data, int string);
void Init_LCD(void);
void lcd_clear(void);
void lcd_putc(char c);
void lcd_puts(char *s);

void Write_LCD_Ins(char instruction);
void Write_LCD_Data(char data);
void ClrDisplay(void);
void ClrDisplay_Buffer_0(void);
void ClrDisplay_Buffer_1(void);
void ClrDisplay_Buffer_2(void);
void ClrDisplay_Buffer_3(void);
unsigned char CheckBusy(void);

void SetPostion(char pos);
void DisplayOnOff(char data);
void lcd_BIG_mid(void);
void lcd_BIG_bot(void);
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
void Display_Process(void);
void Display_Update(char p_L1,char p_L2,char p_L3,char p_L4);
int wait_for_character(void);
void print_CR(void);
void outchar(char character);

//------------------------------------------------------------------------------

#define NULL ((void *) 0x0)
//#define LCD_INTERVAL         12500 // 8,000,000 / 8 / 8 / [1/100msec] = 12500

// LCD
#define LCD_HOME_L1           0x80
#define LCD_HOME_L2           0xA0
#define LCD_HOME_L3           0xC0
#define LCD_HOME_L4           0xE0

#define DISPLAY_ON 	          0x04
#define DISPLAY_OFF           0x03
#define CURSOR_ON             0x02
#define CURSOR_OFF            0x05
#define BLINK_ON              0x01
#define BLINK_OFF             0x06
#define BOTTOM                0x05
#define TOP                   0x06

#define CLEAR_DISPLAY         0x01
#define RETURN_HOME           0x02
#define POWER_DOWN_MODE       0x02
#define PD_BIT                0x01 // (set = enter power down mode)
#define ENTRY_MODE_SET        0x04
#define ID_BIT                0x02
#define S_BIT                 0x01
#define BDC_BIT               0x02
#define BDS_BIT               0x01
#define DISPLAY_CONTROL       0x08
#define D_BIT                 0x04
#define EXTENDED_FUNCTION_SET 0x08
#define FW_BIT                0x04
#define BW_BIT                0x02
#define NW_BIT                0x01
#define DH_BIAS_DOT_SHIFT     0x10
#define UD2_BIT               0x08
#define UD1_BIT               0x04
#define BS1_BIT               0x02
#define DH2_BIT               0x01
#define INTERNAL_OSC_FREQ     0x10
#define BS0_BIT               0x08
#define F2_BIT                0x04
#define F1_BIT                0x02
#define F0_BIT                0x01
#define FUNCTION_SET          0x20
#define DL_BIT                0x10
#define N_BIT                 0x08
#define DH_BIT                0x04
#define BE_BIT                0x04
#define RE_BIT                0x02
#define IS_BIT                0x01
#define REV_BIT               0x01
#define POWER_CONTROL         0x50
#define BON_BIT               0x04
#define C5_BIT                0x02
#define C4_BIT                0x01
#define FOLLOWER_CONTROL      0x60
#define DON_BIT               0x08
#define RAB2_BIT              0x04
#define RAB1_BIT              0x02
#define RAB0_BIT              0x01

#define START_WR_INSTRUCTION  0x1f
#define START_WR_DATA         0x5f

