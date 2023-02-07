//
// Created by Rustam on 2/7/23.
//

#include "nvm.h"

NVM_STAT writeSector(uint32_t Address, void *values, uint16_t size){

    uint16_t *AddressPtr;
    uint16_t *valuePtr;
    AddressPtr = (uint16_t *)Address;
    valuePtr=(uint16_t *)values;
    size = size / 2;  // incoming value is expressed in bytes, not 16 bit words
    while(size) {
        // unlock the flash
        // Key 1 : 0x45670123
        // Key 2 : 0xCDEF89AB
        OPEN_FLASH;
        FLASH->CR &= ~(1<<1); // ensure PER is low
        FLASH->CR |= (1<<0);  // set the PG bit
        *(AddressPtr) = *(valuePtr);
        while(FLASH->SR & (1<<0)); // wait while busy
        if (FLASH->SR & (1<<2))
            return NVM_ERASERR; // flash not erased to begin with
        if (FLASH->SR & (1<<4))
            return NVM_WPROTERR; // write protect error
        AddressPtr++;
        valuePtr++;
        size--;
    }
    return NVM_OK;
}



void eraseSector(uint32_t SectorStartAddress)
{
    OPEN_FLASH;
    FLASH->CR &= ~(1<<0);  // Ensure PG bit is low
    FLASH->CR |= (1<<1); // set the PER bit
    FLASH->AR = SectorStartAddress;
    FLASH->CR |= (1<<6); // set the start bit
    while(FLASH->SR & (1<<0)); // wait while busy
}


void readSector(uint32_t SectorStartAddress, void * values, uint16_t size)
{
    uint16_t *AddressPtr;
    uint16_t *valuePtr;
    AddressPtr = (uint16_t *)SectorStartAddress;
    valuePtr=(uint16_t *)values;
    size = size/2; // incoming value is expressed in bytes, not 16 bit words
    while(size)
    {
        *((uint16_t *)valuePtr)=*((uint16_t *)AddressPtr);
        valuePtr++;
        AddressPtr++;
        size--;
    }
}