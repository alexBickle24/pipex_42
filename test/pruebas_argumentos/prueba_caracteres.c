

#include <stdio.h>

int main(int argz, char **argv)
{
    if (argz == 2)
    {
        printf("%s", argv[1]);
        return (0);
    }
}