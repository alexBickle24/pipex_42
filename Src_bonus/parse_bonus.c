/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:39:57 by alex              #+#    #+#             */
/*   Updated: 2025/01/21 19:52:44 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	parse_prompt(char **arg, int *control)
{
	static char	*l;
	int			fd_inter;

	if (!(ft_strnstr(arg[1], "here_doc", 8) && ft_strlen(arg[1]) == 8))
	{
		*control = 3;
		fd_inter = tunel_file(arg[1], 0);
		if (fd_inter < 0)
			return (-1);
		return (fd_inter);
	}
	fd_inter = open("inter.txt", O_CREAT | O_TRUNC | O_APPEND | O_RDWR, 0664);
	if (fd_inter < 0 || g_argz < 6)
		return (-1);
	write(1, ">", 1);
	l = get_next_line(0);
	while (ft_strncmp(l, arg[2], ft_strlen(arg[2])) != 0 || (ft_strlen(l) - 1) != ft_strlen(arg[2]))
	{
		parse_and_write(l, fd_inter);
		free(l);
		write(1, ">", 1);
		l = get_next_line(0);
	}
	*control = 4;
	return (free(l), fd_inter);
}

void	parse_and_write(char *line, int fd_inter)
{
	unsigned int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$')
		{
			if ((i >= 1 && line[i - 1] == ' '
					&& line[i + 1] != '(' && line[i + 1] != ' '
					&& line[i + 1] != '\n' && line[i + 1] != '$')
				|| (line[i + 1] != '(' && line[i + 1] != ' '
					&& line[i + 1] != '\n' && line[i + 1] != '$'))
			{
				i = write_env(&line[i], fd_inter, i);
			}
			else if (line[i + 1] == '(')
				i = hrdoc_exec(&line[i], fd_inter, i);
			else
				ft_putchar_fd(line[i], fd_inter);
		}
		else
			ft_putchar_fd(line[i], fd_inter);
		i++;
	}
}

unsigned int	hrdoc_exec(char *line, int fd_inter, int counters)
{
	unsigned int	len;
	pid_t			id;
	char			**orders_list;
	char			*new_line;
	char			*x_file;

	id = fork();
	if (id < 0)
		ft_error(NULL, NULL, NULL, NULL);
	if (id == 0)
	{
		new_line = trim_line(line);
		orders_list = ft_split(new_line, ' ');
		if (!orders_list)
			ft_error(NULL, NULL, NULL, NULL);
		x_file = orders_list[0];
		x_file = check_exe(x_file);
		dup2(fd_inter, STDOUT_FILENO);
		if (!x_file || execve(x_file, orders_list, g_env) == -1)
			ft_error(orders_list, NULL, new_line, NULL);
	}
	wait(NULL);
	len = ft_strlen(new_line);
	return (counters + len + 2);
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

unsigned int	write_env(char *line, int fd_dest, unsigned int count)
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
	env_value = get_env_value(env_name);
	if (!env_value)
	{
		free(env_name);
		return (count - 1);
	}
	ft_putstr_fd(env_value, fd_dest);
	return (count - 1);
}
