/***********************************************
   > File Name: 独立按键实验
   > Author: pengshp
   > Mail: pengshp3@outlook.com
   > Date: 2015年 7 月 16 日
*************************************************/
//--包含你要使用的头文件--//
#include <reg51.h>	   //此文件中定义了51的一些特殊功能寄存器
#include <intrins.h>

//--定义要使用的IO口--//
#define  GPIO_KEY P1           //独立键盘用P1口
#define  GPIO_LED P0           //led使用P0口

//--声明全局函数--//
void Delay10ms(unsigned int c); //延时10ms
unsigned char Key_Scan();

void main(void)
{
	unsigned char ledValue, keyNum;

	ledValue = 0x01;

	while (1)
	{	
		keyNum = Key_Scan();  //扫描键盘

		switch (keyNum)
		{
			case(0xFE) :	  //返回按键K1的数据
				ledValue = 0x01;
				break;
			case(0xFD) :	  //返回按键K2的数据
				ledValue = 0x02;
				break;
			case(0xFB) :	  //返回按键K3的数据
				ledValue = 0x04;
				break;
			case(0xF7) :	  //返回按键K4的数据
				ledValue = 0x08;
				break;
			case(0xEF) :	  //返回按键K5的数据
				ledValue = 0x10;
				break;
			case(0xDF) :	  //返回按键K6的数据
				ledValue = 0x20;
				break;
			case(0xBF) :	  //返回按键K7的数据
				ledValue = 0x40;
				break;
			case(0x7F) :	  //返回按键K8的数据
				ledValue = 0x80;
				break;
			default:
				break;
		}

		GPIO_LED = ledValue;  //点亮LED灯
	}				
}

/*******************************************************************************
* 函 数 名         : Key_Scan()
* 函数功能		   : 扫描键盘
* 输    入         : 无
* 输    出         : 读取到的键值
*******************************************************************************/

unsigned char Key_Scan()
{
	unsigned char keyValue = 0 , i; //保存键值

	//--检测按键1--//
	if (GPIO_KEY != 0xFF)		//检测按键K1是否按下
	{
		Delay10ms(1);	        //消除抖动

		if (GPIO_KEY != 0xFF)	//再次检测按键是否按下
		{
			keyValue = GPIO_KEY;
			i = 0;
			while ((i<50) && (GPIO_KEY != 0xFF))	 //检测按键是否松开
			{
				Delay10ms(1);
				i++;
			}
		}
	}

	return keyValue;   //将读取到键值的值返回
}

/*******************************************************************************
* 函 数 名         : Delay10ms
* 函数功能		   : 延时函数，延时10ms
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void Delay10ms(unsigned int c)   //误差 0us
{
    unsigned char a, b;

	//--c已经在传递过来的时候已经赋值了，所以在for语句第一句就不用赋值了--//
    for (;c>0;c--)
	{
		for (b=38;b>0;b--)
		{
			for (a=130;a>0;a--);
		}
           
	}       
}