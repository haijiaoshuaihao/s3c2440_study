
#include "s3c2440_soc.h"
#include "uart.h"
#include "init.h"
#include "interrupt.h"

char g_Char = 'A';
char g_Char3 = 'a';
const char g_Char2 = 'B';
int g_A = 0;
int g_B;
void delay(volatile int d);
int led_init(void);
void dma_init();

int main(void)
{
	led_init();
	dma_init("thank you,dma!");
	interrupt_init();  /*初始化终端控制器*/
	key_eint_init();   /*初始化中断源，设置为外部按键*/
	//uart0_init();
   // put_str("This is a demo!\r\n"); 
	//put_str();
	puts("\n\rg_A = ");
	printHex(g_A);
	puts("\n\r");

	while (1)
	{
#if 0
		puts("\n\rg_Char = ");
		printHex(g_Char);
		puts("\n\r");


		puts("\n\rg_Char3 = ");
		printHex(g_Char3);
		puts("\n\r");
#endif
		putchar(g_Char);
		g_Char++;

		putchar(g_Char3);
		g_Char3++;
		delay(1000000);
	}


	return 0;
}
