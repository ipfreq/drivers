#include "TM4C123.h"


#define K_ROW GPIOE 
#define K_COL GPIOC 



void KEYPAD_init(void)
{
	SYSCTL->RCGCCPIO|=0x04; //Enable ProtC Clock 
	SYSCTL->RCGCCPIO|=0x01; //Enable PortE Clock
	K_ROW->DIR |=0x0F; // Set as output
	K_ROW->DEN|=0x0F; // Set Digital Enable 
	K_ROW->ODR|=0x0F;  // Set Open drain configuration 

	K_COL->DIR&=~0xF0; // Set PC4-7 as Input
	K_COL->DEN|=0xF0; 
	K_COL->PUR|=0xF0; // add pull-up resistor 

}

unsigned char getKey(void)
{
	const unsigned char keymap[4][4]={
		{'1','2','3','A'},
		{'4','5','6','B'},
		{'7','8','9','C'},
		{'*','0','#','D'},
	};
	uint8_t k_row,k_col;
	K_ROW->DATA=0x0;     // set low  
	k_col=K_COL->DATA&0xF0; // k_col 
	if(k_col==0xF0)
		return 0;// no key is pressed
	for(;;)
	{
		k_row=0;
		K_ROW->DATA=0x0E;
		delay_micro(10);
		k_col=K_COL->DATA&0xF0;
		if(k_col !=0xF0)
			break;
		k_row=1;
		K_ROW->DATA=0x0D; // 0000-1101
		delay_micro(10);
		k_col=K_COL->DATA&0xF0; // k_col 
		if(k_col!=0xF0)
			break;
		k_row=2;
		K_ROW->DATA=0x0B;
		delay_micro(10);
		k_col=K_COL->DATA&0xF0; // k_col 
		if(k_col!=0xF0)
			break;
		k_row=3;
		K_ROW->DATA=0x07;
		delay_micro(10);
		k_col=K_COL->DATA&0xF0; // k_col 
		if(k_col!=0xF0)
			break;

		return 0 ;
	}

	if(k_col==0xE0)
		return keymap[k_row][0];
	if(k_col==0xD0)
		return keymap[k_row]1];

	if(k_col==0xB0)
		return keymap[k_row][2];
	if(k_col==0x70)
		return keymap[k_row][3];
	return 0 ;



}