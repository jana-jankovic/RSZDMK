#include <stdio.h>

int main()
{
    int a = 5;
    int b = 4;
    int c;
	
    if(a > b)
        c = a - b;
    else
        c = b - a;

    printf("Result: %d\n", c);

    return 0;
}