
#define RS           //register select signal(command, data)
#define RW          //read and write signal(read=1,write=0)
#define EN         //enable signal from high to low
#define FLAG      //busy flag signal high until the data be processed

#define LCD_DATA  // data lines address

#define LCD_STROBE()  ((EN=1),(EN=0))

void lcd_write(unsigned char);
void lcd_clear(void);
void lcd_putch(char);
void lcd_puts(const char *);
void lcd_cursor(unsigned char);
void lcd_init(unsigned char initVal,unsigned char mode);
