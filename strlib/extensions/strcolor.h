#ifndef STRCOLOR_H
#define STRCOLOR_H

// Dependencies

#include <stdio.h>          // printf

// Constants (Foreground, Regular)
#define FG_BLACK "\e[30m"
#define FG_RED "\e[0;31m"
#define FG_GREEN "\e[32m"
#define FG_YELLOW "\e[33m"
#define FG_BLUE "\e[34m"
#define FG_MAGENTA "\e[35m"
#define FG_CYAN "\e[36m"
#define FG_WHITE "\e[37m"

// Constants (Background, Regular)
#define BG_BLACK "\e[40m"
#define BG_RED "\e[41m"
#define BG_GREEN "\e[42m"
#define BG_YELLOW "\e[43m"
#define BG_BLUE "\e[44m"
#define BG_MAGENTA "\e[45m"
#define BG_CYAN "\e[46m"
#define BG_WHITE "\e[47m"

// Other Constants
#define COLOR_RESET "\e[0m"


// Function Prototypes
// Total amount of functions in strcolor.h: 1 (1 defined)
void PrintColored(char *text, char *fg, char *bg);


// Functions

void PrintColored(char *text, char *fg, char *bg){
    printf("%s", fg);
    printf("%s", bg);
    printf("%s", text);
    printf(COLOR_RESET);
}

#endif
