#ifndef COLORS_H
#define COLORS_H

// ================= RESET =================
#define RESET          "\033[0m"

// ================= STYLES =================
#define BOLD           "\033[1m"
#define DIM            "\033[2m"
#define ITALIC         "\033[3m"
#define UNDERLINE      "\033[4m"
#define BLINK          "\033[5m"
#define REVERSE        "\033[7m"
#define HIDDEN         "\033[8m"
#define STRIKETHROUGH  "\033[9m"

// ================= COULEURS (FOREGROUND) =================
// Standard
#define BLACK          "\033[30m"
#define RED            "\033[31m"
#define GREEN          "\033[32m"
#define YELLOW         "\033[33m"
#define BLUE           "\033[34m"
#define MAGENTA        "\033[35m"
#define CYAN           "\033[36m"
#define WHITE          "\033[37m"

// Bright
#define BRIGHT_BLACK   "\033[90m"
#define BRIGHT_RED     "\033[91m"
#define BRIGHT_GREEN   "\033[92m"
#define BRIGHT_YELLOW  "\033[93m"
#define BRIGHT_BLUE    "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN    "\033[96m"
#define BRIGHT_WHITE   "\033[97m"

// ================= BACKGROUND =================
// Standard
#define BG_BLACK       "\033[40m"
#define BG_RED         "\033[41m"
#define BG_GREEN       "\033[42m"
#define BG_YELLOW      "\033[43m"
#define BG_BLUE        "\033[44m"
#define BG_MAGENTA     "\033[45m"
#define BG_CYAN        "\033[46m"
#define BG_WHITE       "\033[47m"

// Bright
#define BG_BRIGHT_BLACK   "\033[100m"
#define BG_BRIGHT_RED     "\033[101m"
#define BG_BRIGHT_GREEN   "\033[102m"
#define BG_BRIGHT_YELLOW  "\033[103m"
#define BG_BRIGHT_BLUE    "\033[104m"
#define BG_BRIGHT_MAGENTA "\033[105m"
#define BG_BRIGHT_CYAN    "\033[106m"
#define BG_BRIGHT_WHITE   "\033[107m"

// ================= 256 COLORS =================
// Usage: printf(COLOR256(196) "Hello" RESET);
#define COLOR256(n)   "\033[38;5;" #n "m"
#define BG_COLOR256(n) "\033[48;5;" #n "m"

// ================= TRUE COLOR (RGB) =================
// Usage: printf(RGB(255,0,0) "Hello" RESET);
#define RGB(r,g,b)     "\033[38;2;" #r ";" #g ";" #b "m"
#define BG_RGB(r,g,b)  "\033[48;2;" #r ";" #g ";" #b "m"

void colors_init(void);

#endif
