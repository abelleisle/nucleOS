#ifndef _PERIPHERIAL_IO_
#define _PERIPHERIAL_IO_

unsigned char intb(unsigned short port);
void outb(unsigned short port, unsigned char data);

//#define _inline inline __attribute__((always_inline))
//
//static _inline unsigned char inb(unsigned short port)
//{
//    unsigned char rv;
//    asm volatile ("inb %1, %0" : "=a" (rv) : "dN" (port));
//    return rv;
//}
//
//static _inline void outb(unsigned short port, unsigned char data)
//{
//    asm volatile ("outb %1, %0" : : "dN" (port), "a" (data));
//}

#endif /* ifndef _PERIPHERIAL_IO_ */
