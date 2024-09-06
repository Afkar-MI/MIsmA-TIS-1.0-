/*
 * OP_Config.h
 *
 *  Created on: Jan 26, 2024
 *      Author: afkar.mi
 */

#ifndef OUTPINSCONFIG_H_
#define OUTPINSCONFIG_H_

#include "driverlib.h"
#include "device.h"
#include "F28x_Project.h"

#define OUT_1     67
#define OUT_2     18
#define OUT_3     19
#define OUT_4     32
#define OUT_5     16
#define OUT_6     24
#define OUT_7     5
#define OUT_8     4
#define OUT_9     3
#define OUT_10     2
#define OUT_11     1
#define OUT_12     0
#define OUT_13     61
#define OUT_14     123
#define OUT_15     122
#define OUT_16     58
#define OUT_17     59
#define OUT_18     124
#define OUT_19     125
#define OUT_20     29
#define OUT_21     66
#define OUT_22     131
#define OUT_23     130
#define OUT_24     63
#define OUT_25     64
#define OUT_26     26
#define OUT_27     27
#define OUT_28     25
#define OUT_29     15
#define OUT_30     14
#define OUT_31     11
#define OUT_32     10
#define OUT_33     9
#define OUT_34     8
#define OUT_35     7
#define OUT_36     6
#define OUT_37     40
#define OUT_38     41
#define OUT_39     52
#define OUT_40     65

#define ROW_1     0x8000    //0b1000000000000000
#define ROW_2     0x4000    //0b0100000000000000
#define ROW_3     0x2000    //0b0010000000000000
#define ROW_4     0x1000    //0b0001000000000000
#define ROW_5     0x0800    //0b0000100000000000
#define ROW_6     0x0400    //0b0000010000000000
#define ROW_7     0x0200    //0b0000001000000000
#define ROW_8     0x0100    //0b0000000100000000
#define ROW_9     0x0080    //0b0000000010000000
#define ROW_10    0x0010    //0b0000000001000000
#define ROW_11    0x0020    //0b0000000000100000
#define ROW_12    0x0010    //0b0000000000010000
#define ROW_13    0x0008    //0b0000000000001000
#define ROW_14    0x0004    //0b0000000000000100
#define ROW_15    0x0002    //0b0000000000000010
#define ROW_16    0x0001    //0b0000000000000001
#define ROW_All   0xFFFF

#define Read_Write      104       // Shift Register Read and *Write // *write - triggered for negative
#define STR_CLK         105       // Store Register Clock
#define nSR_CLK         22        // Shift Register Clock - triggered for Negative, add 'n' mentioned it's negative
#define SER_Data        60        // Serial Data to enable the each row the latch array
#define nChip_Select    111       // Chip Select - Clear the Register and hold operations // Triggered for negative


extern int OUTPUT[40];
                   // Output pins - Data

void outPinsConfig(void);
void clear_register(void);
void clockPinsInit(void);
void outputPinsInit(void);
void ShiftReg_CLK(void);
void StoreReg_CLK(void);
void line_En(Uint16 data_line);
void data_out(Uint16 *data);

#endif /* OUTPINSCONFIG_H_ */
