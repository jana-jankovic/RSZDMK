#include <stdio.h>

int main()
{
    int a = 3;
    int b = 8;
    int c;
	
    if(a > b)
        c = a - b;
    else
        c = b - a;

    printf("Result: %d\n", c);

    return 0;
}