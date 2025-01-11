

#include <stdio.h>
#include <stdlib.h>

 static unsigned int	ft_count_words(const char *s, int c);
 size_t	ft_strlen(const char *s);


void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	ptr = (char *)malloc((size * nmemb));
	if (!(ptr))
		return (NULL);
	while (i < (nmemb * size))
	{
		*(char *)(ptr + i) = 0;
		i++;
	}
	return (ptr);
}

char	*ft_strdup(const char *s)
{
	size_t		i;
	size_t		num_values;
	char		*ptr;

	num_values = ft_strlen(s);
	i = 0;
	ptr = (char *)malloc((num_values + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (i <= num_values)
	{
		ptr[i] = s[i];
		i++;
	}
	return (ptr);
}

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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	size_t			i;

	i = 0;
	if (!s)
		return (0);
	if ((size_t)start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		ptr = (char *)malloc(ft_strlen(s + start) + 1);
	else
		ptr = (char *)malloc(len + 1);
	if (!(ptr))
		return (0);
	while (i < (len) && s[start] != '\0')
	{
		ptr[i] = s[start];
		start++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static size_t	*ft_counter_begin(const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	*aux_b;

	i = 0;
	j = 0;
	aux_b = malloc((ft_count_words(s, c)) * sizeof(size_t));
	if (!aux_b)
		return (NULL);
	while (s[i] != '\0')
	{
		if ((i == 0 && s[i] != c) || (i >= 1 && (s[i] != c && s[i - 1] == c)))
		{
			aux_b[j] = i;
			j++;
		}
		i++;
	}
	return (aux_b);
}

static size_t	*ft_counter_end(const char *s, char c)
{
	size_t	i;
	size_t	t;
	size_t	*aux_e;

	i = 0;
	t = 0;
	aux_e = malloc((ft_count_words(s, c)) * sizeof(size_t));
	if (!aux_e)
		return (NULL);
	while (s[i] != '\0')
	{
		if ((s[i] != c && s[i + 1] == s[ft_strlen(s)])
			|| ((s[i] != c && s[i + 1] == c)))
		{
			aux_e[t] = i;
			t++;
		}
		i++;
	}
	return (aux_e);
}

static unsigned int	ft_count_words(const char *s, int c)
{
	unsigned int	count_words;
	int				i;

	i = 0;
	count_words = 0;
	while (s[i])
	{
		if ((i == 0 && s[i] != c) || (i >= 1 && (s[i] != c && s[i - 1] == c)))
			count_words++;
		i++;
	}
	return (count_words);
}

static void	*ft_free(char **ptr, int i, size_t *aux_b, size_t *aux_e)
{
	while (i >= 0)
	{
		free(*(ptr + i));
		i--;
	}
	free(aux_b);
	free(aux_e);
	free(ptr);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**ptr;
	size_t	*aux_b;
	size_t	*aux_e;
	size_t	n;

	if (!s)
		return (NULL);
	aux_b = ft_counter_begin(s, c);
	if (!aux_b)
		return (NULL);
	aux_e = ft_counter_end(s, c);
	if (!aux_e)
		return (free(aux_b), NULL);
	ptr = (char **)ft_calloc((ft_count_words(s, c) + 1), sizeof(char *));
	if (!ptr)
		return (free(aux_b), free(aux_e), NULL);
	n = -1;
	while (++n < ft_count_words(s, c))
	{
		*(ptr + n) = ft_substr(s, aux_b[n], (aux_e[n] - aux_b[n] + 1));
		if (!*(ptr + n))
			return (ft_free(ptr, n, aux_b, aux_e));
	}
	return (free(aux_b), free(aux_e), ptr);
}


int main(void)
{
    char **split;

    split = ft_split("hola", ' ');
    printf("%s", split[0]);
    return(0);
}