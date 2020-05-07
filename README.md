# picoUART
small, fast, and precise bit-bang UART for 8-bit AVR MCUs

(c) Ralph Doncaster 2020 open source MIT license

picoUART is a pico-size simplex high-speed AVR bit-bang UART.
Code size is less than 80 bytes total for transmit and receive.
picoUART timing is accurate to the cycle (+- 0.5 cycle error);
this is less than 1% at 8Mhz.

Default Rx is on PB0, and Tx is on PB1.  If set to the same pin,
picoUART is also capable of 1-wire (shared Rx/Tx) operation.

picoUART 1.0.0 supports interrupt-driven receive using pin-change interrupts.  Currently 1-wire shared Rx/Tx is not supported with PCINT-based receive.  For the interrupt driven receive, use purx_dataready() and pu_read().

picoUART is a library that is compatible with the Arduino API but is not
 dependent on any Arduino functions so it can be used with avr-libc.  When used with the Arduino IDE, version 1.6.0 or later is required.

For an even smaller transmit-only asynchronous serial library, see <a href="https://github.com/nerdralph/debugSerial">debugSerial</a>.
