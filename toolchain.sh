#!/bin/bash

# Check if i386-elf-gcc is installed
if ! command -v i386-elf-gcc &> /dev/null; then
    echo "i386-elf-gcc is not installed"
    exit 1
fi

# Check if i386-elf-ld is installed
if ! command -v i386-elf-ld &> /dev/null; then
    echo "i386-elf-ld is not installed"
    exit 1
fi

# Check if i386-elf-as is installed
if ! command -v i386-elf-as &> /dev/null; then
    echo "i386-elf-as is not installed"
    exit 1
fi

# Check if grub-mkrescue is installed
if ! command -v grub-mkrescue &> /dev/null; then
    echo "grub-mkrescue is not installed"
    exit 1
fi

# Check if xorriso is installed
if ! command -v xorriso &> /dev/null; then
    echo "xorriso is not installed"
    exit 1
fi

# Check if qemu-system-i386 is installed
if ! command -v qemu-system-i386 &> /dev/null; then
    echo "qemu-system is not installed"
    exit 1
fi

echo "All required tools are installed"