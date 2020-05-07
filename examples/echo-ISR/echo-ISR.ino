// echo example using interrupt-driven receive

#include <picoUART.h>

void setup()
{
    prints("\npicoUART rxISR echo ");
}

void loop()
{
    if ( purx_dataready() )
    {
        prints(" got: ");
        putx(pu_read());
        putx('\n');
    }
}

