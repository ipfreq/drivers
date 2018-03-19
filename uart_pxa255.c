#include"uart.h"
void serialInit(void)
{
  static int bInitialized =FALSE;
  /*Initialize the UART only once. */
  if(bInitialized==FALSE)
  {
    /*Set the communication parameters. */
    gSerialParams.baudRate=115200;
    gSerialParams.dataBits=DATA_8;
    gSerialParams.parity=PARITY_NONE;
    gSerialParams.stopBits=STOP_1;
    serialConfig(&gSerialParams);
    bInitialized=TRUE;
  }
}

void SerialPutChar(char outputChar)
{
  /*Wait until the transmitter is redy for the next character.*/
  while ((pSerialPort->uartStatus&TRANSMITTER_EMPTY)==0)
   ;
/*Send the character via the serial port.*/
pSerialPort->data=outputChar;

}

char serialGetChar(void)
{
  /*Wait for the next character to arrive.*/
  while((pSerialPort->uartStatus&DATA_READY)==0)
  ;
  return pSerialPort->data;
}
