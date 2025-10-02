#!/bin/bash
set -e

# Create build folder
mkdir -p build

echo "[*] Assembling bootloader.asm..."
nasm -f elf32 bootloader.asm -o build/boot.o

echo "[*] Compiling kernel.c..."
gcc -m32 -ffreestanding -c kernel.c -o build/kernel.o

echo "[*] Linking kernel..."
ld -m elf_i386 -T linker.ld -o build/verklempt.bin build/boot.o build/kernel.o

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

