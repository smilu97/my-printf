#include <stdio.h>
#include <stdarg.h>

int read_int(va_list ap) {
    return va_arg(ap, int);
}

void fn(int n, ...)
{
    int a, b, c;
    va_list ap;
    va_start(ap, n);
    a = read_int(ap);
    b = read_int(ap);
    c = read_int(ap);
    va_end(ap);
    printf("(%d, %d, %d)\n", a, b, c);
}

int main()
{
    fn(3, 1, 2, 3);
    printf("%.2s", "asd");
}