; boot.asm - verklemptOS Multiboot bootloader
bits 32
section .text
align 4
    dd 0x1BADB002              ; Multiboot unique number
    dd 0x0                     ; Flags
    dd -(0x1BADB002 + 0x0)     ; Checksum

global start
extern kernel_main

start:
    cli                         ; Clear interrupts
    mov esp, stack_space        ; Set up stack pointer
    call kernel_main            ; Jump to kernel
.hang:
    hlt                         ; Halt CPU
    jmp .hang                   ; Infinite loop

section .bss
resb 8192                       ; 8KB stack space
stack_space:
