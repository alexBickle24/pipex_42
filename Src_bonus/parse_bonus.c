/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:39:57 by alex              #+#    #+#             */
/*   Updated: 2025/03/17 05:33:55 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*parse_prompt(char **arg, int *control)
{
	static	char	*l;
	char			*src_name;
	int				fd_inter;
	
	if (!(ft_strnstr(arg[1], "here_doc", 8) && ft_strlen(arg[1]) == 8))
	{
		src_name = ft_strdup(arg[1]);
		return (src_name);
	}
	*control = 4;
	src_name = new_file_name("/tmp/");
	fd_inter = open(src_name, O_CREAT | O_TRUNC | O_APPEND | O_RDWR, 0664);
	if (fd_inter < 0 || g_argz < 5)
		return (NULL);
	write(1, ">", 1);
	l = get_next_line(0);
	while (ft_strncmp(l, arg[2], ft_strlen(arg[2])) != 0 || (ft_strlen(l) - 1) != ft_strlen(arg[2]))
	{
		write_line_in_heredoc(l, fd_inter);
		free(l);
		write(1, ">", 1);
		l = get_next_line(0);
	}
	free(l);
	return (close (fd_inter), src_name);
}

void	write_line_in_heredoc(char *line, int fd_inter)
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
//la logica esta bien pero falta ajustar los indices ademas habria que  hacer un split y maneja rloq ue me 
//explcio sltan del modo explicito, De todas maneras cuando hice pruebas seguisinedo imposibel de imirtare
//hoce captura
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
			ft_error(NULL, NULL, new_line, NULL);
		free(new_line);
		x_file = orders_list[0];
		x_file = check_exe(x_file);
		dup2(fd_inter, STDOUT_FILENO);
		if (!x_file || execve(x_file, orders_list, g_env) == -1)
			ft_error(orders_list, NULL, NULL, NULL);
	}
	wait(NULL);
	len = ft_strlen(new_line);
	return (counters + len + 1);
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
	return (free(env_name), count - 1);
}
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
