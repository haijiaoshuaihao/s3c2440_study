#ifndef _UART_H
#define _UART_H

void uart0_init();
int putchar(int c);
int getchar(void);
int puts(const char *s);
void printHex(unsigned int val);
void printException(unsigned int cpsr, char *str);
//unsigned int put_str(const char * s);
int put_str();
unsigned int mystrlen(const char *p);
#endif

