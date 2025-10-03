// shell.c - Main shell with Matrix effects
#include "shell.h"
#include "keyboard.h"

char *VGA_MEMORY = (char*)0xb8000;

// ==================== CURSOR STRUCT ====================
typedef struct {
    int row;
    int col;
} Cursor;

Cursor cursor = {0, 0};  // Tracks current terminal position

// ==================== UTILITY FUNCTIONS ====================
int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

int strlen(const char* s) {
    int len = 0;
    while (s[len] != '\0') len++;
    return len;
}

void sleep(int ticks) {
    for (volatile int i = 0; i < ticks * 1000000; i++);
}

// ==================== DISPLAY FUNCTIONS ====================
void clear_screen() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT * 2; i += 2) {
        VGA_MEMORY[i] = ' ';
        VGA_MEMORY[i + 1] = GREEN_ON_BLACK;
    }
    cursor.row = 0;
    cursor.col = 0;
}

void scroll_up() {
    for (int i = 0; i < (VGA_HEIGHT - 1) * VGA_WIDTH * 2; i++) {
        VGA_MEMORY[i] = VGA_MEMORY[i + VGA_WIDTH * 2];
    }
    for (int i = (VGA_HEIGHT - 1) * VGA_WIDTH * 2; i < VGA_HEIGHT * VGA_WIDTH * 2; i += 2) {
        VGA_MEMORY[i] = ' ';
        VGA_MEMORY[i + 1] = GREEN_ON_BLACK;
    }
}

void put_char_at_cursor(char c, unsigned char color) {
    if (c == '\n') {
        cursor.col = 0;
        cursor.row++;
        if (cursor.row >= VGA_HEIGHT) {
            scroll_up();
            cursor.row = VGA_HEIGHT - 1;
        }
        return;
    }

    int pos = (cursor.row * VGA_WIDTH + cursor.col) * 2;
    VGA_MEMORY[pos] = c;
    VGA_MEMORY[pos + 1] = color;

    cursor.col++;
    if (cursor.col >= VGA_WIDTH) {
        cursor.col = 0;
        cursor.row++;
        if (cursor.row >= VGA_HEIGHT) {
            scroll_up();
            cursor.row = VGA_HEIGHT - 1;
        }
    }
}

void backspace_cursor(int min_col, int min_row) {
    if (cursor.col > min_col || cursor.row > min_row) {
        if (cursor.col > 0) {
            cursor.col--;
        } else if (cursor.row > 0) {
            cursor.row--;
            cursor.col = VGA_WIDTH - 1;
        }

        int pos = (cursor.row * VGA_WIDTH + cursor.col) * 2;
        VGA_MEMORY[pos] = ' ';
        VGA_MEMORY[pos + 1] = GREEN_ON_BLACK;
    }
}

void print_at_cursor(const char* str, unsigned char color) {
    for (int i = 0; str[i]; i++)
        put_char_at_cursor(str[i], color);
}

void print(const char* str, int row, unsigned char color) {
    cursor.row = row;
    cursor.col = 0;
    print_at_cursor(str, color);
}


// ==================== MATRIX RAIN EFFECT ====================
// still under consideration and development
void matrix_rain() {
    clear_screen();
    
    int col_positions[VGA_WIDTH];
    int col_lengths[VGA_WIDTH];
    
    for (int i = 0; i < VGA_WIDTH; i++) {
        col_positions[i] = -(i % 25);
        col_lengths[i] = 10 + (i % 15);
    }
    
    char matrix_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()<>[]{}";
    int char_count = 82;
    int pseudo_rand = 42;
    
    for (int frame = 0; frame < 500; frame++) {
        for (int col = 0; col < VGA_WIDTH; col++) {
            int pos = col_positions[col];
            
            if (pos >= 0 && pos < VGA_HEIGHT) {
                char c = matrix_chars[pseudo_rand % char_count];
                print_at_cursor(&c, MAKE_COLOR(COLOR_WHITE, COLOR_BLACK));
                
                for (int tail = 1; tail < col_lengths[col]; tail++) {
                    int tail_pos = pos - tail;
                    if (tail_pos >= 0 && tail_pos < VGA_HEIGHT) {
                        char tc = matrix_chars[(pseudo_rand + tail) % char_count];
                        unsigned char tail_color;
                        if (tail < 3) tail_color = MAKE_COLOR(COLOR_LIGHT_GREEN, COLOR_BLACK);
                        else if (tail < 7) tail_color = GREEN_ON_BLACK;
                        else tail_color = MAKE_COLOR(COLOR_DARK_GRAY, COLOR_BLACK);

                        int old_row = cursor.row, old_col = cursor.col;
                        cursor.row = tail_pos; cursor.col = col;
                        put_char_at_cursor(tc, tail_color);
                        cursor.row = old_row; cursor.col = old_col;
                    }
                }

                int clear_pos = pos - col_lengths[col];
                if (clear_pos >= 0 && clear_pos < VGA_HEIGHT) {
                    char space = ' ';
                    int old_row = cursor.row, old_col = cursor.col;
                    cursor.row = clear_pos; cursor.col = col;
                    put_char_at_cursor(space, GREEN_ON_BLACK);
                    cursor.row = old_row; cursor.col = old_col;
                }
            }

            col_positions[col]++;
            if (col_positions[col] - col_lengths[col] > VGA_HEIGHT) {
                col_positions[col] = -(pseudo_rand % 20);
                col_lengths[col] = 8 + (pseudo_rand % 17);
            }

            pseudo_rand = (pseudo_rand * 1103515245 + 12345) & 0x7fffffff;
        }
        
        sleep(1);
    }

    clear_screen();
}

// ==================== SHELL LOOP ====================
void shell_loop() {
    char line[MAX_LINE];
    init_keyboard();
    clear_screen();

    print_at_cursor("========================================\n", CYAN_ON_BLACK);
    print_at_cursor("VERKLEMPT OS v0.0.2\n", CYAN_ON_BLACK);
    print_at_cursor("========================================\n\n", CYAN_ON_BLACK);
    print_at_cursor("Hello stranger, welcome to the crypts of depression\n", CYAN_ON_BLACK);
    print_at_cursor("Type 'help' for available commands\n\n", GREEN_ON_BLACK);

    while (1) {
        // Print prompt
        print_at_cursor("verklemptOS> ", GREEN_ON_BLACK);
        int prompt_col = cursor.col; // Track where user input starts
        int prompt_row = cursor.row;

        int i = 0; // input buffer index

        // Input loop
        while (1) {
            char c = get_key();

            if (c == '\n') {
                line[i] = '\0';
                put_char_at_cursor('\n', GREEN_ON_BLACK);
                break;
            } 
            else if (c == '\b') {
                if (i > 0) {
                    i--;
                    backspace_cursor(prompt_col, prompt_row);
                }
            } 
            else if (i < MAX_LINE - 1 && c >= 32) { // printable characters
                line[i++] = c;
                put_char_at_cursor(c, GREEN_ON_BLACK);
            }
        }

        // Execute the command if not empty
        if (strlen(line) > 0) execute_command(line);
    }
}

    

// ==================== COMMAND EXECUTION ====================
void execute_command(char* cmd) {
    if (strcmp(cmd, "help") == 0) {
        print_at_cursor("Available commands:\n", GREEN_ON_BLACK);
        print_at_cursor("  help     - Display this help message\n", WHITE_ON_BLACK);
        print_at_cursor("  clear    - Clear the screen\n", WHITE_ON_BLACK);
        /*print_at_cursor("  matrix   - Enter the Matrix (falling characters)\n", WHITE_ON_BLACK);*/ //under development
        print_at_cursor("  horror   - Display horror ASCII art\n", WHITE_ON_BLACK);
        print_at_cursor("  about    - About this OS\n", WHITE_ON_BLACK);

    } else if (strcmp(cmd, "clear") == 0) {
        clear_screen();

    } /*else if (strcmp(cmd, "matrix") == 0) {
        matrix_rain();

    }*/ else if (strcmp(cmd, "horror") == 0 || strcmp(cmd, "ascii") == 0) {
        show_ascii();
        print_at_cursor("\n[Press any key to return...]", MAKE_COLOR(COLOR_DARK_GRAY, COLOR_BLACK));
        get_key();
        clear_screen();

    } else if (strcmp(cmd, "about") == 0) {
        print_at_cursor("VERKLEMPT OS - An OS that watches you back\n", RED_ON_BLACK);
        print_at_cursor("Reality is just a simulation running on rust and fear.\n", MAKE_COLOR(COLOR_DARK_GRAY, COLOR_BLACK));
        print_at_cursor("Every keystroke feeds the machine.\n", MAKE_COLOR(COLOR_DARK_GRAY, COLOR_BLACK));
        print_at_cursor("There is no escape.\n", MAKE_COLOR(COLOR_DARK_GRAY, COLOR_BLACK));

    } else {
        print_at_cursor("Unknown command. Type 'help' for available commands.\n", RED_ON_BLACK);
    }
}

