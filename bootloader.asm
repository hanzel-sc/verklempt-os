; boot.asm - VerklemptOS
bits 32
section .text

; Multiboot header
align 4
  dd 0x1BADB002		; unique number
  dd 0x0		; flags (none)
  dd -(0x1BADB002 + 0x0); checksum (unique + flags + checksum = 0)

global start
extern kernel_main ; defined in kernel.c

start:
	cli 	; disable interrupts
	call kernel_main ; jump to C kernel

.hang
	hlt	; halt CPU if Kernel returns
	jmp .hang

