#include <picoUART.h>
#include <pu_print.h>

void setup() {}

void loop()
{
    uint8_t c;
    prints_P(PSTR("\r\npicoUART echo "));
    c = purx();
    prints_P(PSTR(" got: "));
    putx(c);
}

