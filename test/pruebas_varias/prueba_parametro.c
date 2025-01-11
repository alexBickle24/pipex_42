

#include <stdio.h>

int funcion(int a)
{
    a = 2;
    return(a);
}

int main(void)
{
    int a;

    a = funcion(a);
    printf("el valor de a es %d", a);
    return(0);
}
