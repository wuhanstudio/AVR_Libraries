/*
 * IIC.c
 *
 * Created: 2016/2/17 16:47:09
 *  Author: WuhanStudio
 */ 

#include "IIC.h"

/*--------------------------------------------------------------------
程序名称：I2C Start
程序功能：
注意事项：
提示说明：
输    入：
返    回：
--------------------------------------------------------------------*/
bool I2C_Start()     
{
 I2CStart();      
 I2CWaitAck();
 if( I2CChkAck()!=I2C_START ) 
  return I2C_ERR;
 return I2C_CRR;
}

/*--------------------------------------------------------------------
程序名称：I2C ReStart
程序功能：
注意事项：
提示说明：
输    入：
返    回：
--------------------------------------------------------------------*/
bool I2C_Restart()     
{
 I2CStart();      
 I2CWaitAck();
 if( I2CChkAck()!=I2C_RESTART ) 
  return I2C_ERR;
 return I2C_CRR;
}

/*--------------------------------------------------------------------
程序名称：I2C(TWI)发送 7位 器件写地址: XXXX XXX0
程序功能：
注意事项：
提示说明：
输    入：
返    回：
--------------------------------------------------------------------*/
bool I2C_SendWrDAdr(uint8 wrDAdr) 
{
 I2CSendByte(wrDAdr);   //设置 器件写地址
 I2CWaitAck();
 if( I2CChkAck()!=I2C_MT_SLA_ACK )  
  return I2C_ERR;
 return I2C_CRR;  
}

/*--------------------------------------------------------------------
程序名称：I2C(TWI)发送 10位 器件写地址: 1111 0XX0, XXXX XXXX
程序功能：
注意事项：
提示说明：兼容 发送 7位 器件写地址: XXXX XXX0
输    入：
返    回：
--------------------------------------------------------------------*/
bool I2C_SendWrDAdr_(uint16 wrDAdr) 
{
 if( (wrDAdr&0xF000) == 0xF000 )						//判断是否为 10位 器件地址
  if( I2C_SendWrDAdr( (uint8)wrDAdr>>8 )==I2C_ERR )		//设置 （高位）器件写地址
   return I2C_ERR;
 if( I2C_SendWrDAdr( (uint8)wrDAdr )==I2C_ERR )			//设置 （低位）器件写地址
  return I2C_ERR;
 return I2C_CRR;
}

/*--------------------------------------------------------------------
程序名称：I2C(TWI)发送 7位 器件读地址: XXXX XXX1
程序功能：
注意事项：
提示说明：
输    入：
返    回：
--------------------------------------------------------------------*/
bool I2C_SendRdDAdr(uint8 rdDAdr) 
{
 I2CSendByte(rdDAdr);   //设置 器件读地址
 I2CWaitAck();
 if( I2CChkAck()!=I2C_MR_SLA_ACK )  
  return I2C_ERR;
 return I2C_CRR; 
}

/*--------------------------------------------------------------------
程序名称：I2C(TWI)发送 10位 器件读地址: 1111 0XX0, XXXX XXXX
程序功能：
注意事项：
提示说明：
输    入：
返    回：
--------------------------------------------------------------------*/
bool I2C_SendRdDAdr_(uint8 rdDAdr) 
{
 if( (rdDAdr&0xF000) == 0xF000 )						//判断是否为 10位 器件地址
  if( I2C_SendWrDAdr( (uint8)rdDAdr>>8 )==I2C_ERR )		//设置 （高位）器件读地址
   return I2C_ERR;
 if( I2C_SendWrDAdr( (uint8)rdDAdr )==I2C_ERR )			//设置 （低位）器件读地址
  return I2C_ERR;
 return I2C_CRR;
}

/*--------------------------------------------------------------------
程序名称：I2C(TWI)发送数据
程序功能：
注意事项：
提示说明：
输    入：
返    回：
--------------------------------------------------------------------*/
bool I2C_SendDat(uint8 configDat) 
{
 I2CSendByte(configDat);   
 I2CWaitAck();
 if( I2CChkAck()!=I2C_MT_DATA_ACK ) 
  return I2C_ERR;
 return I2C_CRR; 
}

/*--------------------------------------------------------------------
程序名称：I2C(TWI)接收数据且不产生应答
程序功能：
注意事项：
提示说明：
输    入：
返    回：
--------------------------------------------------------------------*/
bool I2C_RcvNAckDat(uint8 *pRdDat) 
{
 I2CRcvNckByte();
 I2CWaitAck();
 if( I2CChkAck()!=I2C_MR_DATA_NACK )
  return I2C_ERR;
 *pRdDat=TWDR;
 return I2C_CRR;
}

/*--------------------------------------------------------------------
程序名称：I2C(TWI)接收数据且产生应答
程序功能：
注意事项：
提示说明：
输    入：
返    回：
--------------------------------------------------------------------*/
bool I2C_RcvAckDat(uint8 *pRdDat) 
{
 I2CRcvAckByte();     
 I2CWaitAck();
 if( I2CChkAck()!=I2C_MR_DATA_ACK )
  return I2C_ERR;
 *pRdDat=TWDR;
 return I2C_CRR;
}

/*--------------------------------------------------------------------
程序名称：I2C(TWI)写器件，写一个数据
程序功能：
注意事项：
提示说明：
输    入：wrDAdr: write device-address 写器件地址
   wordAdr: word address 字地址
   dat: data 数据
返    回：
--------------------------------------------------------------------*/
bool I2C_Write(uint16 wrDAdr,uint8 wordAdr,uint8 dat)
{
 if( I2C_Start()==I2C_ERR )
  return I2C_ERR;

 if( I2C_SendWrDAdr_(wrDAdr)==I2C_ERR )
  return I2C_ERR;

 if( I2C_SendDat(wordAdr)==I2C_ERR )
  return I2C_ERR;

 if( I2C_SendDat(dat)==I2C_ERR )
  return I2C_ERR;

 I2C_Stop();

 return I2C_CRR;
}

/*--------------------------------------------------------------------
程序名称：I2C(TWI)写器件，写N个数据
程序功能：
注意事项：
提示说明：
输    入：wrDAdr: write device-address 写器件地址
   wordAdr: word address 字地址
   *pWrDat: p->write data 写入数据指针
   num: number 写入数据个数
返    回：
--------------------------------------------------------------------*/
//bool I2C_Write_(uint16 wrDAdr,uint8 wordAdr,
//      uint8 *pWrDat,uint8 num)
//{
//
//} 

/*--------------------------------------------------------------------
程序名称：I2C(TWI)读器件，读一个数据
程序功能：
注意事项：
提示说明：
输    入：wrDAdr: write device-address 写器件地址
   wordAdr: word address 字地址
   rdDAdr: read device-address 读器件地址
   *pRdDat: p->read data 读取数据指针
返    回：
--------------------------------------------------------------------*/
bool I2C_Read(uint16 wrDAdr,uint8 wordAdr,
     uint8 rdDAdr,uint8 *pRdDat)
{
 if( I2C_Start()==I2C_ERR )
  return I2C_ERR;

 if( I2C_SendWrDAdr_(wrDAdr)==I2C_ERR )
  return I2C_ERR;

 if( I2C_SendDat(wordAdr)==I2C_ERR )
  return I2C_ERR;

 if( I2C_Restart()==I2C_ERR )
  return I2C_ERR;

 if( I2C_SendRdDAdr(rdDAdr)==I2C_ERR )
  return I2C_ERR;

 if( I2C_RcvNAckDat(pRdDat)==I2C_ERR )
  return I2C_ERR;

 I2C_Stop();

 return I2C_CRR;
}

/*--------------------------------------------------------------------
程序名称：I2C(TWI)读器件，读N个数据
程序功能：
注意事项：
提示说明：
输    入：wrDAdr: write device-address 写器件地址
   wordAdr: word address 字地址
   rdDAdr: read device-address 读器件地址
   *pRdDat: p->read data 读取数据指针
   num: number 读取数据个数
返    回：
--------------------------------------------------------------------*/
bool I2C_Read_(uint16 wrDAdr,uint8 wordAdr,
      uint8 rdDAdr,uint8 *pRdDat,uint8 num)
{
  uint8 i;
 
 if( I2C_Start()==I2C_ERR )
  return I2C_ERR;

 if( I2C_SendWrDAdr_(wrDAdr)==I2C_ERR )
  return I2C_ERR;

 if( I2C_SendDat(wordAdr)==I2C_ERR )
  return I2C_ERR;

 if( I2C_Restart()==I2C_ERR )
  return I2C_ERR;

 if( I2C_SendRdDAdr(rdDAdr)==I2C_ERR )
  return I2C_ERR;

 for(i=0;i<num-1;i++)
  if( I2C_RcvAckDat(pRdDat+i)==I2C_ERR )
   return I2C_ERR;
 
 if( I2C_RcvNAckDat(pRdDat+i)==I2C_ERR )
   return I2C_ERR;

 I2C_Stop();
 
 return I2C_CRR;
}