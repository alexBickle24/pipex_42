

#include <stdio.h>
#include <unistd.h>

size_t	ft_strlen(const char *s)
{
	size_t	n;

	n = 0;
	while (*s)
	{
		n++;
		s++;
	}
	return (n);
}

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;

	if (!*to_find)
		return ((char *)str);
	i = 0;
	while (str[i] && i < n)
	{
		j = 0;
		while (str[i + j] == to_find[j] && i + j < n)
		{
			if (!to_find[j + 1])
				return ((char *)str + i);
			j++;
		}
		i++;
	}
	return (0);
}

int main(int argz, char **argv)
{
    const char *cadena = "Here\\_doc  ";
    char *comp;

	if (argz < 2)
	{
		printf("error\n");
		return(1);
	}
	printf("hola\n");
    comp = ft_strnstr(cadena, argv[1], 9);
    printf("el valor de comp es: %s\n", comp);
    return(0);
}