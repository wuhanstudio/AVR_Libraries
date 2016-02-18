/*
 * IIC.h
 *
 * Created: 2016/2/17 16:47:20
 *  Author: WuhanStudio
 */ 


#ifndef IIC_H_
#define IIC_H_

#include <avr/io.h>
#include <stdbool.h>

#define int8  signed char
#define uint8 unsigned char 

#define int16 int
#define uint16 unsigned int


 
/* TWSR values (not bits) */
/* Master */
#define I2C_START   0x08
#define I2C_RESTART   0x10

/* Master Transmitter */
#define I2C_MT_SLA_ACK  0x18
#define I2C_MT_SLA_NACK  0x20
#define I2C_MT_DATA_ACK  0x28
#define I2C_MT_DATA_NACK 0x30
#define I2C_MT_ARB_LOST  0x38

/* Master Receiver */
#define I2C_MR_ARB_LOST  0x38
#define I2C_MR_SLA_ACK  0x40
#define I2C_MR_SLA_NACK  0x48
#define I2C_MR_DATA_ACK  0x50
#define I2C_MR_DATA_NACK 0x58

/* Slave Transmitter */
#define I2C_ST_SLA_ACK   0xA8
#define I2C_ST_ARB_LOST_SLA_ACK 0xB0
#define I2C_ST_DATA_ACK   0xB8
#define I2C_ST_DATA_NACK  0xC0
#define I2C_ST_LAST_DATA  0xC8

/* Slave Receiver */
#define I2C_SR_SLA_ACK    0x60
#define I2C_SR_ARB_LOST_SLA_ACK  0x68
#define I2C_SR_GCALL_ACK   0x70
#define I2C_SR_ARB_LOST_GCALL_ACK 0x78
#define I2C_SR_DATA_ACK    0x80
#define I2C_SR_DATA_NACK   0x88
#define I2C_SR_GCALL_DATA_ACK  0x90
#define I2C_SR_GCALL_DATA_NACK  0x98
#define I2C_SR_STOP     0xA0

/* Misc */
#define I2C_NO_INFO   0xF8
#define I2C_BUS_ERROR  0x00

/*
 * The lower 3 bits of TWSR are reserved on the ATmega163.
 * The 2 LSB carry the prescaler bits on the newer ATmegas.
 */
#define I2C_STATUS_MASK (_BV(TWS7)|_BV(TWS6)|_BV(TWS5)|_BV(TWS4)|_BV(TWS3))
#define I2C_STATUS  (TWSR & I2C_STATUS_MASK)

/*
 * R/~W bit in SLA+R/W address field.
 */
#define I2C_READ  1
#define I2C_WRITE  0

#define I2CStart()     (TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN))
#define I2CStop()      (TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN))
#define I2CWaitAck() {while(!(TWCR&(1<<TWINT)));}
#define I2CChkAck()  (TWSR&0xf8)								//check ack
#define I2CSendAck() (TWCR|=(1<<TWEA))
#define I2CSendNoAck() (TWCR&=~(1<<TWEA))
#define I2CSendByte(x) {TWDR=(x);TWCR=(1<<TWINT)|(1<<TWEN);} 
#define I2CRcvNckByte() (TWCR=(1<<TWINT)|(1<<TWEN))
#define I2CRcvAckByte() (TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA))

/* For Program */
#define I2C_Stop()  I2CStop()
#define I2C_SendAck() I2CSendAck()
#define I2C_SendNoAck() I2CSendNoAck()
#define I2C_WaitAck() I2CWaitAck()

/* I2C Config */
#define I2C_ERR   0
#define I2C_CRR   1

#endif /* IIC_H_ */