#include <stdio.h>


void PrintResult(int res)
{
    printf("Result: %d\n", res);
}


int Calculation(int a, int b)

{
    if(a > b)
        return a - b;
    else
        return b - a;
}

int main()
{   
    int a = 5;
    int b = 4;
    int c;
    
    c = Calculation(a,b);

    PrintResult(c);

    return 0;
}