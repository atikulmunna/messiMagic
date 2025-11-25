#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
    #include <windows.h>
    #define CLEAR_SCREEN "cls"
#else
    #include <sys/ioctl.h>
    #define CLEAR_SCREEN "clear"
#endif

// ANSI Color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

// Configuration
typedef struct {
    char character;
    char* color;
    int delay_ms;
    int animate;
} Config;

// Function prototypes
void print_m(Config cfg);
void print_e(Config cfg);
void print_s(Config cfg);
void print_i(Config cfg);
void print_banner();
void print_usage();
void animate_text(const char* text, int delay_ms);
void clear_screen();
void sleep_ms(int milliseconds);
int get_terminal_width();

int main(int argc, char *argv[]) {
    Config cfg = {'*', CYAN, 0, 0};
    
    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage();
            return 0;
        } else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--animate") == 0) {
            cfg.animate = 1;
            cfg.delay_ms = 30;
        } else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--char") == 0) {
            if (i + 1 < argc) {
                cfg.character = argv[++i][0];
            }
        } else if (strcmp(argv[i], "--red") == 0) {
            cfg.color = RED;
        } else if (strcmp(argv[i], "--green") == 0) {
            cfg.color = GREEN;
        } else if (strcmp(argv[i], "--yellow") == 0) {
            cfg.color = YELLOW;
        } else if (strcmp(argv[i], "--blue") == 0) {
            cfg.color = BLUE;
        } else if (strcmp(argv[i], "--magenta") == 0) {
            cfg.color = MAGENTA;
        } else if (strcmp(argv[i], "--rainbow") == 0) {
            cfg.color = "RAINBOW";
        }
    }
    
    if (cfg.animate) {
        clear_screen();
    }
    
    print_banner();
    
    printf("\n%s%s", BOLD, cfg.color);
    
    print_m(cfg);
    if (cfg.animate) sleep_ms(200);
    
    print_e(cfg);
    if (cfg.animate) sleep_ms(200);
    
    print_s(cfg);
    if (cfg.animate) sleep_ms(200);
    
    print_s(cfg);
    if (cfg.animate) sleep_ms(200);
    
    print_i(cfg);
    
    printf("%s\n", RESET);
    
    return 0;
}

void print_banner() {
    printf("%s%s", BOLD, YELLOW);
    printf("╔═══════════════════════════════════════════╗\n");
    printf("║     ASCII ART GENERATOR v2.0              ║\n");
    printf("║     MESSI Pattern Generator               ║\n");
    printf("╚═══════════════════════════════════════════╝\n");
    printf("%s", RESET);
}

void print_usage() {
    printf("Usage: ascii_art [OPTIONS]\n\n");
    printf("Options:\n");
    printf("  -h, --help        Show this help message\n");
    printf("  -a, --animate     Enable animation effect\n");
    printf("  -c, --char CHAR   Use custom character (default: *)\n");
    printf("  --red             Use red color\n");
    printf("  --green           Use green color\n");
    printf("  --yellow          Use yellow color\n");
    printf("  --blue            Use blue color\n");
    printf("  --magenta         Use magenta color\n");
    printf("  --rainbow         Use rainbow colors\n\n");
    printf("Example:\n");
    printf("  ./ascii_art -a --rainbow\n");
    printf("  ./ascii_art -c '#' --green\n");
}

void print_m(Config cfg) {
    const char* colors[] = {RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA};
    int color_idx = 0;
    
    printf("\n\n");
    
    for (int i = 0; i <= 11; i++) {
        if (strcmp(cfg.color, "RAINBOW") == 0) {
            printf("%s", colors[color_idx++ % 6]);
        }
        
        for (int j = 0; j <= 2; j++) {
            printf(j == 0 ? "\t%c" : "%c", cfg.character);
        }
        for (int k = 1; k <= i; k++) {
            printf(" ");
        }
        for (int j = 0; j <= 2; j++) {
            printf("%c", cfg.character);
        }
        for (int m = 10; m >= i; m--) {
            printf("  ");
        }
        for (int j = 0; j <= 2; j++) {
            printf("%c", cfg.character);
        }
        for (int k = 1; k <= i; k++) {
            printf(" ");
        }
        for (int j = 0; j <= 2; j++) {
            printf("%c", cfg.character);
        }
        
        printf("\n");
        if (cfg.animate) {
            fflush(stdout);
            sleep_ms(cfg.delay_ms);
        }
    }
}

void print_e(Config cfg) {
    const char* colors[] = {RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA};
    int color_idx = 0;
    
    printf("\n\n");
    
    for (int i = 0; i <= 11; i++) {
        if (strcmp(cfg.color, "RAINBOW") == 0) {
            printf("%s", colors[color_idx++ % 6]);
        }
        
        for (int j = 1; j <= 8; j++) {
            if ((i >= 0 && i < 2) || (i > 4 && i < 7) || 
                (i >= 2 && i <= 4 && j == 1) || 
                (i > 6 && i <= 9 && j == 1) || 
                (i > 9 && i <= 11)) {
                if (i > 4 && i < 7) {
                    printf("%c%c", cfg.character, cfg.character);
                } else {
                    printf("%c%c%c", cfg.character, cfg.character, cfg.character);
                }
            } else {
                printf("  ");
            }
        }
        printf("\n");
        if (cfg.animate) {
            fflush(stdout);
            sleep_ms(cfg.delay_ms);
        }
    }
}

void print_s(Config cfg) {
    const char* colors[] = {RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA};
    int color_idx = 0;
    
    printf("\n\n");
    
    for (int i = 0; i <= 11; i++) {
        if (strcmp(cfg.color, "RAINBOW") == 0) {
            printf("%s", colors[color_idx++ % 6]);
        }
        
        for (int j = 1; j <= 8; j++) {
            if ((i >= 0 && i < 2) || (i > 4 && i < 7) || 
                (i >= 2 && i <= 4 && j == 1) || 
                (i > 6 && i <= 9 && j == 8) || 
                (i > 9 && i <= 11)) {
                printf("%c%c%c", cfg.character, cfg.character, cfg.character);
            } else {
                printf("   ");
            }
        }
        printf("\n");
        if (cfg.animate) {
            fflush(stdout);
            sleep_ms(cfg.delay_ms);
        }
    }
}

void print_i(Config cfg) {
    const char* colors[] = {RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA};
    int color_idx = 0;
    
    printf("\n\n");
    
    for (int i = 1; i <= 2; i++) {
        if (strcmp(cfg.color, "RAINBOW") == 0) {
            printf("%s", colors[color_idx++ % 6]);
        }
        for (int j = 1; j <= 24; j++) {
            printf("%c", cfg.character);
        }
        printf("\n");
        if (cfg.animate) {
            fflush(stdout);
            sleep_ms(cfg.delay_ms);
        }
    }
    
    for (int i = 1; i <= 12; i++) {
        if (strcmp(cfg.color, "RAINBOW") == 0) {
            printf("%s", colors[color_idx++ % 6]);
        }
        for (int j = 1; j <= 3; j++) {
            printf(j == 1 ? "          %c" : "%c", cfg.character);
        }
        printf("\n");
        if (cfg.animate) {
            fflush(stdout);
            sleep_ms(cfg.delay_ms);
        }
    }
    
    for (int i = 1; i <= 2; i++) {
        if (strcmp(cfg.color, "RAINBOW") == 0) {
            printf("%s", colors[color_idx++ % 6]);
        }
        for (int j = 1; j <= 24; j++) {
            printf("%c", cfg.character);
        }
        printf("\n");
        if (cfg.animate) {
            fflush(stdout);
            sleep_ms(cfg.delay_ms);
        }
    }
}

void clear_screen() {
    system(CLEAR_SCREEN);
}

void sleep_ms(int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

int get_terminal_width() {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
#endif
}
