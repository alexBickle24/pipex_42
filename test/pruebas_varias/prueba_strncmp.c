


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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((const unsigned char) s1[i] - (const unsigned char) s2[i]);
		i++;
	}
	return (0);
}

int main(int argz, char **argv)
{
    const char *cadena = "Here\\_doc";
    int result;
    size_t  len;

	if (argz < 2)
	{
		printf("error\n");
		return(1);
	}
	printf("hola\n");
    len = ft_strlen(argv[1]);
    result = ft_strncmp(cadena, argv[1], len);
    printf("el valor de result es: %d\n", result);
    return(0);
}