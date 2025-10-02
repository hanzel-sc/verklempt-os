ENTRY(start)
SECTIONS
{
    . = 1M;    /* load at 1MB */

    .text : {
        *(.text)
    }
    .rodata : {
        *(.rodata)
    }
    .data : {
        *(.data)
    }
    .bss : {
        *(.bss)
    }
}

