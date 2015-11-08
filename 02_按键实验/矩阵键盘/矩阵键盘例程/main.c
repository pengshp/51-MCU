/**************************************
  > File Name: 矩阵键盘实验
  > Author: pengshp
  > Mail: pengshp3@outlook.com
  > Date: 2015年 7 月 16 日
***************************************/
#include<reg51.h>
#define uchar unsigned char
#define GPIO_DIG P0
#define GPIO_KEY P1

uchar code DIG_CODE[17]={0x3f,0x06,0x5b,0x4f,
	                     0x66,0x6d,0x7d,0x07,
                         0x7f,0x6f,0x77,0x7c,
                         0x39,0x5e,0x79,0x71};
uchar KeyValue;
void Delay10ms();    //延时10ms
void KeyDown();		 //检测按键函数

void main(void)
{
	while(1)
	{
		KeyDown();
		GPIO_DIG=~DIG_CODE[KeyValue];
	}				
}

void KeyDown()
{
	char a=0;
	GPIO_KEY=0x0f;            //0000 1111 高四位全为0，低四位为1
	if(GPIO_KEY!=0x0f)        //读取按键是否按下
	{
		Delay10ms();          //延时10ms进行消抖
		if(GPIO_KEY!=0x0f)    //再次检测键盘是否按下
		{
			//测试列
			GPIO_KEY=0X0F;
			switch(GPIO_KEY)
			{
				case(0X07):	KeyValue=0;break;
				case(0X0b):	KeyValue=1;break;
				case(0X0d): KeyValue=2;break;
				case(0X0e):	KeyValue=3;break;
			}
			//测试行
			GPIO_KEY=0XF0;
			switch(GPIO_KEY)
			{
				case(0X70):	KeyValue=KeyValue;break;
				case(0Xb0):	KeyValue=KeyValue+4;break;
				case(0Xd0): KeyValue=KeyValue+8;break;
				case(0Xe0):	KeyValue=KeyValue+12;break;
			}
			while((a<50)&&(GPIO_KEY!=0xf0))	 //检测按键松手检测
			{
				Delay10ms();                 //延时处理
				a++;
			}
		}
	}
}

void Delay10ms()   //误差 0us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}