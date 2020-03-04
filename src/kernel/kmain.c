#include <peripheral/framebuffer/framebuffer.h>

char *opener =
"                  _       ___  ____        \n"
" _ __  _   _  ___| | ___ / _ \\/ ___|      \n"
"| '_ \\| | | |/ __| |/ _ \\ | | \\___ \\   \n"
"| | | | |_| | (__| |  __/ |_| |___) |      \n"
"|_| |_|\\__,_|\\___|_|\\___|\\___/|____/   \n";

int kmain(void)
{
    Framebuffer_SetColor(FB_COLOR_RED, FB_COLOR_BLACK);
    Framebuffer_PutChar('\n');
    Framebuffer_PutString(opener);
    return 0;
}
