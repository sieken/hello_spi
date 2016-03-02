/* main.c

   this uses the chipkit as master to send characters to a gameboy
   via SPI */

#include <stdint.h>
#include <pic32mx.h>


uint8_t clrBuf;
uint8_t handshake = 0x00;
char message[] = {
  'S','o','c','i','l','i','s','t','e','r',' ','h','e','m','+',0x0D,
  'u','r',' ','h','u','s','e',' ','h','a',' ','h','a','+','+',0x0D,
  'l','o','l',',','t','r','o','d','d','e',' ','d','u','+','+',0x0D,
  'j','a','.',' ','*','F','i','s','*','+','+','+','+','+','+',0x0D,
};


#define MS_LENGTH   (sizeof(message)/sizeof(message[0]))
#define SLEEP       10000000

void spi_init (void);
void send (char c);
void sleep (void);

/* SPI initialization routine */
void spi_init (void) {
  SPI2CON = 0;
  IEC(1) = 0;
  IPC(7) = 0;
  IFS(1) = 0;

  SPI2BRG = 0x1FF;      // Set SCK ~78kHz
  SPI2STATCLR = 0x40;
  SPI2CON = 0x8060;     // Set ON, CKE, MSTEN
}

/* send one character (byte) of data via SPI */
void send (char c) {
  while(!(SPI2STAT & 0x08));
  SPI2BUF = c;
  while(!(SPI2STAT & 0x01));
  clrBuf = (uint8_t)SPI2BUF;

  /*check if incoming data matches handshake*/
  if (clrBuf == (uint8_t)0xAA) {
    handshake = (uint8_t)clrBuf;
  }
}

/* bad sleep function */
void sleep (void) {
  int i;
  for (i = 0; i < SLEEP; i++) {/* do nothing */}
}

int main (void) {
  uint8_t ccount = 0x00;
  char c;
  char idle_send = 0xAA;

  /* initialize SPI & LED5 */
  spi_init();
  TRISF &= ~0x01;
  PORTF &= ~0x01;

  /*test handshake routine*/
  while (1) {
    PORTF = 0x01;
    sleep();
    send(idle_send);
    if (handshake == 0xAA) {
      break;
    }
  }

  /* main routine */
  while (1) {
    PORTF = 0x00;             //turns light off when main runs
    c = message[ccount];
    sleep();
    send (c);
    ccount++;
    if (ccount > MS_LENGTH)
      ccount = 0;

  }
  return 0;
}
