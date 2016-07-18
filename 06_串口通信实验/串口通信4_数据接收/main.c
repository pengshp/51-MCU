/**************************************
  > File Name: 串口数据接收PC->MCU
  > Author: pengshp
  > Mail: pengshp3@outlook.com
  > Date: 2016 年 3 月 27 日
  > 说明：把收到的数据通过P2控制8个小灯的亮灭
***************************************/
#include<reg51.h>
#include<stdio.h>
#define uchar unsigned char
#define uint unsigned int

uchar tmp;
void init_UART()
{
	SCON=0x50;
	TMOD=0x20;
	PCON=0x00; //波特率加倍
	TH1=0xFD;  //波特率9600
	TL1=TH1;
	TR1=1;
}

uchar UART_Rec()
{
	uchar g_Uart_Reval;
	if(RI)//RI=1,说明数据接收完毕
	{
		g_Uart_Reval=SBUF;//读取缓冲器的数据
		RI=0;             //软件清零
	}
	return g_Uart_Reval;
}
int main()
{
	init_UART();
	/*
	TI=1;
	printf("I love you");
	while(!TI);
	TI=0;
	*/
	
	while(1)
	{
		tmp=UART_Rec();
		if(tmp=='1')
		{
			P2=0xFF;
		}
		else if (tmp=='0')
		{
			P2=0x55;
		}
	}
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