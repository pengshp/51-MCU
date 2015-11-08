/**************************************
  > File Name: 红外通信原理
  > Author: pengshp
  > Mail: pengshp3@outlook.com
  > Date: 2015年 7 月 27 日
***************************************/
#include<reg51.h>
#define GPIO_DIG P0

sbit LSA  = P2^2;
sbit LSB  = P2^3;
sbit LSC  = P2^4;
sbit IRIN = P3^2;                           //红外接收器位声明

unsigned char code DIG_CODE[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
						         0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
unsigned char DisplayData[8];               //用来存放要显示的8位数的值
unsigned char IrValue[6];	                //用来存放读取到的红外值
unsigned char Time;

void DigDisplay();                          //动态显示函数
void IrInit();
void DelayMs(unsigned int);

void main()
{
	IrInit();
	while(1)
	{
		IrValue[4]=IrValue[2]>>4;	 	 	//高位
		IrValue[5]=IrValue[2]&0x0f;		    //低位
		DisplayData[0] = 0x00;
		DisplayData[1] = DIG_CODE[IrValue[4]];
		DisplayData[2] = DIG_CODE[IrValue[5]];
		DisplayData[3] = 0x76;	  
		DisplayData[4] = 0x00;
		DisplayData[5] = DIG_CODE[IrValue[4]];
		DisplayData[6] = DIG_CODE[IrValue[5]];
		DisplayData[7] = 0x76;
		DigDisplay();	
	}
}

void DelayMs(unsigned int x)                 //0.14ms误差 0us
{
	unsigned char i;
	while(x--)
	{
		for (i = 0; i<13; i++);
	}
}

void IrInit()
{
	IT0=1;                                   //下降沿触发
	EX0=1;                                   //打开中断0允许
	EA=1;	                                 //打开总中断
	IRIN=1;                                  //初始化端口
}

void ReadIr() interrupt 0
{
	unsigned char j,k;
	unsigned int err;
	Time=0;					 
	DelayMs(70);
	if(IRIN==0)		                         //确认是否真的接收到正确的信号
	{	 
		err=1000;				             //1000*10us=10ms,超过说明接收到错误的信号
		while((IRIN==0)&&(err>0))	         //等待前面9ms的低电平过去  		
		{			
			DelayMs(1);
			err--;
		} 
		if(IRIN==1)			                 //如果正确等到9ms低电平
		{
			err=500;
			while((IRIN==1)&&(err>0))		 //等待4.5ms的起始高电平过去
			{
				DelayMs(1);
				err--;
			}
			for(k=0;k<4;k++)		         //共有4组数据
			{				
				for(j=0;j<8;j++)	         //接收一组数据
				{
					err=60;		
					while((IRIN==0)&&(err>0))//等待信号前面的560us低电平过去
					{
						DelayMs(1);
						err--;
					}
					err=500;
					while((IRIN==1)&&(err>0))//计算高电平的时间长度。
					{
						DelayMs(1);          //0.14ms
						Time++;
						err--;
						if(Time>30)
						{
							EX0=1;
							return;
						}
					}
					IrValue[k]>>=1;	         //k表示第几组数据
					if(Time>=8)			     //如果高电平出现大于565us，那么是1
					{
						IrValue[k]|=0x80;
					}
					Time=0;		             //用完时间要重新赋值							
				}
			}
		}
		if(IrValue[2]!=~IrValue[3])          //反码取反后与原码相同则说明信号接受正确
		{
			return;
		}
	}			
}

void DigDisplay()
{
	unsigned char i;
	unsigned int j;
	for(i=0;i<8;i++)
	{
		switch(i)	                        //位选，选择点亮的数码管
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;   //显示第0位
			case(1):
				LSA=1;LSB=0;LSC=0; break;   //显示第1位
			case(2):
				LSA=0;LSB=1;LSC=0; break;   //显示第2位
			case(3):
				LSA=1;LSB=1;LSC=0; break;   //显示第3位
			case(4):
				LSA=0;LSB=0;LSC=1; break;   //显示第4位
			case(5):
				LSA=1;LSB=0;LSC=1; break;   //显示第5位
			case(6):
				LSA=0;LSB=1;LSC=1; break;   //显示第6位
			case(7):
				LSA=1;LSB=1;LSC=1; break;   //显示第7位	
		}
		GPIO_DIG=DisplayData[i];            //发送段码
		j=10;						        //扫描间隔时间设定
		while(j--);	
		GPIO_DIG=0x00;                      //消隐
	}
}