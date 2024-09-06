/*
 * OP_Config.c
 *
 *  Created on: Jan 26, 2024
 *      Author: afkar.mi
 */

// OUTPUT configurations
// we have 40 digital data outputs.


#include "OutPinsConfig.h"

void outPinsConfig(void){

    clear_register();   // Clear all the Outputs
    clockPinsInit();    // Initiate Shift Register clock pins
    outputPinsInit();   //Initiate Output data pins

}

/*-----------------------------Shift Register---------------------------------*/
// Clear the Outputs of MCU
void clear_register(void){
   GPIO_WritePin(nChip_Select , 1);     // Disable  the Output // Hold the operations
   //GPIO_WritePin(STR_CLK, 0);           // set Store clock to low
   //GPIO_WritePin(nSR_CLK, 0);            // Set Shift Register clock to Low
   GPIO_WritePin(SER_Data, 0);          // Set the Serial Data to Low
   DELAY_US(100*1000);                  //500 ms delay

   //// Enable Register Shift operation.
   // CS- LOW; R/*W - LOW
   GPIO_WritePin(nChip_Select, 0);    //
   GPIO_WritePin(Read_Write, 0);      // Register - Read State
   DELAY_US(100*1000);         //500 ms delay
}


// Pin Configurations for Shift Register Pins
void clockPinsInit(void){
    // Set the pin configuration and CPU
    GPIO_SetupPinMux(Read_Write, GPIO_MUX_CPU1, 0);                 // Shift Register Clear
    GPIO_SetupPinOptions(Read_Write, GPIO_OUTPUT, GPIO_PUSHPULL);

    GPIO_SetupPinMux(STR_CLK, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(STR_CLK, GPIO_OUTPUT, GPIO_PUSHPULL);

    GPIO_SetupPinMux(nSR_CLK, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(nSR_CLK, GPIO_OUTPUT, GPIO_PUSHPULL);

    GPIO_SetupPinMux(SER_Data, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(SER_Data, GPIO_OUTPUT, GPIO_PUSHPULL);

    GPIO_SetupPinMux(nChip_Select, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(nChip_Select, GPIO_OUTPUT, GPIO_PUSHPULL);

}

//Shift Register Clock
void ShiftReg_CLK(void){
    GPIO_WritePin(nSR_CLK, 0);   // Shift Register CLK high
    DELAY_US(100*1000);         //500 ms delay

    GPIO_WritePin(nSR_CLK, 1);   // Shift Register CLK Low
    DELAY_US(100*1000);         // 500 ms Delay
}

// Store Register Clock
void StoreReg_CLK(void){
    GPIO_WritePin(STR_CLK, 0);  // Store Register CLK low
    DELAY_US(100*1000);         //500 ms delay

    GPIO_WritePin(STR_CLK, 1);  // Store Register CLK high
    DELAY_US(500*1000);         // 500 ms Delay
}


//Enable each Row to receive the Output data
void line_En(Uint16 data_line){
    GPIO_WritePin(STR_CLK, 0);  // Store Register CLK low
    GPIO_WritePin(nChip_Select, 0);
    int i=0;
    // Enable Each Row line one by one
    for (i=0; i<16 ; i++){ // 16 clock cycles
        GPIO_WritePin(SER_Data, (data_line>>i) & 0x01);
        ShiftReg_CLK();
     }


    GPIO_WritePin(STR_CLK, 1);  // Store Register CLK low
    ShiftReg_CLK();

}
/*-----------------------------------------------------------------------------*/

/*------------------------------Data Outputs------------------------------*/

// Pins configuration of Output data pins
void outputPinsInit(void){

    int i;
    for (i=0; i <40; i++){

        GPIO_SetupPinMux(OUTPUT[i], GPIO_MUX_CPU1, 0);   // Set the pin configuration and CPU
        GPIO_SetupPinOptions(OUTPUT[i], GPIO_OUTPUT, GPIO_PUSHPULL); // set the pin as outputs

    }

}

// Data Output for each columns (40 Columns) one by one

void data_out(Uint16 *data){
    int i=0;
    int j;
    for ( j=0; j<5 ; j++){

    GPIO_WritePin(OUTPUT[i],   data[j]>>7 & 0x01 );
    GPIO_WritePin(OUTPUT[i+1], data[j]>>6 & 0x01 );
    GPIO_WritePin(OUTPUT[i+2], data[j]>>5 & 0x01 );
    GPIO_WritePin(OUTPUT[i+3], data[j]>>4 & 0x01 );
    GPIO_WritePin(OUTPUT[i+4], data[j]>>3 & 0x01 );
    GPIO_WritePin(OUTPUT[i+5], data[j]>>2 & 0x01 );
    GPIO_WritePin(OUTPUT[i+6], data[j]>>1 & 0x01 );
    GPIO_WritePin(OUTPUT[i+7], data[j] & 0x01 );
    i = i+8;
    }
}

