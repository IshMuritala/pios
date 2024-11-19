
#include <stddef.h>

/*strncmp */
int strncmp(const char *s1, const char *s2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0') {
            return (unsigned char)s1[i] - (unsigned char)s2[i];
        }
    }
    return 0;
}

/* memcpy */
void *memcpy(void *dest, const void *src, size_t n) {
    unsigned char *d = dest;
    const unsigned char *s = src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}

/* toupper */
int toupper(int c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 'A';
    }
    return c;
}

/* delay */
void delay() {
    for (volatile int i = 0; i < 100000; i++);
}

/* printf */
void printf(const char *str) {
    while (*str) {
        uart_putc(*str++);
    }
}

/*printk alias for printf */
void printk(const char *str) {
    printf(str);
}
