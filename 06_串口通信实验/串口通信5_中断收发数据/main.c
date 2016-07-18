/**************************************
  > File Name: 中断实现收发数据
  > Author: pengshp
  > Mail: pengshp3@outlook.com
  > Date: 2016 年 3 月 28 日
***************************************/
#include <reg51.h>
#include <stdio.h>
#define uchar unsigned char
#define uint unsigned int
	
uint getDate=0;
bit RxTx_Flag=0;
void InitUART(void)
{
    TMOD = 0x20; //串口工作模式1
    SCON = 0x50;
    TH1 = 0xFA;  //波特率9600
    TL1 = TH1;
    PCON = 0x80; //波特率加倍
    EA = 1;      //总中断
    ES = 1;      //串口中断
    TR1 = 1;     //定时器1
}

void SendOneByte(unsigned char c)
{
    SBUF = c;
    while(!TI);
    TI = 0;
}

int main()
{
    InitUART();
	while(1)
	{
		if(RxTx_Flag)
		{
			RxTx_Flag=0;
			ES=0;//屏蔽外部中断，防干扰
			TI=1;printf("你给我一个:");while(!TI);TI=0;
			SBUF=getDate;
			while(!TI); //等待数据发送完毕
			TI=0;
			TI=1;printf("\n");while(!TI);TI=0;
			TI=1;printf("我给你一个ASCII: 0x%x",getDate);while(!TI);TI=0;
			TI=1;printf("\n");while(!TI);TI=0;
			ES=1; //开中断标志位
		}//只能发送接收一个字节的数据，多字节数据会丢失
	}
	return 0;
}

void UARTInterrupt() interrupt 4
{
    if(RI)
    {
        RI = 0;//数据接收完成后软件清零
        //add your code here!
		getDate=SBUF;//读取数据
		RxTx_Flag=1; //接收标志位
    }
}