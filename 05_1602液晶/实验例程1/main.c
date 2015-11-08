/**************************************
  > File Name: LCD1602实验
  > Author: pengshp
  > Mail: pengshp3@outlook.com
  > Date: 2015年 7 月 21 日
***************************************/
#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int

uchar ENCHAR_PuZh[16]=" Pechin Science ";
void main()
{
	uchar i;
	LCD1602_Init();
	while(1)
	{
		LCD1602_WriteCom(0x80);
		for(i=0;i<16;i++)
		{
			LCD1602_WriteData(ENCHAR_PuZh[i]);
		}	
	}
}

/*lcd.h文件*/
#ifndef __LCD_H_
#define __LCD_H_
/**********************************
当使用的是4位数据传输的时候定义
**********************************/
#define LCD1602_4PINS

#include<reg51.h>
#define uint unsigned int 
#define uchar unsigned char
/**********************************
PIN口定义
**********************************/
#define LCD1602_DATAPINS P0
sbit LCD1602_E=P2^7;
sbit LCD1602_RW=P2^5;
sbit LCD1602_RS=P2^6;

void Delay1us(uint a);            //在51单片机12MHZ时钟下的延时函数
void LCD1602_WriteCom(uchar com); //LCD1602写入8位命令子函数	
void LCD1602_WriteData(uchar dat);//LCD1602写入8位数据子函数		
void LCD1602_Init();              //LCD1602初始化子程序					  
#endif

/*LCD.C文件*/
//#include"lcd.h"

/*******************************************************************************
* 函数名         : Delay1us
* 函数功能		 : 延时函数，延时1us
* 输入           : a
* 输出         	 : 无
*******************************************************************************/

void Delay1us(uint a)
{
	uint b,c;
	for(c=a;c>0;c--)
		for(b=110;b>0;b--);
}
/*******************************************************************************
* 函数名         : LCD1602_WriteCom
* 函数功能		 : 向LCD写入一个字节的命令
* 输入           : com
* 输出         	 : 无
*******************************************************************************/
#ifndef 	LCD1602_4PINS	     //当没有定义这个LCD1602_4PINS时
void LCD1602_WriteCom(uchar com) //写入命令
{
	LCD1602_E=0;
	LCD1602_RS=0;
	LCD1602_RW=0;
	LCD1602_DATAPINS=com;
	Delay1us(10);
	LCD1602_E=1;
	Delay1us(10);
	LCD1602_E=0;
}
#else 
void LCD1602_WriteCom(uchar com) //写入命令
{
	LCD1602_E=0;
	LCD1602_RS=0;
	LCD1602_RW=0;
	LCD1602_DATAPINS=com;	//由于4位的接线是接到P0口的高四位，所以传送高四位不用改
	Delay1us(10);
	LCD1602_E=1;
	Delay1us(10);
	LCD1602_E=0;
	Delay1us(10);
	LCD1602_DATAPINS=com<<4;
	Delay1us(10);
	LCD1602_E=1;
	Delay1us(10);
	LCD1602_E=0;
}
#endif
/*******************************************************************************
* 函数名         : LCD1602_WriteData
* 函数功能		 : 向LCD写入一个字节的数据
* 输入           : dat
* 输出         	 : 无
*******************************************************************************/		   
#ifndef 	LCD1602_4PINS		   
void LCD1602_WriteData(uchar dat) //写入数据
{
	LCD1602_E=0;
	LCD1602_RS=1;
	LCD1602_RW=0;
	LCD1602_DATAPINS=dat;
	Delay1us(10);
	LCD1602_E=1;
	Delay1us(10);
	LCD1602_E=0;
}
#else
void LCD1602_WriteData(uchar dat) //写入数据
{
	LCD1602_E=0;
	LCD1602_RS=1;
	LCD1602_RW=0;
	LCD1602_DATAPINS=dat;	//由于4位的接线是接到P0口的高四位，所以传送高四位不用改
	Delay1us(10);
	LCD1602_E=1;
	Delay1us(10);
	LCD1602_E=0;
	LCD1602_DATAPINS=dat<<4;
	Delay1us(10);
	LCD1602_E=1;
	Delay1us(10);
	LCD1602_E=0;
}
#endif
/*******************************************************************************
* 函数名         : LCD1602_Init()
* 函数功能		 : 初始化LCD屏
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/		   
#ifndef		LCD1602_4PINS
void LCD1602_Init()			 //LCD初始化子程序
{
 	LCD1602_WriteCom(0x38);  //开显示
	LCD1602_WriteCom(0x0c);  //开显示不显示光标
	LCD1602_WriteCom(0x06);  //写一个指针加1
	LCD1602_WriteCom(0x01);  //清屏
	LCD1602_WriteCom(0x80);  //设置数据指针起点
}
#else
void LCD1602_Init()			 //LCD初始化子程序
{
	LCD1602_WriteCom(0x32);	 //将8位总线转为4位总线
	LCD1602_WriteCom(0x28);	 //在四位线下的初始化
	LCD1602_WriteCom(0x0c);  //开显示不显示光标
	LCD1602_WriteCom(0x06);  //写一个指针加1
	LCD1602_WriteCom(0x01);  //清屏
	LCD1602_WriteCom(0x80);  //设置数据指针起点
}
#endif

