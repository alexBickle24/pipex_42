/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exes_and_redirs_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 02:56:26 by alex              #+#    #+#             */
/*   Updated: 2025/03/17 22:45:23 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

//Hayd isc casos porque no los archivos no se abren con los mismo sprermiosso en esos casos 
int	tunel_file(char *file, char flag)
{
	int	fd_trgt;

	if (!flag)
	{
		fd_trgt = open(file, O_RDONLY , 0664);
		if (fd_trgt < 0)
			return (-1);
		if (dup2(fd_trgt, STDIN_FILENO) == -1)
		{
			close(fd_trgt);
			return (-1);
		}
	}
	else
	{
		fd_trgt = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		if (fd_trgt < 0)
			return (-1);
		if (dup2(fd_trgt, STDOUT_FILENO) == -1)
		{
			close(fd_trgt);
			return (-1);
		}
	}
	return (close(fd_trgt),fd_trgt);
}

void	pipe_forward(int *pipe_reference, int pipe_port, int fd)
{
	int		other_fd;

	if (pipe_port == 0)
		other_fd = 1;
	else
		other_fd = 0;
	close(pipe_reference[other_fd]);
	if (dup2(pipe_reference[pipe_port], fd) == -1)
		ft_error(NULL, NULL, NULL, NULL);
	close(pipe_reference[pipe_port]);
}

void	search_and_exec(char **arguments, int control)
{
	char	**orders_list;
	char	*comand;
	char	*x_file;

	orders_list = ft_split((const char *)arguments[control], ' ');
	if (!orders_list)
		ft_error(NULL, NULL, NULL, NULL);
	comand = orders_list[0];
	x_file = check_exe(comand);
	if (execve(x_file, orders_list, g_env) == -1)//hayq quietoq ue mire x_file par quw errno lo onfigureotra
		ft_error(orders_list, NULL, NULL, NULL);

}

void 	close_fds(int *pipe_ports)
{
	close(pipe_ports[0]);
	close(pipe_ports[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}