/**************************************
  > File Name: LCD1602实验
  > Author: pengshp
  > Mail: pengshp3@outlook.com
  > Date: 2015年 7 月 21 日
***************************************/
#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int

sbit RD_RS=P2^6;
sbit LCDE_E=P2^7;
sbit WR_RW=P2^5;

uchar code table1[]="STC-51 MCU";
uchar code table2[]=" pengshp ";

uchar i,j;
uchar num;
void Delay(uint x)
{
	for(i=x;i>0;i--)
	{
		for(j=120;j>0;j--)
		{
		}
	}
}

/*写命令函数*/
void write_com(uchar com)
{
	RD_RS=0;
	WR_RW=0;
	LCDE_E=0;
	P0=com;
	LCDE_E=1;
	Delay(5);
	LCDE_E=0;
}

/*写数据函数*/
void write_data(uchar dat)
{
	RD_RS=1;
	WR_RW=0;
	LCDE_E=0;
	P0=dat;
	LCDE_E=1;
	Delay(5);
	LCDE_E=0;
}

/*初始化函数*/
void intt()
{
	write_com(0x38);//显示模式
	write_com(0x08);//显示关闭
	write_com(0x01);//显示清屏
	write_com(0x06);//显示光标移动
	write_com(0x0F);//显示开及光标设置
}
	
void main()
{
	intt();
	for(num=0;num<10;num++)
    {
		write_data(table1[num]);
		Delay(300);
    }
	write_com(0x80+0x40);
	for(num=0;num<9;num++)
    {
		write_data(table2[num]);
		Delay(10);
    }
	while(1);
}