# Strcolor
strcolor.h defines several constants for ANSI coloring and a singular function.

# Constants
- FG_BLACK, "\e[30m"
- FG_RED, "\e[0;31m"
- FG_GREEN, "\e[32m"
- FG_YELLOW, "\e[33m"
- FG_BLUE, "\e[34m"
- FG_MAGENTA, "\e[35m"
- FG_CYAN, "\e[36m"
- FG_WHITE, "\e[37m"
- BG_BLACK, "\e[40m"
- BG_RED, "\e[41m"
- BG_GREEN, "\e[42m"
- BG_YELLOW, "\e[43m"
- BG_BLUE, "\e[44m"
- BG_MAGENTA, "\e[45m"
- BG_CYAN, "\e[46m"
- BG_WHITE, "\e[47m"
- COLOR_RESET, "\e[0m"


# Functions
- ```void StrPrintColored(char *text, char *fg, char *bg)```:
	
	Prints out the string ```text``` with the foreground and background color being set by ```fg``` and ```bg``` resepectivly.
