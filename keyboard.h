// keyboard.h - Keyboard driver header
#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KB_DATA_PORT    0x60
#define KB_STATUS_PORT  0x64
#define BACKSPACE       0x0E
#define ENTER           0x1C
#define LSHIFT          0x2A
#define RSHIFT          0x36
#define LSHIFT_REL      0xAA
#define RSHIFT_REL      0xB6

typedef struct {
    unsigned char shift_pressed;
    unsigned char ctrl_pressed;
    unsigned char alt_pressed;
} KeyboardState;

extern KeyboardState kb_state;

// Core keyboard functions
unsigned char inb(unsigned short port);
void outb(unsigned short port, unsigned char data);
char get_key();
void read_line(char* buffer, int max_len);
void init_keyboard();

#endif

