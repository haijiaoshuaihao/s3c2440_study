
#include "s3c2440_soc.h"
#include "interrupt.h"

void interrupt_init(void)
{
   INTMSK &=~ ( (1<<0) | (1<<2) | (1<<5) );
}

void key_eint_init(void)
{
   /*根据JZ2440的按键 配置这些引脚为外部中断*/ 
   GPFCON &=~ ((3<<0) | (3<<4));
   GPFCON |=  ((2<<0) | (2<<4));
   GPGCON &=~ ((3<<6) | (3<<22));
   GPGCON |=  ((2<<6) | (2<<22));

   /*设置中断触发方式：双边缘触发*/
   EXTINT0 |= ( (7<<0) | (7<<8) );
   EXTINT1 |=  (7<<12) ;
   EXTINT2 |=  (7<<12) ;

   /*设置中断屏蔽寄存器*/
   EINTMASK &=~  ((1<<11)|(1<<19));
}

void handle_irq_c(void)
{
	/*分辨中断源*/
	int bit = INTOFFSET;
	if (bit == 0 || bit == 2 || bit == 5)
	{
		key_eint_irq(bit);
	}
	else if(bit == 17)
	{
		dma_eint_irq();
	}
	/*清除中断，从源头开始*/
	SRCPND = (1<<bit);
	INTPND = (1<<bit);
}


void dma_eint_irq()
{
	GPFDAT &=~ ( (1<<4)|(1<<6) );
	GPFDAT |= (1<<5);
}

/* 读EINTPEND分辨率哪个EINT产生(eint4~23)
 * 清除中断时, 写EINTPEND的相应位
 */


void key_eint_irq(int irq)
{
	unsigned int val = EINTPEND;
	unsigned int val1 = GPFDAT;
	unsigned int val2 = GPGDAT;
	
	if (irq == 0) /* eint0 : s2 控制 D12 */
	{
		if (val1 & (1<<0)) /* s2 --> gpf6 */
		{
			/* 松开 */
			GPFDAT |= (1<<6);
		}
		else
		{
			/* 按下 */
			GPFDAT &= ~(1<<6);
		}
		
	}
	else if (irq == 2) /* eint2 : s3 控制 D11 */
	{
		if (val1 & (1<<2)) /* s3 --> gpf5 */
		{
			/* 松开 */
			GPFDAT |= (1<<5);
		}
		else
		{
			/* 按下 */
			GPFDAT &= ~(1<<5);
		}
		
	}
	else if (irq == 5) /* eint8_23, eint11--s4 控制 D10, eint19---s5 控制所有LED */
	{
		if (val & (1<<11)) /* eint11 */
		{
			if (val2 & (1<<3)) /* s4 --> gpf4 */
			{
				/* 松开 */
				GPFDAT |= (1<<4);
			}
			else
			{
				/* 按下 */
				GPFDAT &= ~(1<<4);
			}
		}
		else if (val & (1<<19)) /* eint19 */
		{
			if (val2 & (1<<11))
			{
				/* 松开 */
				/* 熄灭所有LED */
				GPFDAT |= ((1<<4) | (1<<5) | (1<<6));
			}
			else
			{
				/* 按下: 点亮所有LED */
				GPFDAT &= ~((1<<4) | (1<<5) | (1<<6));
			}
		}
	}

	EINTPEND = val;/*对应位置写1清除*/
}