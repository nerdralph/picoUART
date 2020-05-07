// echo example using interrupt-driven receive

#include <picoUART.h>

void setup()
{
    prints("\npicoUART rxISR echo\n");
}

void loop()
{
    if ( purx_dataready() )
    {
        char c = pu_read();
        prints(" got: ");
        putx(c);
        putx('\n');
    }
}

