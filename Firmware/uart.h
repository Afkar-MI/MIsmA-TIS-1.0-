/*
 * uart.h
 *
 *  Created on: Jan 31, 2024
 *      Author: afkar.mi
 */

#ifndef UART_H_
#define UART_H_



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "F28x_Project.h"

#define UART_RECV_TIMOUT_VALUE      0xFBBB
#define UART_RECV_FLAG              SciaRegs.SCIFFRX.bit.RXFFST

#define HEADER                      0x0040  // Frame Header UART Data
#define DATA_LENGTH                 0x0050  // Data Length from PC (80 Bytes)
#define UART_RECV_LENGTH            0x0052  // Data Length (whole lenght , 82 bytes)

extern uint16_t uart_recv_buf[82];
extern uint16_t flag_uart_recv;

void scia_echoback_init(void);
void scia_fifo_init(void);
void scia_xmit(int a);
void scia_msg(char *msg);
void uart_init(void);

#endif /* UART_H_ */
