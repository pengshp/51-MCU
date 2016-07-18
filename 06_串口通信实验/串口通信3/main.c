/**************************************
  > File Name: 串口数据发送实验【MCU->PC】
  > Author: pengshp
  > Mail: pengshp3@outlook.com
  > Date: 2016 年 3 月 27 日
***************************************/
#include<reg51.h>

#define uchar unsigned char
#define uint unsigned int

uchar code TAB1[]="I love you 普中科技 51-MCU\n";
void init_UART()
{
	SCON=0x50;
	TMOD=0x20;
	PCON=0x80; //波特率加倍
	TH1=0xF4;  //波特率4800
	TL1=TH1;
	//EA=1;
	//ES=1;
	TR1=1;
}

void SendOneByte(uchar c)
{
	SBUF=c;
	while(!TI);//等待数据发送完
	TI=0;
}

void SendStr(uchar *pStr)
{
	while(*pStr)
	{
		SendOneByte(*pStr++);
	}
}
int main()
{
	uchar a='a';
	init_UART();
	//SendOneByte(a);
	SendStr(TAB1);
	while(1);
	return 0;
}

//void UARTInterrupt() interrupt 4
//{
//	if(RI)
//	{
//		RI=0;
//		
//	}
//	else
//		TI=0;
//}