#include <picoUART.h>
#include <pu_print.h>

void setup() {}

void loop()
{
    uint8_t c;
    prints("\r\npicoUART echo ");
    c = purx();
    prints(" got: ");
    putx(c);
}

