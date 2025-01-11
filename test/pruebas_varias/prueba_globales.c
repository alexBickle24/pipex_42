

#include <stdio.h>
#include <string.h>

int numero;
char *cadena;
#define digito 3


void nuevo_numero(void)
{
    int     a;

    a = 3;
    numero = a;
    printf("el valor de la funcion suma es, %d\n", numero);
}
int numero2(void)
{
    int a;
    char aux_cadena[5];
    
    strlcpy(aux_cadena, "hola", 5);
    cadena = aux_cadena;
    a = 4;
    numero = numero + a;
    printf("el valor del numero  dentro de la funcion 2 es, %d\n", numero);
    return(numero);
}

int main(void)
{
    int num;

    nuevo_numero();
    printf("el valor del nuevo numero es %d\n", numero);
    num = numero2();
    printf("el valor del nuevo numero en el momento2 es %d\n", num);
    printf("el valor de la cadena es %s\n", cadena);
    return(0);
}