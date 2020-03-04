INCS = src/
OBJECTS = src/init/loader.o src/kernel/kmain.o \
		  src/peripheral/framebuffer/framebuffer.o \
		  src/peripheral/framebuffer/framebuffer.s.o \
		  src/peripheral/io.s.o
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		 -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -I$(INCS)
LDFLAGS = -T libs/ld/link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

OUT = iso/boot/kernel.elf

all: $(OUT)

$(OUT): $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o $(OUT)

os.iso: $(OUT)
	xorrisofs -R                                \
				-b boot/grub/stage2_eltorito    \
				-no-emul-boot                   \
				-boot-load-size 4               \
				-A os                           \
				-input-charset utf8             \
				-quiet                          \
				-boot-info-table                \
				-o os.iso                       \
				iso

run: os.iso
	bochs -f bochsrc.txt -q

qemu: os.iso
	qemu-system-i386 -cdrom os.iso -serial mon:stdio -m 1G -soundhw ac97,pcspk \
	-enable-kvm -rtc base=localtime

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.s.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf $(OUT) os.iso $(OBJECTS)
