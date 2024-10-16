//function.c//

#include "functions.h"
#include <stdint.h>
#include <stdio.h>
#define USART1_BASE (0x40011000)

enum message{
    USART_TX_ERROR,         //0 (no data provided)
    USART_TX_BUSY,          //1 (the transmission is busy or timed out)
    USART_TX_INCOMPLETE,    //2 (the trasmission is incomplite due to an early null-terminator)
    USART_TX_COMPLETE,      //3 (the trasmission is complete)

};

typedef struct{
    uint32_t data_reg;
    uint32_t status_reg;

} usart1_t;

#define usart ((usart1_t *) USART1_BASE)


const uint32_t TIMEOUT = 10;

uint32_t usart_tx_start(const uint8_t *data_bytes, uint32_t n_bytes){

    uint32_t timeout = TIMEOUT;

    usart->data_reg = 'A';

    if (data_bytes == NULL){
        return USART_TX_ERROR;
    }

    for (uint32_t i = 0; i<n_bytes; i++){

        while(!usart_is_tx_ready()){
            timeout--;
            if (timeout == 0){
                return USART_TX_BUSY;
            }
            
        }

        usart->data_reg = data_bytes[i];

        if( data_bytes[i+1] == '\0'){
            return USART_TX_INCOMPLETE;
        }

    }

    return USART_TX_COMPLETE;

}


uint32_t usart_is_tx_ready(void){

    uint32_t mask = 0x80; // 10000000

    if (usart->status_reg & mask){
        return 1; //the buffer is ready
    }

    else{
        return 0; //the buffer is not ready
    }
}

void delay_routine_1(void){
    __asm(
        "mov r1,#11 \n"
        "loop: \n"
        "sub r1,r1,#1 \n"
        "cmp r1,#0 \n"
        "bne loop \n"


    );
}

void delay_routine_2(unsigned int delay_counter){
    __asm(
        "mov r0, %0 \n"    // Move the value of delay_counter into r0
        "loop2: \n"
        "sub r0,r0,#1 \n"
        "cmp r0,#0 \n"
        "bne loop2 \n"

        :                   // No output
        : "r" (delay_counter) // Input: delay_counter
    );
}