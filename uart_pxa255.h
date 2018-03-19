typedef struct
{
  uint32_t data;
  unint32_t interruptEnable;
  unint32_t interruptStatus;
  unint32_t uartConfig;
  unint32_t pinConfig;
  unint32_t uartStatus;
  unint32_t pinStatus;
}volatile uart_t;

uart_t *pSerialPort=(uart_t *)(0x40100000);
/*UART Config Register (LCR) Bit Desicriptions*/

#define DATABITS_LENGTH_0       (0x01)
#define DATABITS_LENGTH_1       (0x02)
#define STOP_BITS               (0x04)
#define PARITY_ENABLE           (0x08)
#define EVEN_PARITY_ENABLE      (0x10)

typedef enum {PARITY_NONE,PARITY_ODD=PARITY_ENABLE,
  PARITY_EVEN=(PARITY_ENABLE|EVEN_PARITY_ENABLE)} parity_t;

  typedef enum {DATA_5,DATA_6=DATABITS_LENGTH_0,DATA_7=DATABITS_LENGTH_1,
  DATA_8=(DATABITS_LENGTH_0|DATABITS_LENGTH_1)}databits_t;

  typedef enum{STOP_1,STOP_2=STOP_BITS}stopbits_t;

  typedef struct
  {
    uint32_t dataBits;
    uint32_t stopBits;
    unint32_t baudRate;
    unint32_t parity;
  }serialparams_t;

  serialparams_t gSerialParams;
  void serialInit(void);
#define TRANSMITTER_EMPTY     (0x40)
void serialPutChar(char outputChar);
#define DATA_READY            (0X01)
char serialGetChar(void);
