#include"TM4C123.h"


#define RS 1
#define RW 2
#define EN 4
#define LCD GPIOB
void LCD_Init(void);
void LCD_Cmd(unsigned char command);
void LCD_Data (unsigned char data );
void delay_milli(int n);
void delay_micro(int n);
void LCD_Write4bits(unsigned char data, unsigned char control);
void LCD_4bits_Init(void);
void LCD4bits_Data(unsigned char data);
void LCD4bits_Cmd(unsigned char);