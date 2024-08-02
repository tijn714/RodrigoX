# RodrigoX OS 
A hobby operating system for x86 Intel machines.

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

## Planned Features
- File System (FS): Implement a file system for storing and retrieving data
- User Space: Create a user-friendly interface and separate user space from kernel space
- Security: Implement security measures to protect the OS and user data


## Building and Running

To build and run RodrigoX, follow these steps:

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
qemu-system-i386 -drive format=raw,file=RodrigoX.iso -d cpu_reset -monitor stdio
```
