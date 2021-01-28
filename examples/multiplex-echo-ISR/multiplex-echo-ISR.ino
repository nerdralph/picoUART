#include <picoUART.h>
#include <pu_print.h>
#include <stdlib.h>

#define PU_BAUD_RATE 9600L
#define PU_TX B,4
#define PU_RX B,4

// Signal switch registers ATTiny85 - CD74HC4067
#define S0 0
#define S1 1
#define S2 2
#define S3 3

const int buflen = 20;
char linebuf[buflen];

uint8_t int_i;
char itoa_i[8];

int readline()
{
  int count = 0;
  char c;
  c = pu_read(); // waste
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
  // Setup pins for multiplexer CD74HC4067
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  // Switch multiplexer to TX output 0001b
  digitalWrite(S0, HIGH);
  prints("\nrxISR line echo\n");
  digitalWrite(S0, LOW); // back to rx
}

void loop()
{
  if ( purx_dataready() )
  {
    readline();
    // Switch multiplexer to TX output 0001b
    digitalWrite(S0, HIGH);

    prints("got: ");
    prints(linebuf);

    digitalWrite(S0, LOW); // RX - 0000b
  }
  // Switch multiplexer to analog in - 0010b
  digitalWrite(S1, HIGH);
  delay(500);
  int_i = analogRead(A2);

  // Switch to TX out from 0010b to 0001b
  digitalWrite(S1, LOW);
  digitalWrite(S0, HIGH);
  itoa(int_i, itoa_i, 10);
  for (int_i = 0; int_i < 7; int_i++) {
    if (itoa_i[int_i]) {
      
      putx(itoa_i[int_i]);
      
    }
    itoa_i[int_i] = false;
  }
  prints("\r\n");
  digitalWrite(S0, LOW); // back to rx - 0000b
}

