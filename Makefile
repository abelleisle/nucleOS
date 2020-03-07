ARCH = i686
ARCHDIR = src/arch/$(ARCH)
include $(ARCHDIR)/make.config

CROSS = toolchain/i686-elf/bin/i686-elf-
CC = $(CROSS)gcc
AS = nasm
LD = $(CROSS)ld

KERNEL_OBJECTS = $(KERNEL_ARCH_OBJS)                        \
				 src/kernel/kmain.o                         \
		  		 src/peripheral/framebuffer/framebuffer.o   \
		  		 src/peripheral/framebuffer/framebuffer.s.o \
		  		 src/peripheral/io.s.o

OBJECTS = $(ARCHDIR)/crti.s.o   \
		  $(ARCHDIR)/crtbegin.o \
		  $(KERNEL_OBJECTS)     \
		  $(ARCHDIR)/crtend.o   \
		  $(ARCHDIR)/crtn.s.o

INCS = -Isrc/ -L./toolchain/i686-elf/lib/gcc/i686-elf/8.2.0
CFLAGS = -nostdlib -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c $(INCS)
ASFLAGS = -f elf32
LDFLAGS = -T $(ARCHDIR)/link.ld -nostdlib -lgcc $(INCS)

OUT = iso/boot/kernel.elf

all: $(OUT)

$(ARCHDIR)/crtbegin.o $(ARCHDIR)/crtend.o:
	TOBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$TOBJ" $@

$(OUT): $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $(OUT)

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
