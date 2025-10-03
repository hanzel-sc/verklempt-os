#!/bin/bash
set -e

# Create build folder
mkdir -p build

echo "[*] Assembling boot.asm..."
nasm -f elf32 boot.asm -o build/boot.o

echo "[*] Compiling kernel.c..."
gcc -m32 -ffreestanding -c kernel.c -o build/kernel.o
gcc -m32 -ffreestanding -c shell.c -o build/shell.o
gcc -m32 -ffreestanding -c keyboard.c -o build/keyboard.o
gcc -m32 -ffreestanding -c ascii.c -o build/ascii.o

echo "[*] Linking kernel..."
ld -m elf_i386 -T linker.ld -o build/verklempt.bin build/boot.o build/kernel.o build/shell.o build/keyboard.o build/ascii.o

echo "[*] Creating ISO for VirtualBox..."
mkdir -p build/isodir/boot/grub
cp build/verklempt.bin build/isodir/boot/verklempt.bin

cat > build/isodir/boot/grub/grub.cfg << EOF
menuentry "VerklemptOS" {
    multiboot /boot/verklempt.bin
}
EOF

grub-mkrescue -o build/verklempt.iso build/isodir

echo "[*] ISO built: build/verklempt.iso"
echo "[*] Launching QEMU for testing..."

# Launch QEMU immediately for fast testing
qemu-system-i386 -kernel build/verklempt.bin -serial stdio

