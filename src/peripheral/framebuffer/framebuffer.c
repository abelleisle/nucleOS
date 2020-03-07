#include "framebuffer.h"

#include <peripheral/io.h>

#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT    0x3D5

#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND  15

static char *fb = (char *)(0x000B8000);

unsigned short screenWidth = 80;
unsigned short csr_x = 0, csr_y = 0;
unsigned char fb_attrib = 0x0F;

static unsigned short framebuffer_ToOffset(unsigned short x, unsigned short y)
{
    return ((y * screenWidth) + x) * 2;
}

static void framebuffer_WriteCell(char c)
{
    char *where;
    where = fb + framebuffer_ToOffset(csr_x, csr_y);
    *where = c;
    *(where+1) = fb_attrib;
}

void Framebuffer_SetColor(FB_COLOR_t fg, FB_COLOR_t bg)
{
    fb_attrib = (bg << 4) | (fg & 0x0F);
}

void Framebuffer_MoveCursor(unsigned short x, unsigned short y)
{
    unsigned short temp = framebuffer_ToOffset(x, y);

    csr_x = x;
    csr_y = y;

    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, ((temp >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, temp & 0x00FF);
}

void Framebuffer_UpdateCursor(void)
{
    Framebuffer_MoveCursor(csr_x, csr_y);
}

void Framebuffer_PutChar(unsigned char c)
{
    if (c == 0x08) {
    /* Backspace */
        if (csr_x != 0) csr_x--;
    } else if (c == 0x09) {
    /* Handle tab, but incrementing by 4 and aligning to nearest 4 */
        csr_x = (csr_x + 4) & ~(4 - 1);
    } else if (c == '\r') {
    /* Handles carriage return by returning cursor to beginning of line */
        csr_x = 0;
    } else if (c == '\n') {
    /* Handles new line by going down a line and returning to the beginning */
        csr_x = 0;
        csr_y++;
    } else if (c >= ' ') {
    /* All characters greater than or equal to space are printable */
        framebuffer_WriteCell(c);
        csr_x++;
    }

    /* If we go over the edge of the screen return to the next line */
    if (csr_x >= 80) {
        csr_x = 0;
        csr_y++;
    }

    Framebuffer_UpdateCursor();
}

void Framebuffer_PutString(char *str)
{
    for (char *s = str; *s != '\0'; s++)
    {
        Framebuffer_PutChar(*s);
    }
}
