#include "tm4c123.h"


#define RED			(1U<<1)

void periodic_timer(int times);

void timer1_oneshot(int mdelay);


int main()
{
	SYSCTL->RCGCGPIO |=0X20 ; 
	GPIOF->DIR|=RED;
	GPIOF->DEN|=RED;

	while(1)
	{
		GPIOF->DATA^=RED;
		//timer1_oneshot(4);
		periodic_timer(200);

	}
	return 0 ;
}


void timer1_oneshot(int mdelay)
{
	SYSCTL->RCGCTIMER|=0X01; 
	TIMER0->CTL=0;
	TIMER0->CFG=0x04; // 16- bits
	TIMER0->TAMR=0X01; // ONE-SHOT 
	TIMER0->TAILR=16000*mdelay-1;
	TIMER0->ICR=0x1;
	TIMER0->CTL|=0X01; //enable interrupt again 
	while((TIMER0->RIS&0X01)==0); // wait for timeout flag to set 
}


void periodic_timer(int times)
{
	int j=0;
	SYSCTL->RCGCTIMER|=0X01; 
	TIMER0->CTL=0x0;
	TIMER0->CFG=0x04; // 16- bits
	TIMER0->TAMR=0X02; // periodic timer
	TIMER0->TAILR=16000-1; // 1mili seconds
	TIMER0->ICR=0x1;
	TIMER0->CTL|=0X01; //enable interrupt again 
	for(j=0;j<times;j++)
	while((TIMER0->RIS&0X01)==0); // wait for timeout flag to set 



}