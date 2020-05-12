// echo example using interrupt-driven receive

#include <picoUART.h>
#include <pu_print.h>

const int buflen = 20;
char linebuf[buflen];

int readline()
{
    int count = 0;
    char c;
    do {
        while ( ! purx_dataready() );   // wait for data
        c = pu_read();
        linebuf[count++] = c;
    } while ( (c != '\n') && (count < buflen - 1) );
    linebuf[count] = '\0';
    return count;
}

void setup()
{
    prints("\nrxISR line echo\n");
}

void loop()
{
    if ( purx_dataready() )
    {
        readline();
        prints("got: ");
        prints(linebuf);
    }
}

