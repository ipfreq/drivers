#include"lcd_TM4C123.h"

int main(int argc, char const *argv[])
{
	LCD_Init();
	LCD_Cmd(0x01);
	LCD_Cmd(0x08);
	delay_milli(500);
	LCD_Data ('C' );
	delay_milli(1);
	LCD_Data ('M' );
	delay_micro(500);

	return 0;
}
void LCD_Init(void)
{
	// Enable clock to GPIO Port 
	//Set GPIO Pins as an output pins 
	// Enable GPIO Pins
	//Function set command  	0x38= 8-bit , 2 display 2x7 font 
	//Entry mode set command    0x06 = increment automatically 
	//Display control      		0x0f = turn on display cursor blinking
	// Display control      	0x01 =clear display
	SYSCTL->RCGCGPIO|=(0x01|0x02);
	GPIOA->DIR|=0xE0;
	GPIOA->DEN|=0xE0;
	GPIOB->DIR|=0xFF;
	GPIOB->DEN|=0xFF;
	LCD_Cmd(0x38); // 8-bits , 2 line display , 5x7 font 
	//LCD_Cmd(0x28); // 4-bits . ......
	LCD_Cmd(0x06); // increment automatically 
	LCD_Cmd(0x0F); // Turn on display
	LCD_Cmd(0x01); //clear display


}


void LCD_Cmd(unsigned char command)
{
	//Select command register  RS=0 to select command 
	//Wrie command 
	//Secure command  send a pulse set E high for a brief moment 
	// set back to command register 
	// Delay to allow lcd execute commands MCU is too fast compared with LCD

	GPIOA->DATA=0x00; //RS=0, RW=0 , E=0 
	GPIOA->DATA=command; 
	GPIOA->DATA=0x80;
	delay_micro(0);
	GPIOA->DATA=0x00;
	if (command<4)
		delay_milli(2);
	else 
		delay_micro(37);

}


void LCD_Data (unsigned char data )
{
	//Select data regiser RS=1 
	//Write data 
	//Secure data E= high for a brief moment 
	//set back to command register  RS=0
	//Delay to allow LCD to catch up with MCU
	GPIOA->DATA=0x20; // 0b0010 0000 RS=1 RW=0 E=0
	GPIOA->DATA=data;
	GPIOA->DATA=0x80; // 0B 1000 0000
	GPIOA->DATA=0x00;
	delay_micro(0);
}


void delay_milli(int n)
{
		int i, j;
	for (i=0;i<n;i++)
	{
		for (j=0;j<3180;j++)
		{

		}
	}
	//do nothing for n mili seconds
}

void delay_micro(int n)
{
	int i, j;
	for (i=0;i<n;i++)
	{
		for (j=0;j<3;j++)
		{

		}
	}
	//do nothing for n micro seconds
}


void LCD_Write4bits(unsigned char data, unsigned char control)
{
	data&=0xF0;  // clear lower 4 bits 
	control &=0x0F; // clear upper 4 bits 
	LCD->DATA=data|control; 
	LCD->DATA=data|control|EN;
	delay_micro(0);
	LCD->DATA=data;
	if(command<4)
		delay_milli(2);
	else
		delay_micro(40);

}

void LCD_4bits_Init(void)
{

	SYSCTL->RCGCGPIO|=(0x01|0x02);
	LCD->DIR|=0xFF; 
	LCD->DEN|=0xFF;
	LCD4bits_Cmd(0x28);
	LCD4bits_Cmd(0x06);
	LCD4bits_Cmd(0x01);
	LCD4bits_Cmd(0x0F);



}


void LCD4bits_Data(unsigned char data)
{
	LCD_Write4bits(data&0xF0,RS);
	LCD_Write4bits(data<<4,RS);
	delay_micro(40);




void LCD4bits_Cmd(unsigned char command)
{
	LCD_Write4bits(command&0xF0,0);
	LCD_Write4bits(command<<4,0);
	if(command<<4)
		delay_milli(2);
	else 
		delay_micro(40);
}