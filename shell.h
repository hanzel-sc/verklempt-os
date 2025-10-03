// shell.h - Shell and display header
#ifndef SHELL_H
#define SHELL_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define MAX_LINE 128

// VGA Color definitions
#define COLOR_BLACK         0x0
#define COLOR_BLUE          0x1
#define COLOR_GREEN         0x2
#define COLOR_CYAN          0x3
#define COLOR_RED           0x4
#define COLOR_MAGENTA       0x5
#define COLOR_BROWN         0x6
#define COLOR_LIGHT_GRAY    0x7
#define COLOR_DARK_GRAY     0x8
#define COLOR_LIGHT_BLUE    0x9
#define COLOR_LIGHT_GREEN   0xA
#define COLOR_LIGHT_CYAN    0xB
#define COLOR_LIGHT_RED     0xC
#define COLOR_LIGHT_MAGENTA 0xD
#define COLOR_YELLOW        0xE
#define COLOR_WHITE         0xF

#define MAKE_COLOR(fg, bg) ((bg << 4) | fg)
#define GREEN_ON_BLACK MAKE_COLOR(COLOR_GREEN, COLOR_BLACK)
#define RED_ON_BLACK MAKE_COLOR(COLOR_RED, COLOR_BLACK)
#define CYAN_ON_BLACK MAKE_COLOR(COLOR_CYAN, COLOR_BLACK)
#define WHITE_ON_BLACK MAKE_COLOR(COLOR_LIGHT_GRAY, COLOR_BLACK)

// Shell functions
void shell_loop();
void execute_command(char* cmd);

// Display functions
void print(const char* str, int row, unsigned char color);
void print_at(const char* str, int x, int y, unsigned char color);
void clear_screen();
void scroll_up();

// Utility functions
int strcmp(const char* s1, const char* s2);
int strlen(const char* s);
void sleep(int ticks);

// Special effects
void show_ascii();
void matrix_rain();

#endif
