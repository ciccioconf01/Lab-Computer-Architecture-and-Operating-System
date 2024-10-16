//main.c//

#include "functions.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern uint32_t usart_tx_start(const uint8_t *data_bytes, uint32_t n_bytes);
extern uint32_t usart_is_tx_ready(void);
extern void delay_routine_1(void);
extern void delay_routine_2(unsigned int delay_counter);

int main(){

    int val = 0;
    int val2 = 0;
    
    const uint8_t message_to_send[] = "Ciaone";

    while (1){


        val2 = usart_tx_start(message_to_send, sizeof(message_to_send));

        if (val2==4){
            break;
        }
        else{
            ;
        }

        delay_routine_2(2000);
    }

    if (val2 == 0){
        usart_tx_start("ERROR: no data provided", sizeof("ERROR: no data provided"));
    }
    else if (val2 == 1){
        usart_tx_start("ERROR: the transmission is busy or timed out", sizeof("ERROR: the transmission is busy or timed out"));
    }
    else if (val2 == 2){
        usart_tx_start("ERROR: the trasmission is incomplite due to an early null-terminator", sizeof("ERROR: the trasmission is incomplite due to an early null-terminator"));
    }
    else if (val2 == 3){
        usart_tx_start("COMPLETE: the trasmission is complete", sizeof("COMPLETE: the trasmission is complete"));
    }
}