/*
**  Processor: S32K144
**  Author: Saurabh Kumar
**  GCC Version: 12.3
**  
**  Startup file for the GCC Compiler
**  Execution starts from here after the reset.
**  Startup Code Initialize the RAM and required peripherals
**  And then Jumps to the main() function
*/
#include "main.h"
#include "interrupt.h"
#include "startup.h"

uint32_t flashConfig[] __attribute__ ((section (".flashConfig"))) = {
 (uint32_t) 0xFFFFFFFF,
 (uint32_t) 0xFFFFFFFF,
 (uint32_t) 0xFFFFFFFF,
 (uint32_t) 0xFFFF7FFE
};

void Reset_Handler(){
    initDataNbss();
    main();

    /* Never returns back to here and putting a trap for that */
    while(1);
}

void initDataNbss() {

    /* Variable for copy data section */

    uint32_t* endTextAdd   = (uint32_t*) &_etext;
    uint32_t* startDataAdd = (uint32_t*) &_sdata_ram;
    uint32_t* endDataAdd   = (uint32_t*) &_edata_ram;

    /* Variable for copy bss section */

    uint32_t* startBss  = (uint32_t*) &_bss_start_;
    uint32_t* endBss    = (uint32_t*) &_bss_end_;

    /*copy data section */

    while(startDataAdd != endDataAdd)
    {
       *(startDataAdd++) = *(endTextAdd++);
    }

    /*copy bss section */

    while(startBss != endBss)
    {
        *(startBss++) = 0;
    }
}
