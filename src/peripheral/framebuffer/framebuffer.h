#ifndef _PERIPHERIAL_FRAMEBUFFER_
#define _PERIPHERIAL_FRAMEBUFFER_

typedef enum {
    FB_COLOR_BLACK = 0x0,
    FB_COLOR_BLUE,
    FB_COLOR_GREEN,
    FB_COLOR_CYAN,
    FB_COLOR_RED,
    FB_COLOR_MAGENTA,
    FB_COLOR_BROWN,
    FB_COLOR_LIGHTGREY,
    FB_COLOR_DARKGREY,
    FB_COLOR_LIGHTBLUE,
    FB_COLOR_LIGHTGREEN,
    FB_COLOR_LIGHTCYAN,
    FB_COLOR_LIGHTRED,
    FB_COLOR_LIGHTMAGENTA,
    FB_COLOR_YELLOW,
    FB_COLOR_WHITE
} FB_COLOR_t;

void Framebuffer_SetColor(FB_COLOR_t fg, FB_COLOR_t bg);

void Framebuffer_MoveCursor(unsigned short x, unsigned short y);
void Framebuffer_UpdateCursor(void);

void Framebuffer_PutChar(unsigned char c);
/*
 * @warning MUST BE NULL TERMINATED STRING
 */
void Framebuffer_PutString(const char *str);

void Framebuffer_PutInt(int Number);

/*
 * MODE    RESOLUTION  BITS PER PIXEL  MAXIMUM COLORS
 * 0x0100  640x480     4               16
 * 0x0101  640x480     8               256
 * 0x0102  800x600     4               16
 * 0x0103  800x600     8               256
 * 0x010D  320x200     15              32k
 * 0x010E  320x200     16              64k
 * 0x010F  320x200     24/32*          16m
 * 0x0110  640x480     15              32k
 * 0x0111  640x480     16              64k
 * 0x0112  640x480     24/32*          16m
 * 0x0113  800x600     15              32k
 * 0x0114  800x600     16              64k
 * 0x0115  800x600     24/32*          16m
 * 0x0116  1024x768    15              32k
 * 0x0117  1024x768    16              64k
 * 0x0118  1024x768    24/32*          16m
 */

#endif /* ifndef _PERIPHERIAL_FRAMEBUFFER_ */
