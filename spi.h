#ifndef _VDIP1_SPI_H_
#define _VDIP1_SPI_H_

#define XFER_OK    0
#define XFER_RETRY 1

void  SPI_Init(void);

int   SPI_Read(uint8 *);
uint8 SPI_ReadWait(void);
void  SPI_Write(uint8);
void  SPI_WriteStr(const uint8*);
void  SPI_WriteStrN(const uint8 *, uint32);
int   SPI_Xfer(int, uint8*);

#endif
