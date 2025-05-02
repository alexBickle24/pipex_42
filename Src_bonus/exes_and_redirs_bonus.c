/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exes_and_redirs_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcarril <alcarril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 02:56:26 by alex              #+#    #+#             */
/*   Updated: 2025/03/27 16:15:12 by alcarril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

//esta funcion va a tener que ser llamda desde otra funcion que tenga el caso de redireccion a la
//pipe o deireccion a un archvo de salida -> caso A.1
int	tunel_in_file(char *file)
{
	int	fd_trgt;

	if (access(file, F_OK | R_OK) == -1)
		return (-1);
	fd_trgt = open(file, O_RDONLY, 0664);
	if (fd_trgt < 0)
		return (-1);
	if (dup2(fd_trgt, STDIN_FILENO) == -1)
	{
		close(fd_trgt);
		return (-1);
	}
	close(fd_trgt);
	return (fd_trgt);
}

//esta funcion va a tener que ser llamda desde otra funcion que tenga el caso de redireccion a la
//pipe o deireccion a un archvo de salida -> caso A.2
int	tunel_out_file(char *file)
{
	int	fd_trgt;
	//modificacion si file es NULL se aborta funcion
	fd_trgt = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_trgt < 0)
		return (-1);
	if (dup2(fd_trgt, STDOUT_FILENO) == -1)
	{
		close(fd_trgt);
		return (-1);
	}
	close(fd_trgt);
	return (fd_trgt);
}
//esta funcion va a tener que ser llamda desde otra funcion que tenga el caso de redireccion a la
//pipe o deireccion a un archvo de salida -> caso B.1 y B.2 (se cntrola con el tercer argumento)
void	pipe_forward(int *pipe_reference, int pipe_port, int fd)
{
	int		other_fd;

	if (pipe_port == 0)
		other_fd = 1;
	else
		other_fd = 0;
	close(pipe_reference[other_fd]);
	if (dup2(pipe_reference[pipe_port], fd) == -1)
	{
		close(pipe_reference[pipe_port]);
		ft_error(NULL, NULL, NULL, NULL);
	}
	close(pipe_reference[pipe_port]);
}

//vamos a necesitar tambien funciones para manejar el caso de las redirecciones
//esta funcion sigue siendo util
void	close_fds(int *pipe_ports)
{
	if (pipe_ports)
	{
		close(pipe_ports[0]);
		close(pipe_ports[1]);
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

//de esta funcion si tockenizamos con una estructura[comando, dedireccion, flags... ]
//los necesitarems la utima parte
void	search_and_exec(t_control *c, int position)
{
	char	**orders_list;
	char	*comand;
	char	*x_file;

	orders_list = ft_split((const char *)(c->args[position]), ' ');
	if (!orders_list || !orders_list[0])
	{
		free(c->src_file);
		if (orders_list || !orders_list[0])
			ft_free_table(orders_list);
		ft_putstr_fd("comand not found\n", 2);
		exit(1);
	}
	comand = orders_list[0];
	//a partir de aqui es lo que necesitamos. adeas aqui tengo que hacer modificacion de una cosa
	x_file = check_exe(comand, c->env);
	if (x_file && (access(x_file, F_OK | X_OK) == -1))
	{
		ft_error(orders_list, c->src_file, x_file, strerror(errno));
	}
	else if (!x_file || execve(x_file, orders_list, c->env) == -1)
	{
		ft_error(orders_list, c->src_file, comand, "command not found");
	}
}
