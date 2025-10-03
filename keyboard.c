// keyboard.c - Enhanced keyboard driver with shift support
#include "keyboard.h"

KeyboardState kb_state = {0, 0, 0};

// US QWERTY scancode map (lowercase)
static char scancode_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ',
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    '-', 0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// Shift map (uppercase/symbols)
static char scancode_map_shift[128] = {
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', 0,
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0, '|',
    'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' ',
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    '-', 0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

unsigned char inb(unsigned short port) {
    unsigned char result;
    __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

void outb(unsigned short port, unsigned char data) {
    __asm__ volatile ("outb %0, %1" : : "a"(data), "Nd"(port));
}

void init_keyboard() {
    kb_state.shift_pressed = 0;
    kb_state.ctrl_pressed = 0;
    kb_state.alt_pressed = 0;
}

char get_key() {
    unsigned char scancode;
    
    while (1) {
        // Check if data is available
        if (inb(KB_STATUS_PORT) & 0x01) {
            scancode = inb(KB_DATA_PORT);
            
            // Handle shift keys
            if (scancode == LSHIFT || scancode == RSHIFT) {
                kb_state.shift_pressed = 1;
                continue;
            }
            if (scancode == LSHIFT_REL || scancode == RSHIFT_REL) {
                kb_state.shift_pressed = 0;
                continue;
            }
            
            // Only process key press (not release)
            if (scancode < 128) {
                char c = kb_state.shift_pressed ? 
                         scancode_map_shift[scancode] : 
                         scancode_map[scancode];
                if (c != 0) return c;
            }
        }
    }
}

void read_line(char* buffer, int max_len) {
    int i = 0;
    char c;
    
    while (1) {
        c = get_key();
        
        if (c == '\n') {
            buffer[i] = '\0';
            return;
        } else if (c == '\b') {
            if (i > 0) {
                i--;
            }
        } else if (i < max_len - 1) {
            buffer[i++] = c;
        }
    }
}
