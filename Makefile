CC=i386-elf-gcc
AS=i386-elf-as
LD=i386-elf-ld

INCLUDE_DIR=include

CCFLAGS= -c -std=gnu99 -ffreestanding -Wall -Wextra
CCFLAGS+= -fno-stack-protector -I $(INCLUDE_DIR)
ASFLAGS= 
LDFLAGS= -T linker.ld -nostdlib

BOOT_SRC=boot/boot.S
STAGE_TWO_SRC=boot/start.S

KERNEL_SRC=src/kernel.c
KERNEL_OBJ=$(KERNEL_SRC:.c=.o)

DRIVERS_C_SRC=$(wildcard drivers/*.c)
DRIVERS_C_OBJ=$(DRIVERS_C_SRC:.c=.o)

DRIVERS_S_SRC=$(wildcard drivers/*.S)
DRIVERS_S_OBJ=$(DRIVERS_S_SRC:.S=.o)

DRIVERS_OBJ=$(DRIVERS_C_OBJ) $(DRIVERS_S_OBJ)


OBJS=$(KERNEL_OBJ) $(DRIVERS_OBJ)


%.o: %.c
	$(CC) -o $@ -c $< $(CCFLAGS)

%.o: %.S
	$(AS) -o $@ -c $< $(ASFLAGS)


all: clean bootsect kernel iso run

clean:
	rm -rf *.bin
	rm -rf *.o
	rm -rf bin
	rm -rf drivers/*.o
	rm -rf src/*.o
	rm -rf boot/*.o
	rm -rf *.img
	rm -rf *.iso


bootsect:
	mkdir -p bin
	$(AS) -o bin/bootsect.o boot/boot.S
	$(LD) -o bin/bootsect.bin bin/bootsect.o -Ttext 0x7c00 --oformat binary

kernel: $(KERNEL_OBJ) $(DRIVERS_C_OBJ) $(DRIVERS_S_OBJ)
	mkdir -p bin
	$(AS) -o bin/stage2.o src/start.S
	$(LD) -o bin/kernel.bin bin/stage2.o $(OBJS) $(LDFLAGS) 


iso: bootsect kernel
	dd if=/dev/zero of=RodrigoX.iso bs=512 count=2880
	dd if=./bin/bootsect.bin of=RodrigoX.iso conv=notrunc bs=512 seek=0 count=1
	dd if=./bin/kernel.bin of=RodrigoX.iso conv=notrunc bs=512 seek=1 count=2048

run: iso
	qemu-system-i386 -rtc base=localtime -drive format=raw,file=RodrigoX.iso -d cpu_reset -monitor stdio 