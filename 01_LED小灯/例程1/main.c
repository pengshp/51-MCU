/**************************************
  > File Name: 左右流水灯
  > Author: pengshp
  > Mail: pengshp3@outlook.com
  > Date: 2015年 7 月 13 日
***************************************/
#include<reg51.h>

void delay500ms(void)          //误差 0us
{
    unsigned char a,b,c;
    for(c=23;c>0;c--)
        for(b=152;b>0;b--)
            for(a=70;a>0;a--);
}

void main()
{
	unsigned char cnt=0;
	P2=0x00;
	while(1)
	{	
		for(;cnt<8;cnt++)
		{
			P2=(0x01<<cnt);//0000 0001左移
			delay500ms();
		}
		cnt=0;
		for(;cnt<8;cnt++)
		{
			P2=(0x80>>cnt);//1000 0000右移
			delay500ms();
		}
		cnt=0;	
	}	
}