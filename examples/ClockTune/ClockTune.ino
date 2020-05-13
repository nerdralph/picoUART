// picoUART OSCCAL tuner for t13 and t85 series
// Ralph Doncaster 2020 open source MIT license
// repeatedly press 'x' until OSCCAL value stabilizes
// should only take 3 or 4 tries
// output value is timing delta in cycles followed by OSCCAL value

#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <picoUART.h>
#include <pu_print.h>

// add 0.5 for integer rounding
// #define CYCLES_PER_BIT (uint8_t)(PUBIT_CYCLES() + 0.5)
const uint8_t CYCLES_PER_BIT = (uint8_t)(PUBIT_CYCLES + 0.5);

// converts 4-bit nibble to ascii hex
uint8_t nibbletohex(uint8_t value)
{
    value &= 0x0F;
    if ( value > 9 ) value += 'A' - ':';
    return value + '0';
}

void printHex(uint8_t value)
{
    //putx(nibbletohex(value>>4));
    putx(nibbletohex(value/16));
    putx(nibbletohex(value));
}


ISR(PCINT0_vect)
{
  // start timer when pin transitions low
  if ((PINB & 1<<PURXBIT) == 0)
    TCCR0B = 1<<CS00;
  else {
    uint8_t current = TCNT0;    
    // end of interval, reset counter
    TCCR0B = 0;
    TCNT0 = 0;
#ifdef DEBUG
    printHex(current);
    putx(' ');
#endif
    // 'x' begins with 3 zeros + start bit = 4 * bit-time
    // match speed to soft uart bit time
    // use mod256 math to handle potential uint8_t overflow
    unsigned expected = (unsigned)(PUBIT_CYCLES * 4 + 0.5);
    char delta = (expected & 0xFF) - current;
    printHex(OSCCAL);
    if (delta > 3) {
      OSCCAL++;
      prints_P(PSTR(" slow"));
    }
    else if (delta < -3) {
      OSCCAL--;
      prints_P(PSTR(" fast"));
    }
    else prints_P(PSTR(" good"));
    putx('\n');
  }
  // clear interrupt flag in case another triggered
  GIFR = 1<<PCIF;
}

void setup()
{
  _delay_ms(100);                       // serial monitor open delay
  PORTB |= 1<<PURXBIT;                  // pullup RX line

  printHex(OSCCAL);
  prints_P(PSTR(" Hit x to test.\n"));
wait_x:
  // wait for tuning character to ensure not reading noise
  // before entering tuning mode
  uint8_t counter = 0;
  while (PINB & (1<<PURXBIT));
  do {
    counter++;
  }  while ((PINB & (1<<PURXBIT)) == 0);
  
  // low period should be 4 bit-times for 'x'
  // counter loop is 4 cycles, so counter =~ cycles/bit
  // 1/4 = 25% timing margin
  uint8_t margin = CYCLES_PER_BIT / 4;
  // use __builtin_abs() in case some fool made an abs() macro
  uint8_t delta = __builtin_abs( counter - CYCLES_PER_BIT);
#ifdef DEBUG
  printHex(delta);
#endif
  if (delta > margin) {
    prints_P(PSTR(" noise skipped\n"));
    goto wait_x;
  }

  _delay_ms(1);                         // skip remaining bits in frame
  prints_P(PSTR(" OSCCAL "));
  if (delta < 2) { 
    prints_P(PSTR("OK\n"));
    return;
  }
  prints_P(PSTR("imperfect\n"));
  // reset counter for first interrupt
  TCCR0B = 0;
  TCNT0 = 0;
  // setup interrupt on Rx pin
  PCMSK = 1<<PURXBIT;
  GIMSK = 1<<PCIE;
  sei();  
  MCUCR |= 1<<SE;                       // sleep enable
}

void loop()
{
  // sleep while waiting for interrupt
  asm("sleep");
}
