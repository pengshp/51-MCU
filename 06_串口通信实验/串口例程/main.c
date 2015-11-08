/**************************************
  > File Name: 串口通信实验
  > Author: pengshp
  > Mail: pengshp3@outlook.com
  > Date: 2015年 7 月 21 日
***************************************/
#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int

uchar flag,i;
/*串口初始化函数*/
void init_uart()
{
	SCON=0x50;  //设置为工作方式1
	TMOD=0x20;  //设置计数器工作方式2
	PCON=0x80;  //波特率加倍
	TH1=0xF3;   //计数器初始值，波特率为4800
	TL1=0xF3;
	EA=1;       //打开总中断
	ES=1;       //打开接受中断
	TR1=1;      //打开计数器
}

void main()
{
	init_uart();
	while(1)
	{
		if(flag==1)
		{
			ES=0;      //关闭串口中断
			flag=0;
			SBUF=i;    //接受到的数据写入SBUF
			while(!TI);//判断是否发送完
			TI=0;
			ES=1;      //打开串口中断
		 }
	 }
}	

void serial() interrupt 4
{
	RI=0;              //接受标志位清零
	i=SBUF;            //从SBUF读数据
	flag=1;            //说明接受到数据
}