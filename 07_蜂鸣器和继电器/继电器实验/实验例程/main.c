/**************************************
  > File Name: 继电器实验
  > Author: pengshp
  > Mail: pengshp3@outlook.com
  > Date: 2015年 7 月 25 日
***************************************/
#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int

sbit RELAY=P1^4;              //继电器位声明
sbit K1=P0^0;                 //开关K1位声明

void Delay(uint ms)
{
	uchar i;
	while(ms--)
	{
		for(i=120;i>0;i--);
	}
}
void main()
{
	RELAY=0;                  //继电器工作
	K1=1;
	while(1)
	{
		if(!K1)
		{
			Delay(50);
			if(K1==0)
			{
				while(!K1);   //等待按键释放
				RELAY=~RELAY; //继电器取反
			}
		}
	}
}