

//
// Included Files
//
#include "uart.h"
// Globals
//
Uint16 LoopCount;
 // Buffer to store data received



char *msg;
// Main
//
//-------------------------------UART RX /TX ------------------------------------------------------------//


uint16_t uart_recv_one_byte(uint16_t *fp)   // Receive one byte data
{
    uint32_t t;
    uint16_t dat;
    for (t = 0; t < UART_RECV_TIMOUT_VALUE; t++) {
        if (UART_RECV_FLAG != 0) {
            dat = SciaRegs.SCIRXBUF.all;
            *fp = 1;
            break;
        }
    }
    if (t >= UART_RECV_TIMOUT_VALUE) {
        dat = 0x00FF;
        *fp = 0;
    }
    return dat;
}



uint16_t uart_recv_data(uint16_t len, uint16_t* buff)  // Receive all data and
{                                                      // and store them in a buffer
    uint16_t i = 0;
    uint16_t flag = 1;
    for (i= 0 ; (i < len) & (flag == 1); i++){
        buff[i] = uart_recv_one_byte(&flag);
    }
    if ((i == len) & (flag == 1)) {
        msg = "\r\nSuccess \0";
        scia_msg(msg);

        return 1;   // success
    } else {
        return 0;   // fail
    }
}

void uart_init(void)
{

// PLL, WatchDog, enable Peripheral Clocks
  // InitSysCtrl();

// Initialize GPIO:
  // InitGpio();

// init the pins for the SCI-A port.
   GPIO_SetupPinMux(43, GPIO_MUX_CPU1, 0xF);
   GPIO_SetupPinOptions(43, GPIO_INPUT, GPIO_PUSHPULL);
   GPIO_SetupPinMux(42, GPIO_MUX_CPU1, 0xF);
   GPIO_SetupPinOptions(42, GPIO_OUTPUT, GPIO_ASYNC);
// Disable CPU __interrupts
//
   DINT;

// Initialize PIE control registers to their default state.
   InitPieCtrl();

// Disable CPU __interrupts and clear all CPU __interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).

   InitPieVectTable();

   LoopCount = 0;

   scia_fifo_init();       // Initialize the SCI FIFO
   scia_echoback_init();   // Initialize SCI for echoback

   msg = "\r\n\n\nHello World!\0";
   scia_msg(msg);

   //msg = "\r\nYou will enter a character, and the DSP will echo it back! \n\0";
   //scia_msg(msg);

   //for(;;)
   //{
       //Uint16 i;
       msg = "\r\nEnter a character: \0";
       scia_msg(msg);

       //
       // Wait for inc character
       //
       while(SciaRegs.SCIFFRX.bit.RXFFST == 0) { } // wait for empty state

       //
       // Get character
       //
       uart_recv_data(UART_RECV_LENGTH, uart_recv_buf);

       //Check the header and length of data
       if ((uart_recv_buf[0] == HEADER) && (uart_recv_buf[1] == DATA_LENGTH))
          {
              flag_uart_recv = 1;
           }

       //LoopCount++;
   //}
}

//
//  scia_echoback_init - Test 1,SCIA  DLB, 8-bit word, baud rate 0x000F,
//                       default, 1 STOP bit, no parity
//
void scia_echoback_init()
{
    //
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function
    //

    SciaRegs.SCICCR.all = 0x0007;   // 1 stop bit,  No loopback
                                    // No parity,8 char bits,
                                    // async mode, idle-line protocol
    SciaRegs.SCICTL1.all = 0x0003;  // enable TX, RX, internal SCICLK,
                                    // Disable RX ERR, SLEEP, TXWAKE
    SciaRegs.SCICTL2.all = 0x0003;
    SciaRegs.SCICTL2.bit.TXINTENA = 1;
    SciaRegs.SCICTL2.bit.RXBKINTENA = 1;

    //
    // SCIA at 9600 baud
    // @LSPCLK = 50 MHz (200 MHz SYSCLK) HBAUD = 0x02 and LBAUD = 0x8B.
    // @LSPCLK = 30 MHz (120 MHz SYSCLK) HBAUD = 0x01 and LBAUD = 0x86.
    //
    SciaRegs.SCIHBAUD.all = 0x0002;
    SciaRegs.SCILBAUD.all = 0x008B;

    SciaRegs.SCICTL1.all = 0x0023;  // Relinquish SCI from Reset
}

//
// scia_xmit - Transmit a character from the SCI
//
void scia_xmit(int a)
{
    while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}
    SciaRegs.SCITXBUF.all =a;
}

//
// scia_msg - Transmit message via SCIA
//
void scia_msg(char * msg)
{
    int i;
    i = 0;
    while(msg[i] != '\0')
    {
        scia_xmit(msg[i]);
        i++;
    }
}
// scia_fifo_init - Initialize the SCI FIFO
//

void scia_fifo_init()
{
    SciaRegs.SCIFFTX.all = 0xE040;
    SciaRegs.SCIFFRX.all = 0x2044;
    SciaRegs.SCIFFCT.all = 0x0;
}

//
// End of file
//
