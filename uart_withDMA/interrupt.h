#ifndef _INTERRUPT_H
#define _INTERRUPT_H

void interrupt_init(void);
void key_eint_init(void);
void handle_irq_c(void);
void key_eint_irq(int irq);
void dma_eint_irq();

#endif