#include <peripheral/framebuffer/framebuffer.h>
#include <arch/i686/gdt.h>
#include <arch/i686/idt.h>

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
                 0x5f,0x2f,0x7c,0x5f,0x5f,0x5f,0x5f,0x2f,0x20,0x00};

void findPrimes(int num);

int kmain(void)
{
    GDT_Setup();
    IDT_Setup();

    Framebuffer_SetColor(FB_COLOR_YELLOW, FB_COLOR_BLACK);
    Framebuffer_PutChar('\n');
    Framebuffer_PutString(opener);
    Framebuffer_PutString("\n\n");

    findPrimes(25);

    asm volatile("int $0x3");
    asm volatile("int $0x4");

    while (1);
}

int isPrime(int num)
{
    int flag = 0;
    for (int i = 2; i < num / 2; ++i) {
        if (num % i == 0) {
            flag = 1;
            break;
        }
    }
    if (!flag)
        return 1;
    else
        return 0;
}

void findPrimes(int num)
{
    Framebuffer_SetColor(FB_COLOR_GREEN, FB_COLOR_BLACK);
    Framebuffer_PutString("Finding prime numbers from 0-");
    Framebuffer_PutInt(num);
    Framebuffer_PutChar('\n');
    Framebuffer_SetColor(FB_COLOR_CYAN, FB_COLOR_BLACK);
    for (int n = 2; n < num; n++) {
        if (isPrime(n)) {
            Framebuffer_PutInt(n);
            Framebuffer_PutString(": is prime!\n");
        }
    }
}
