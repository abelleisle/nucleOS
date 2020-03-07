#include <peripheral/framebuffer/framebuffer.h>

/**
 * Easter egg?
 */
char opener[] = {0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
                 0x20,0x20,0x20,0x20,0x20,0x20,0x5f,0x20,0x20,0x20,0x20,0x20,
                 0x20,0x20,0x5f,0x5f,0x5f,0x20,0x20,0x5f,0x5f,0x5f,0x5f,0x20,
                 0x20,0x0a,0x20,0x5f,0x20,0x5f,0x5f,0x20,0x20,0x5f,0x20,0x20,
                 0x20,0x5f,0x20,0x20,0x5f,0x5f,0x5f,0x7c,0x20,0x7c,0x20,0x5f,
                 0x5f,0x5f,0x20,0x2f,0x20,0x5f,0x20,0x5c,0x2f,0x20,0x5f,0x5f,
                 0x5f,0x7c,0x20,0x0a,0x7c,0x20,0x27,0x5f,0x20,0x5c,0x7c,0x20,
                 0x7c,0x20,0x7c,0x20,0x7c,0x2f,0x20,0x5f,0x5f,0x7c,0x20,0x7c,
                 0x2f,0x20,0x5f,0x20,0x5c,0x20,0x7c,0x20,0x7c,0x20,0x5c,0x5f,
                 0x5f,0x5f,0x20,0x5c,0x20,0x0a,0x7c,0x20,0x7c,0x20,0x7c,0x20,
                 0x7c,0x20,0x7c,0x5f,0x7c,0x20,0x7c,0x20,0x28,0x5f,0x5f,0x7c,
                 0x20,0x7c,0x20,0x20,0x5f,0x5f,0x2f,0x20,0x7c,0x5f,0x7c,0x20,
                 0x7c,0x5f,0x5f,0x5f,0x29,0x20,0x7c,0x0a,0x7c,0x5f,0x7c,0x20,
                 0x7c,0x5f,0x7c,0x5c,0x5f,0x5f,0x2c,0x5f,0x7c,0x5c,0x5f,0x5f,
                 0x5f,0x7c,0x5f,0x7c,0x5c,0x5f,0x5f,0x5f,0x7c,0x5c,0x5f,0x5f,
                 0x5f,0x2f,0x7c,0x5f,0x5f,0x5f,0x5f,0x2f,0x20};

int kmain(void)
{
    Framebuffer_SetColor(FB_COLOR_YELLOW, FB_COLOR_BLACK);
    Framebuffer_PutChar('\n');
    Framebuffer_PutString(opener);
    return 0;
}