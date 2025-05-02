/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:39:57 by alex              #+#    #+#             */
/*   Updated: 2025/03/22 15:02:09 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

//esta funcion la podemos utiizar. A partir de la zona marcada emieza el heredoc. Falta hacer pruebas del heredoc
//en general a ver si fucnion como el de la minishell y saber si se puede ejecutar de mas maneras para el parseo, por ejemp
//despues de un pipe.
char	*parse_prompt(char **arg, int argz, int *control, char **env)
{
	static char		*l;
	char			*src_name;
	int				fd_inter;

	if (!(ft_strnstr(arg[1], "here_doc", 8) && ft_strlen(arg[1]) == 8))
	{
		src_name = ft_strdup(arg[1]);
		return (src_name);
	}
	//a partr de aqui es
	*control = 4;
	src_name = new_file_name("/tmp/");
	fd_inter = open(src_name, O_CREAT | O_TRUNC | O_APPEND | O_RDWR, 0664);
	if (fd_inter < 0 || argz < 6)
		return (free(src_name), NULL);
	write(1, ">", 1);
	l = get_next_line(0);
	while (ft_strncmp(l, arg[2], ft_strlen(arg[2])) != 0
		|| (ft_strlen(l) - 1) != ft_strlen(arg[2]))
	{
		write_line_in_heredoc(l, fd_inter, env);
		free(l);
		write(1, ">", 1);
		l = get_next_line(0);
	}
	return (free(l), close (fd_inter), src_name);
}
//esta funcion contempla todos los posibles casos del parseo del heredoc. Expanddir variables de entorno,escribir el
/7smbolo del dollar, o escribir cuaquier otro tipo de caracter. No ejecuta comandos porque no se exige en Minishell.
//hay qye comprbar si se ha salado algun caso.
void	write_line_in_heredoc(char *line, int fd_inter, char **env)
{
	unsigned int	i;

	if (!line)
		return ;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$')
		{
			if ((line[i + 1] != '(' && line[i + 1] != ' '
					&& line[i + 1] != '\n' && line[i + 1] != '$'))
			{
				i = write_env(&line[i], fd_inter, i, env);
			}
			else
				ft_putchar_fd(line[i], fd_inter);
		}
		else
			ft_putchar_fd(line[i], fd_inter);
		i++;
	}
}

char	*trim_line(char *line)
{
	int		i;

	i = 0;
	while (line[i] != ')')
		i++;
	line = ft_substr(line, 2, i - 2);
	if (!line)
		return (NULL);
	return (line);
}
//esta fucion se puede reultilizar. Maneja el caso en el que nos encntramos un carcter de $ dentro del heredoc
//hay varias opciones del fucnionmiento ero tengo que revisar si me salte alguna excepccion. por tra parte se podria
//reutiliza en arte para expandir tambien fuera del heredoc.
unsigned int	write_env(char *line, int fd, unsigned int count, char **env)
{
	char		*env_value;
	char		*env_name;
	int			i;

	i = 0;
	while (line[i] != ' ' && line[i] != '\n')
		i++;
	count = count + i;
	env_name = ft_substr((const char *)line, 1, i -1);
	if (!env_name)
		return (0);

	env_value = get_env_value(env_name, env);
	if (!env_value)
	{
		free(env_name);
		return (count - 1);
	}
	ft_putstr_fd(env_value, fd);
	return (free(env_name), count - 1);
}
//esta funoin sirve para poder crear un archivo en una carpeta, asegurando que le archivo no existiesse antees.
//El nombre del archivo es un numero que va aumentando. Con esto se controla la correlacion entre rpogramas cuando,
//usar un archivo a la vez. Sirve para poder ejecutar ds MINISHELL con heredoc sin que este se corrompa, ya que siempre
//te aseguras de que el archivo no existies en cada proceso antes de crearlo.
char	*new_file_name(char *path)
{
	int		name;
	char	*file_name;
	char	*name_str;

	name = 0;
	while (1)
	{
		file_name = ft_itoa(name);
		name_str = ft_strjoin(path, file_name);
		if (!name_str)
			return (NULL);
		if (access(name_str, F_OK))
			break ;
		name++;
		free(file_name);
		free(name_str);
	}
	free(file_name);
	return (name_str);
}
