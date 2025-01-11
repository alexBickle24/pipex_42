
#include "libft.h"

int main(void)
{
    int cadena[3] = {2, 3, 16};
    char *numero;
    unsigned int len;
    int cuenta;

    cuenta = &cadena[2] - &cadena[0];
    numero = ft_itoa(cuenta);
    len = ft_strlen(numero);
    write(1, numero, len);
}