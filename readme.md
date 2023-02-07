#  `Non-Volatile Memory lib` 

## Installation 
Put library files to your project, and change in `nvm.h` at `10 line` to your stm32xxxx.h library

## Usage 

Before and after reading/writing/erasing you must disable and enable interrupts

For reading
```C
    disable_interrupts();
    readSector(FLASH_ADDRESS,&value,sizeof(value));
    enable_interrupts();
```

For writing 
```C
    disable_interrupts();
    eraseSector(FLASH_ADDRESS);
    writeSector(FLASH_ADDRESS,&value,sizeof(value));
    enable_interrupts();
```
