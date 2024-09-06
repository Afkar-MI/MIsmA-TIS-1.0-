
//
// Included Files
//
#include "OutPinsConfig.h"
#include "F28x_Project.h"
#include "uart.h"

// Buffer to store data received from PC
uint16_t uart_recv_buf [82] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00};

//Buffer to store data for each rows.
uint16_t  row_1_data_buf[5]  = {0x00, 0x00, 0x00, 0x00, 0x00};
uint16_t  row_2_data_buf[5]  = {0x00, 0x00, 0x00, 0x00, 0x00};
uint16_t  row_3_data_buf[5]  = {0x00, 0x00, 0x00, 0x00, 0x00};
uint16_t  row_4_data_buf[5]  = {0x00, 0x00, 0x00, 0x00, 0x00};
uint16_t  row_5_data_buf[5]  = {0x00, 0x00, 0x00, 0x00, 0x00};
uint16_t  row_6_data_buf[5]  = {0x00, 0x00, 0x00, 0x00, 0x00};
uint16_t  row_7_data_buf[5]  = {0x00, 0x00, 0x00, 0x00, 0x00};
uint16_t  row_8_data_buf[5]  = {0x00, 0x00, 0x00, 0x00, 0x00};
uint16_t  row_9_data_buf[5]  = {0x00, 0x00, 0x00, 0x00, 0x00};
uint16_t  row_10_data_buf[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
uint16_t  row_11_data_buf[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
uint16_t  row_12_data_buf[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
uint16_t  row_13_data_buf[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
uint16_t  row_14_data_buf[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
uint16_t  row_15_data_buf[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
uint16_t  row_16_data_buf[5] = {0x00, 0x00, 0x00, 0x00, 0x00};

//Buffer to test
uint16_t  row_t_data_buf[5]  = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint16_t  row_tz_data_buf[5] = {0x00, 0x00, 0x00, 0x00, 0x00};

int OUTPUT[40] = {OUT_1, OUT_2, OUT_3, OUT_4, OUT_5, OUT_6, OUT_7, OUT_8,
              OUT_9, OUT_10, OUT_11, OUT_12, OUT_13, OUT_14, OUT_15,
              OUT_16, OUT_17, OUT_18, OUT_19, OUT_20, OUT_21, OUT_22,
              OUT_23, OUT_24, OUT_25, OUT_26, OUT_27, OUT_28, OUT_29,
              OUT_30, OUT_31, OUT_32, OUT_33, OUT_34, OUT_35, OUT_36,
              OUT_37, OUT_38, OUT_39, OUT_40}; // Output data pins

uint16_t flag_uart_recv = 0;

void extractData(void);

int main(void)
{
    InitSysCtrl();
    InitGpio();

    outPinsConfig();    // Initiate pins configurations for shift register and output data pins
    //uart_init();        // Initiate UART


    while(1)
    {
        uart_init();        // Initiate UART
        EINT;
        if (flag_uart_recv ==1){

            extractData(); // extract data for each rows

            /*line_En(ROW_16);            //enable Row 16
            data_out(row_16_data_buf);  //send data for Row 16
            DELAY_US(100*1000);         //100 ms delay

            line_En(ROW_15);
            data_out(row_15_data_buf);
            DELAY_US(100*1000);

            line_En(ROW_14);
            data_out(row_14_data_buf);
            DELAY_US(100*1000);         //100 ms delay

            line_En(ROW_13);
            data_out(row_13_data_buf);
            DELAY_US(100*1000);

            line_En(ROW_12);
            data_out(row_13_data_buf);
            DELAY_US(100*1000);         //100 ms delay

            line_En(ROW_11);
            data_out(row_11_data_buf);
            DELAY_US(100*1000);

            line_En(ROW_10);
            data_out(row_10_data_buf);
            DELAY_US(100*1000);         //100 ms delay

            line_En(ROW_9);
            data_out(row_9_data_buf);
            DELAY_US(100*1000);

            line_En(ROW_8);
            data_out(row_8_data_buf);
            DELAY_US(100*1000);         //100 ms delay

            line_En(ROW_7);
            data_out(row_7_data_buf);
            DELAY_US(100*1000);

            line_En(ROW_6);
            data_out(row_6_data_buf);
            DELAY_US(100*1000);         //100 ms delay

            line_En(ROW_5);
            data_out(row_5_data_buf);
            DELAY_US(100*1000);

            line_En(ROW_4);
            data_out(row_4_data_buf);
            DELAY_US(100*1000);         //100 ms delay

            line_En(ROW_3);
            data_out(row_3_data_buf);
            DELAY_US(100*1000);
            */

            /*line_En(ROW_All);
            data_out(row_tz_data_buf);
            DELAY_US(100*1000);
                */

            line_En(ROW_2);
            data_out(row_tz_data_buf);
            DELAY_US(100*1000);         //100 ms delay


            line_En(ROW_1);
            data_out(row_t_data_buf);
            DELAY_US(100*1000);

            flag_uart_recv = 0;

        }

    }
}

// Extract data for each rows
void extractData(void){
    int i;
    for(i=0; i<5; i++){

        row_1_data_buf[i]  = uart_recv_buf[i+2];
        row_2_data_buf[i]  = uart_recv_buf[i+7];
        row_3_data_buf[i]  = uart_recv_buf[i+12];
        row_4_data_buf[i]  = uart_recv_buf[i+17];
        row_5_data_buf[i]  = uart_recv_buf[i+22];
        row_6_data_buf[i]  = uart_recv_buf[i+27];
        row_7_data_buf[i]  = uart_recv_buf[i+32];
        row_8_data_buf[i]  = uart_recv_buf[i+37];
        row_9_data_buf[i]  = uart_recv_buf[i+42];
        row_10_data_buf[i] = uart_recv_buf[i+47];
        row_11_data_buf[i] = uart_recv_buf[i+52];
        row_12_data_buf[i] = uart_recv_buf[i+57];
        row_13_data_buf[i] = uart_recv_buf[i+62];
        row_14_data_buf[i] = uart_recv_buf[i+67];
        row_15_data_buf[i] = uart_recv_buf[i+72];
        row_16_data_buf[i] = uart_recv_buf[i+77];

  }
}

