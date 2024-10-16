//function.h//

#include <stdint.h>
#include <stdio.h>

uint32_t usart_tx_start(const uint8_t *data_bytes, uint32_t n_bytes);
uint32_t usart_is_tx_ready(void);
void delay_routine_1(void);
void delay_routine_2(unsigned int delay_counter);