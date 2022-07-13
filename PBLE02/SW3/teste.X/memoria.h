#ifndef _MEMORIA_H
#define _MEMORIA_H

void i2cInit(void); 
void startC(void);
void stopC(void);
void clkPulse(void);
void checkAkB(void);
void writeByte(unsigned char dados);
unsigned char readByte(void);
void MEMwrite(unsigned char addr1, unsigned char addr2, unsigned char dados);
unsigned char MEMread(unsigned char addr1, unsigned char addr2);

#endif	// _MEMORIA_H