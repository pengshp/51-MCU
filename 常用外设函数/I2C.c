#include <reg52.h>
#include <intrins.h>

#define I2CDelay()  {_nop_();_nop_();_nop_();_nop_();}
sbit I2C_SCL = P3^7;
sbit I2C_SDA = P3^6;

/* 产生总线起始信号 */
void I2CStart()
{
    I2C_SDA = 1; //首先确保SDA、SCL都是高电平
    I2C_SCL = 1;
    I2CDelay();
    I2C_SDA = 0; //先拉低SDA
    I2CDelay();
    I2C_SCL = 0; //再拉低SCL
}
/* 产生总线停止信号 */
void I2CStop()
{
    I2C_SCL = 0; //首先确保SDA、SCL都是低电平
    I2C_SDA = 0;
    I2CDelay();
    I2C_SCL = 1; //先拉高SCL
    I2CDelay();
    I2C_SDA = 1; //再拉高SDA
    I2CDelay();
}
/* I2C总线写操作，dat-待写入字节，返回值-从机应答位的值 */
bit I2CWrite(unsigned char dat)
{
    bit ack;  //用于暂存应答位的值
    unsigned char mask;  //用于探测字节内某一位值的掩码变量

    for (mask=0x80; mask!=0; mask>>=1) //从高位到低位依次进行
    {
        if ((mask&dat) == 0)  //该位的值输出到SDA上
            I2C_SDA = 0;
        else
            I2C_SDA = 1;
        I2CDelay();
        I2C_SCL = 1;          //拉高SCL
        I2CDelay();
        I2C_SCL = 0;          //再拉低SCL，完成一个位周期
    }
    I2C_SDA = 1;   //8位数据发送完后，主机释放SDA，以检测从机应答
    I2CDelay();
    I2C_SCL = 1;   //拉高SCL
    ack = I2C_SDA; //读取此时的SDA值，即为从机的应答值
    I2CDelay();
    I2C_SCL = 0;   //再拉低SCL完成应答位，并保持住总线

    return (~ack); //应答值取反以符合通常的逻辑：
                   //0=不存在或忙或写入失败，1=存在且空闲或写入成功
}
/* I2C总线读操作，并发送非应答信号，返回值-读到的字节 */
unsigned char I2CReadNAK()
{
    unsigned char mask;
    unsigned char dat;

    I2C_SDA = 1;  //首先确保主机释放SDA
    for (mask=0x80; mask!=0; mask>>=1) //从高位到低位依次进行
    {
        I2CDelay();
        I2C_SCL = 1;      //拉高SCL
        if(I2C_SDA == 0)  //读取SDA的值
            dat &= ~mask; //为0时，dat中对应位清零
        else
            dat |= mask;  //为1时，dat中对应位置1
        I2CDelay();
        I2C_SCL = 0;      //再拉低SCL，以使从机发送出下一位
    }
    I2C_SDA = 1;   //8位数据发送完后，拉高SDA，发送非应答信号
    I2CDelay();
    I2C_SCL = 1;   //拉高SCL
    I2CDelay();
    I2C_SCL = 0;   //再拉低SCL完成非应答位，并保持住总线

    return dat;
}
/* I2C总线读操作，并发送应答信号，返回值-读到的字节 */
unsigned char I2CReadACK()
{
    unsigned char mask;
    unsigned char dat;

    I2C_SDA = 1;  //首先确保主机释放SDA
    for (mask=0x80; mask!=0; mask>>=1) //从高位到低位依次进行
    {
        I2CDelay();
        I2C_SCL = 1;      //拉高SCL
        if(I2C_SDA == 0)  //读取SDA的值
            dat &= ~mask; //为0时，dat中对应位清零
        else
            dat |= mask;  //为1时，dat中对应位置1
        I2CDelay();
        I2C_SCL = 0;      //再拉低SCL，以使从机发送出下一位
    }
    I2C_SDA = 0;   //8位数据发送完后，拉低SDA，发送应答信号
    I2CDelay();
    I2C_SCL = 1;   //拉高SCL
    I2CDelay();
    I2C_SCL = 0;   //再拉低SCL完成应答位，并保持住总线

    return dat;
}
