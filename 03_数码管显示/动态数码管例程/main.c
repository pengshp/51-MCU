/**************************************
  >File Name: 动态数码管显示
  > Author: pengshp
  > Mail: pengshp3@outlook.com
  > Date: 2015年 7 月 17 日
***************************************/

#include<reg51.h>
#define GPIO_DIG   P0	//段选
#define GPIO_PLACE P1	//位选
#define uchar unsigned char
#define uint unsigned char
	
uchar code DIG_PLACE[8] = {0xfe,0xfd,0xfb,0xf7,
                           0xef,0xdf,0xbf,0x7f};//位选控制   查表的方法控制
uint code DIG_CODE[17] = {0x3f,0x06,0x5b,0x4f, //0、1、2、3
	                      0x66,0x6d,0x7d,0x07, //4、5、6、7
                          0x7f,0x6f,0x77,0x7c, //8、9、A、B
                          0x39,0x5e,0x79,0x71};//C、D、E、F
uchar DisplayDate[8]=0; //存放要显示的8位数字
void DigDisplay();
void main()
{
	uchar i;
	for(i=0;i<8;i++)
	{
		DisplayDate[i]=DIG_CODE[i];
	}
	while(1)
	{
		DigDisplay();
	}
}

void DigDisplay()
{
	uchar i;
	uint j;
	for(i=0;i<8;i++)
	{
		GPIO_PLACE = DIG_PLACE[i];	 //发送位选,控制要亮的数码管
		GPIO_DIG = DisplayDate[i];   //发送段码，显示相应的数字
		j = 10;						 //扫描间隔时间设定
		while(j--);	
		GPIO_DIG = 0x00;             //消隐
	}
}