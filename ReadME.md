# RodrigoX OS 
A hobby operating system for x86 Intel machines.

<img src="images/Screenshot 2024-08-03 at 00.55.12.png" draggable="false">

## Overview 
RodrigoX is a work-in-progress operating system designed to run on x86 Intel machines. The project aims to create a fully functional OS with a custom bootloader, device drivers, and a user-friendly interface.

# Features

## Implemented
- Interrupt Descriptor Table (IDT): Handles interrupts and exceptions
- Global Descriptor Table (GDT): Manages memory segmentation
- Interrupt Service Routines (ISR): Handles interrupts and exceptions
- Interrupt Request (IRQ): Handles hardware interrupts
- Keyboard Driver: Supports keyboard input
- Timer Driver: Manages system time and scheduling
- Screen Driver: VGA video mode in 640x480 with 16 colors
- Custom Bootloader: Loads the OS into memory
- Added multiboot: Added multiboot support for loading the OS into memory when the custom bootloader fails to.

## Planned Features
- File System (FS): Implement a file system for storing and retrieving data
- User Space: Create a user-friendly interface and separate user space from kernel space
- Security: Implement security measures to protect the OS and user data
- Custom font glyphs: custom 8x16 font glyphs for the system to use, glyphs will be made using ```tools/Fony.exe```


## Build requirements

- ```i386-elf-toolchain``` for the custom loader and compoments

- ```grub-mkrescue``` to build the multiboot image
- ```xorriso``` to build the multiboot image (used by grub)

- ```qemu-system``` to test the built images.

Dont know if everything is installed? use ```toolchain.sh``` to check id the required tools are installed or not.
## Building and Running

To build and run RodrigoX with the custom bootloader, follow these steps:

1. clone the repo:
```bash
git clone https://github.com/tijn714/RodrigoX.git

```

2. cd into project folder
3. to build the ISO:
```bash
make iso
```

4. To run using QEMU:
```bash
qemu-system-i386 -rtc base=localtime  -drive format=raw,file=RodrigoX.iso -d cpu_reset -monitor stdio
```


or use 
```bash
make all
```

to do everything for you.

To build and run RodrigoX with the multiboot bootloader, follow these steps:

1. build the kernel (and it's drivers) and multiboot header with:
```bash
make multiboot
```

```bash
qemu-system-i386 -rtc base=localtime -cdrom RodrigoX.iso
```

