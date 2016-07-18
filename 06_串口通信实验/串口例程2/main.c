/*********************************************************
  > File Name: 串口通信实验2
  > Author: pengshp
  > Mail: pengshp3@outlook.com
  > Date: 2016年 3 月 26 日
***********************************************************/

#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int

uchar flag,i;
void init_UART()
{
	SCON=0x50;
	TMOD=0x20;
	PCON=0x80;
	TH1=0xF3;
	TL1=0XF3;
	EA=1;
	ES=1;
	TR1=1;
}


int main()
{
	init_UART();
	while(1)
	{
		if(flag==1)
		{
			ES=0;
			flag=0;
			SBUF=i;
			while(!TI);
			TI=0;
			ES=1;
		}
	}
	return 0;
}

void serial() interrupt 4
{
	RI=0;
	i=SBUF;
	flag=1;
}