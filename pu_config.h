// picoUART configuration

#ifndef PU_BAUD_RATE
#define PU_BAUD_RATE 115200L            // default baud rate
#endif

// port and bit for Tx and Rx - can be same
#define PU_TX B,0
#define PU_RX B,1

// disable interrupts during Tx and Rx
//#define PU_DISABLE_IRQ 1

