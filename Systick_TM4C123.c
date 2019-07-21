#include"TM4C123.h"
#include<stdbool.h>
#define ONESEC		16000000-1
#define GREEN   (1U<<3)

void Systick_Init(void);
bool Timeout(void);


int main()
{
	SYSCTL->RCGCGPIO |=0x20;
	GPIOF->DIR|=GREEN;
	GPIOF->DEN|=GREEN;


	Systick_Init();
	while(1)
	{
		if(Timeout()) //check if counter reached 0 or not 
		{
			GPIOF->DATA ^=GREEN;
		}
	}


	return 0 ;
}

void Systick_Init(void)
{
	SysTick->LOAD=ONESEC; //will count down from  this number till 0 each 1 second 
	SysTick->CTRL=5; //enable systick 

}

bool Timeout(void)
{
	return SysTick->CTRL &0x10000;
}