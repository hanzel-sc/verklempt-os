// kernel.c — VerklemptOS kernel
#define CYAN_ON_BLACK 0x03
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

char *VGA_MEMORY = (char*)0xb8000;

void clear_screen() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT * 2; i += 2) {
        VGA_MEMORY[i] = ' ';
        VGA_MEMORY[i+1] = CYAN_ON_BLACK;
    }
}

void print(const char *str, int row) {
    int i = 0;
    int pos = row * VGA_WIDTH * 2;
    while (str[i] != '\0') {
        VGA_MEMORY[pos] = str[i];
        VGA_MEMORY[pos+1] = CYAN_ON_BLACK;
        i++;
        pos += 2;
    }
}

void kernel_main() {
    clear_screen();
    print("VerklemptOS v0.0.1", 0);
    print("Hello, wanderer. Welcome to the crypts of depression...", 2);
    while (1) {} 
}

