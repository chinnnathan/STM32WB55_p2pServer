#include <stdlib.h>
#include <stdint.h>

namespace {
    uint8_t Debug_ITMDebug = 0;
};

//****************************************************************************
constexpr uint32_t DWT_CYCCNT_ADDR   = 0xE0001004;
constexpr uint32_t DWT_CONTROL_ADDR  = 0xE0001000;
constexpr uint32_t DWT_LAR_ADDR      = 0xE0001FB0;
constexpr uint32_t SCB_DHCSR_ADDR    = 0xE000EDF0;
constexpr uint32_t SCB_DEMCR_ADDR    = 0xE000EDFC;
constexpr uint32_t ITM_TER_ADDR      = 0xE0000E00;
constexpr uint32_t ITM_TCR_ADDR      = 0xE0000E80;

// volatile uint32_t *DWT_CYCCNT   = (volatile uint32_t *)0xE0001004;
// volatile uint32_t *DWT_CONTROL  = (volatile uint32_t *)0xE0001000;
// volatile uint32_t *DWT_LAR      = (volatile uint32_t *)0xE0001FB0;
// volatile uint32_t *SCB_DHCSR    = (volatile uint32_t *)0xE000EDF0;
// volatile uint32_t *SCB_DEMCR    = (volatile uint32_t *)0xE000EDFC;
// volatile uint32_t *ITM_TER      = (volatile uint32_t *)0xE0000E00;
// volatile uint32_t *ITM_TCR      = (volatile uint32_t *)0xE0000E80;

//****************************************************************************

struct ccounter
{
    uint32_t startTimer = 0;

    volatile uint32_t *DWT_CYCCNT   = (volatile uint32_t *)DWT_CYCCNT_ADDR;
    volatile uint32_t *DWT_CONTROL  = (volatile uint32_t *)DWT_CONTROL_ADDR;
    volatile uint32_t *DWT_LAR      = (volatile uint32_t *)DWT_LAR_ADDR;
    volatile uint32_t *SCB_DHCSR    = (volatile uint32_t *)SCB_DHCSR_ADDR;
    volatile uint32_t *SCB_DEMCR    = (volatile uint32_t *)SCB_DEMCR_ADDR;
    volatile uint32_t *ITM_TER      = (volatile uint32_t *)ITM_TER_ADDR;
    volatile uint32_t *ITM_TCR      = (volatile uint32_t *)ITM_TCR_ADDR;

    void EnableTiming()
    {
        if ((*SCB_DHCSR & 1) && (*ITM_TER & 1)) // Enabled?
            Debug_ITMDebug = 1;
        
        *SCB_DEMCR |= 0x01000000;
        *DWT_LAR = 0xC5ACCE55; // enable access
        *DWT_CYCCNT = 0; // reset the counter
        *DWT_CONTROL |= 1 ; // enable the counter
    }

    void Start()
    {
        startTimer = *DWT_CYCCNT; 
    }

    uint32_t End()
    {
        return *DWT_CYCCNT - startTimer;
    }
};
