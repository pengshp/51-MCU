#include <reg52.h>

extern void I2CStart();
extern void I2CStop();
extern unsigned char I2CReadACK();
extern unsigned char I2CReadNAK();
extern bit I2CWrite(unsigned char dat);

/* E2读取函数，buf-数据接收指针，addr-E2中的起始地址，len-读取长度 */
void E2Read(unsigned char *buf, unsigned char addr, unsigned char len)
{
    do {                       //用寻址操作查询当前是否可进行读写操作
        I2CStart();
        if (I2CWrite(0x50<<1)) //应答则跳出循环，非应答则进行下一次查询
        {
            break;
        }
        I2CStop();
    } while(1);
    I2CWrite(addr);            //写入起始地址
    I2CStart();                //发送重复启动信号
    I2CWrite((0x50<<1)|0x01);  //寻址器件，后续为读操作
    while (len > 1)            //连续读取len-1个字节
    {
        *buf++ = I2CReadACK(); //最后字节之前为读取操作+应答
        len--;
    }
    *buf = I2CReadNAK();       //最后一个字节为读取操作+非应答
    I2CStop();
}
/* E2写入函数，buf-源数据指针，addr-E2中的起始地址，len-写入长度 */
void E2Write(unsigned char *buf, unsigned char addr, unsigned char len)
{
    while (len > 0)
    {
        //等待上次写入操作完成
        do {                       //用寻址操作查询当前是否可进行读写操作
            I2CStart();
            if (I2CWrite(0x50<<1)) //应答则跳出循环，非应答则进行下一次查询
            {
                break;
            }
            I2CStop();
        } while(1);
        //按页写模式连续写入字节
        I2CWrite(addr);           //写入起始地址
        while (len > 0)
        {
            I2CWrite(*buf++);     //写入一个字节数据
            len--;                //待写入长度计数递减
            addr++;               //E2地址递增
            if ((addr&0x07) == 0) //检查地址是否到达页边界，24C02每页8字节，
            {                     //所以检测低3位是否为零即可
                break;            //到达页边界时，跳出循环，结束本次写操作
            }
        }
        I2CStop();
    }
}
