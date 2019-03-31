#include "reg52.h"
#include "intrins.h"
#include "stdio.h"

sfr INT_CLK=0x8f;


sbit UpKey=P3^6;//中断2

sbit StopKey=P3^2;//中断0

sbit LeftKey=P3^3;//中断1

sbit RightKey=P3^0;//中断4



void Init(void);
void Delayms(unsigned char Times);		//@11.0592MHz


unsigned char Flag=1;


int main(void)
{
	
	unsigned char i=0;

	Init();
	while(1)
	{
		switch(Flag)
		{
			case 1://正常行驶
				P1=0xFF;//全部熄灭
			
				break;
			
			case 2://右转
			
				P1=0xFE;//1111 1110
				Delayms(200);
				Delayms(200);
				for(i=0;i<=1;i++)
				{
					P1=_crol_(P1,1);
					Delayms(200);
					Delayms(200);
				}

				break;
			
			case 3:
			
				P1=0xDF;//1101 1111
				Delayms(200);
				Delayms(200);
				for(i=0;i<=1;i++)
				{
					P1=_cror_(P1,1);
					Delayms(200);
					Delayms(200);
					
				}
				break;//左转
			
			case 4://刹车
			
				P1=0x00;
				Delayms(200);
				Delayms(200);
				P1=0xFF;
				Delayms(200);
				Delayms(200);
			    P1=0x00;
				break;
			
			default:
				P1=0xFF;
		
		}
		
	}
}

void Init(void)
{
	INT0=1;
	IT0=1;
	EX0=1;
	
	
	INT1=1;
	IT1=1;
	EX1=1;
	
	INT_CLK|=0x40;//中断4
	INT_CLK|=0x10;//中断4
	
	EA=1;

}

//刹车
void exint0() interrupt 0
{
	Flag=4;
	
	
}

//LeftKey
void exint1() interrupt 2
{
	Flag=3;
	
	
}

//UpKey
void exint2() interrupt 10
{
	Flag=1;
	
	
}


//RightKey
void exint4() interrupt 16
{
	Flag=2;
}


void Delayms(unsigned char Times)		//@11.0592MHz
{
	unsigned char temp;
	unsigned char i, j;
	for(temp=0;temp<Times;temp++)
	{
		_nop_();
		_nop_();
		_nop_();
		i = 11;
		j = 190;
		do
		{
			while (--j);
		} while (--i);
	}
}
