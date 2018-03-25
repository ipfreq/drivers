#include"lcd.h"

void lcd_write(unsigned char c)
{
  while(FLAG);
  LCD_DATA=((c>>4)&0x0f);
  LCD_STROBE();
  LCD_DATA=(c&0x0f);
  LCD_STROBE();
}

void lcd_clear(void)
{
  RS=0;     //SETTING COMMAND MODE.
  lcd_write(0x1);
}

void lcd_putch(char c)
{
    RS=1;  //SETTING DATA MODE.
    lcd_write(c);
}

void lcd_puts(const char* st)
{
  RS=1;
  while(*st)
  lcd_write(*st++);
}
void lcd_cursor(unsigned char position)
{
  RS=0; //COMMAND MODE.
  lcd_write(0x80+position);
}

void lcd_init(void)
{
  char initVal=0x3;
  RS=0;
  EN=0;
  RW=0;
  __delay_ms(15); //waiting 15 milli second.
  LCD_DATA=initVal;
  LCD_STROBE();
  __delay_ms(5);
  LCD_STROBE();
  __delay_ms(200);
  LCD_STROBE();
  __delay_ms(200);
  LCD_DATA=2; //FOUR BIT MODE.
  LCD_STROBE();
	lcd_write(0x28);// init LCD in 4-bit mode with 2 lines and 5x7 matrix
	lcd_write(0xF); // Display On, Cursor On, Cursor Blinking
	lcd_clear();	// Clear screen
	lcd_write(0x6); // Set entry Mode
}
