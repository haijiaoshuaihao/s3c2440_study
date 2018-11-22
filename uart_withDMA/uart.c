#include "s3c2440_soc.h"
char * testbuffer = "this is a demo!" ;

unsigned int mystrlen(const char *p)
{
	unsigned int i = 0;
	while(p[i])
		i++;
 
	return i;
}


/* 115200,8n1 */
void uart0_init()
{
	/* 设置引脚用于串口 */
	/* GPH2,3用于TxD0, RxD0 */
	GPHCON &= ~((3<<4) | (3<<6));
	GPHCON |= ((2<<4) | (2<<6));

	GPHUP &= ~((1 << 2) | (1 << 3)); /* 使能内部上拉 */

	/* 设置波特率 */
	/* UBRDIVn = (int)( UART clock / ( buad rate x 16) ) –1
	 *  UART clock = 50M
	 *  UBRDIVn = (int)( 50000000 / ( 115200 x 16) ) –1 = 26
	 */
	UCON0 = 0x00000009; /* PCLK,中断/查询模式 */
	UBRDIV0 = 26;

	/* 设置数据格式 */
	ULCON0 = 0x00000003; /* 8n1: 8个数据位, 无较验位, 1个停止位 */
}

int putchar(int c)
{
	/* UTRSTAT0 */
	/* UTXH0 */

	while (!(UTRSTAT0 & (1<<2)));
	UTXH0 = (unsigned char)c;
	
	return 0;
}

int getchar(void)
{	
	while (!(UTRSTAT0 & (1<<0)));
	return URXH0;
}

int puts(const char *s)
{
	while (*s)
	{
		putchar(*s);
		s++;
	}
	return 0;
}

int put_str()
{
	//unsigned int size = mystrlen(s);
	DISRC0 = (unsigned int)testbuffer;
	DCON0 |= 20;
	return 0;
}

/*int put_str(const char * s)
{
	unsigned int size =  mystrlen(s); 	
    DISRC0 = (unsigned int) s;
	DCON0 |= size ;
	return 0;
}*/

/* 0xABCDEF12 */
void printHex(unsigned int val)
{
	int i;
	unsigned char arr[8];

	/* ��ȡ��ÿһλ��ֵ */
	for (i = 0; i < 8; i++)
	{
		arr[i] = val & 0xf;
		val >>= 4;   /* arr[0] = 2, arr[1] = 1, arr[2] = 0xF */
	}

	/* ��ӡ */
	puts("0x");
	for (i = 7; i >=0; i--)
	{
		if (arr[i] >= 0 && arr[i] <= 9)
			putchar(arr[i] + '0');
		else if(arr[i] >= 0xA && arr[i] <= 0xF)
			putchar(arr[i] - 0xA + 'A');
	}
	return;
}
void print1(void)
{
	puts("abc\n\r");
}

void print2(void)
{
	puts("123\n\r");
}

void printSWIVal(unsigned int *pSWI)
{
	puts("SWI val = ");
	printHex(*pSWI &0xffffff);
	puts("\n\r");
}

void printCPSR(unsigned int cpsr)
{
	puts("Exception! cpsr = ");
	printHex(cpsr);
	puts("\n\r");
}