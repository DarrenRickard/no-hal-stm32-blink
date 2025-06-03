// logger.h

#ifndef LOGGER_H
#define LOGGER_H

uint32_t const CLK_RATE;
uint16_t const BAUD_RATE;

void uart1_init(void);
void uart1_send_char(char c);
void uart1_send_string(const char *str);

#endif
