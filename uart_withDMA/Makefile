CFLAGS = -mcpu=arm920t -mabi=aapcs -fno-stack-protector -c -o
all: start.o led.o uart.o init.o main.o exception.o interrupt.o dma.o
	#arm-linux-ld -Ttext 0 -Tdata 0x30000000  start.o led.o uart.o init.o main.o -o sdram.elf
	arm-linux-gnueabi-ld -T sdram.lds $^ -o sdram.elf
	arm-linux-gnueabi-objcopy -O binary -S sdram.elf sdram.bin
	arm-linux-gnueabi-objdump -D sdram.elf > sdram.dis
clean:
	rm  *.o *.elf *.dis *.bin

%.o : %.c
	arm-linux-gnueabi-gcc-8 $(CFLAGS)  $@ $<

%.o : %.S
	arm-linux-gnueabi-gcc-8 $(CFLAGS)  $@ $<
