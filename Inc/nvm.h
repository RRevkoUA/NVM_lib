//
// Created by Rustam on 2/7/23.
//

#ifndef ADDRLEDMB_NVM_H
#define ADDRLEDMB_NVM_H


//Include here you STM32
#include "stm32f103xe.h"

#define OPEN_FLASH          FLASH->KEYR = 0x45670123;\
                            FLASH->KEYR = 0xCDEF89AB;

typedef enum {
    NVM_OK = 0,
    NVM_ERASERR,    //Flash not erased to begin with
    NVM_WPROTERR    //Write protect error
}NVM_STAT;


NVM_STAT writeSector(uint32_t Address,void * values, uint16_t size);
void eraseSector(uint32_t SectorStartAddress);

void readSector(uint32_t SectorStartAddress, void * values, uint16_t size);


#endif //ADDRLEDMB_NVM_H
