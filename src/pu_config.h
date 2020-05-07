// picoUART configuration

#ifndef PU_BAUD_RATE
#define PU_BAUD_RATE 115200L            // default baud rate
#endif

// port and bit for Tx and Rx - can be same
#define PU_TX B,0
#define PU_RX B,1

// disable interrupts during Tx and Rx
#define PU_DISABLE_IRQ 1

// I/O register macros
#define GBIT(r,b)       b
#define GPORT(r,b)      (PORT ## r)
#define GDDR(r,b)       (DDR ## r)
#define GPIN(r,b)       (PIN ## r)
#define get_bit(io)     GBIT(io)
#define get_port(io)    GPORT(io)
#define get_ddr(io)     GDDR(io)
#define get_pin(io)     GPIN(io)

#define PUTXBIT     get_bit(PU_TX)
#define PUTXPORT    get_port(PU_TX)
#define PUTXDDR     get_ddr(PU_TX)
#define PURXBIT     get_bit(PU_RX)
#define PURXPIN     get_pin(PU_RX)
