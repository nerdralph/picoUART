# picoUART
small, fast, and precise bit-bang half-duplex UART for 8-bit AVR MCUs

(c) Ralph Doncaster 2020 open source MIT license

picoUART is a pico-size simplex high-speed AVR bit-bang UART.
Code size is less than 80 bytes total for transmit and receive.
picoUART timing is accurate to the cycle (+- 0.5 cycle error);
this is less than 1% at 8Mhz.

picoUART is a library that is compatible with the Arduino API but is not
 dependent on any Arduino functions so it can be used with avr-libc.  When used with the Arduino IDE, version 1.6.0 or later is required.

Default Rx is on PB1, and Tx is on PB0.  If set to the same pin in pu_config.h, picoUART is also capable of 1-wire (shared Rx/Tx) operation.

picoUART 1.0.0 supports interrupt-driven receive using pin-change interrupts on the t13 and t85 series.  Currently 1-wire shared Rx/Tx is not supported with PCINT-based receive. Full-duplex communication is not possible, so received characters will be lost if they arrive during transmit.  For the interrupt driven receive, use purx_dataready() and pu_read().  Due to ISR overhead, the maximum reliable speed is 115.2kbps at 8Mhz.  There is a single-character receive buffer, so data is likely to be lost if it is not read and processed quickly.  A 16-byte receive FIFO is a possibility for a later version.

Examples include a clock tuner program to help determine the best OSCCAL value for error-free communication.

For an even smaller transmit-only asynchronous serial library, see <a href="https://github.com/nerdralph/debugSerial">debugSerial</a>.
