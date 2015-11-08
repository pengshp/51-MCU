/**************************************
  > File Name: 定时器实验
  > Author: pengshp
  > Mail: pengshp3@outlook.com
  > Date: 2015年 7 月 19 日
***************************************/
#include<reg51.h>
#include<intrins.h>
#define GPIO_LED P2
unsigned char Time;

void main()
{
	Time=0;
	GPIO_LED=0x01;   //最左边一个灯亮
	TMOD = 0x01;     //选择工作模式1
	TH0 = 0x3C;	     //设置初始值,定时50ms
	TL0 = 0xB0; 
	TR0 = 1;		 //启动定时器0
	while(1)
	{
		if(TF0==1)                          //判断T0是否溢出
		{
			TF0=0;                          //T0溢出后，清零中断标志
			TH0 = 0x3C;
            TL0 = 0xB0; 
			Time++;                         //计数值自加1
			if(Time==20)                    //20*50ms=1s
			{
				GPIO_LED=_crol_(GPIO_LED,1);//左移一位
				Time=0;                     //重新置0
			}
		 }
	 }
 }