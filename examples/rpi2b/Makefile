all:
	arm-none-eabi-gcc -mcpu=cortex-a7 -fpic -ffreestanding -c src/boot.S -o out/boot.o
	arm-none-eabi-gcc -mcpu=cortex-a7 -fpic -ffreestanding -std=gnu99 -c src/kernel.c -o out/kernel.o -O2 -Wall -Wextra
	arm-none-eabi-gcc -T ld/linker.ld -o out/os.elf -ffreestanding -O2 -nostdlib out/boot.o out/kernel.o

run:
	qemu-system-arm -m 1G -M raspi2b -serial stdio -kernel out/os.elf
