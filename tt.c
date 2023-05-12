#include <stdio.h>
#include <limits.h>

int main()
{
    unsigned long long a = 18446744073709551615;
    int b;
    b = (unsigned char )a;
 
    printf("%lld\n", a);
}