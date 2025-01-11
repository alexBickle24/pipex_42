/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:47:53 by alcarril          #+#    #+#             */
/*   Updated: 2025/01/07 20:09:19 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **g_env;

void	imput_process(char **argv, int *pipe_ports)
{
	int		fd_in;
	char	**comands;
	char	*x_f;
	pid_t	id;
	
	if(pipe(pipe_ports) == -1)
		ft_error(NULL, NULL, NULL, NULL);
	id = fork();
	if (id < 0)
		ft_error(NULL, NULL, NULL, NULL);
	if (id == 0)
	{
		fd_in = tunel_file(argv[1], 0);
		comands = ft_split(argv[2], ' ');
		if (!comands)
			ft_error(NULL, NULL, NULL, NULL);
		x_f = comands[0];
		x_f = check_exe(x_f);
		close(pipe_ports[0]);
		if (dup2(pipe_ports[1], STDOUT_FILENO) == -1 || !x_f || fd_in < 0)
			ft_error(comands, NULL, NULL, NULL);
		if(execve(x_f, comands, NULL) == -1)
			ft_error(comands, NULL, NULL, NULL);
	}
}

void	output_process(char **argv, int *pipe_ports)
{
    int     fd_out;
    char    **comands;
    char    *x_file;
    pid_t   id;
	int status;

	close(pipe_ports[1]);
    if (dup2(pipe_ports[0], STDIN_FILENO) == -1)
		ft_error(NULL, NULL, NULL, NULL);
    id = fork();
    if (id < 0)
        ft_error(NULL, NULL, NULL, NULL);
    if (id == 0)
    {
        fd_out = tunel_file(argv[4], 1);
        comands = ft_split(argv[3], ' ');
        if (!comands)
            ft_error(NULL, NULL, NULL, NULL);
        x_file = comands[0];
        x_file = check_exe(x_file);
        if (!x_file || fd_out < 0 || execve(x_file, comands, NULL) == -1)
			ft_error(comands, NULL, NULL, NULL);
    }
    waitpid(-1 , &status, 0);
}

int	tunel_file(char *file, char flag)
{
	int fd_target;
	
	if (flag == 0)
	{
		fd_target = open(file, O_CREAT | O_RDONLY, 0664);
		if (fd_target < 0)
			return(-1);
		if (dup2(fd_target, STDIN_FILENO) == -1)
		{
			close (fd_target);
			return(-1);
		}
	}
	else
	{
		fd_target = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
		if (fd_target < 0)
			return(-1);
		if (dup2(fd_target, STDOUT_FILENO) == -1)
		{
			close (fd_target);
			return(-1);
		}
	}
	return (fd_target);
}


int main(int argz, char **argv, char **env)
{
	int		pipe_ports[2];
	
	if (argz == 5)
	{
		g_env = env;
		imput_process(argv, pipe_ports);
		output_process(argv, pipe_ports);
		return (0);
	}
	printf("Argumentos insuficinetes");
}