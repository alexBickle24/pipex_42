/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:47:53 by alcarril          #+#    #+#             */
/*   Updated: 2025/01/12 02:56:20 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**g_env;
int		g_argz;

void	imput_process(char **arguments, int *pipe_ports, int src_file, int control)
{
	pid_t	id;
	
	if (control == 4)
	{
		close (src_file);
		src_file = tunel_file("inter.txt", 0);
		if (src_file < 0)
			ft_error(NULL, NULL, NULL, NULL);
	}
	if (src_file == -1)
		ft_error(NULL, NULL, NULL, NULL);
	if(pipe(pipe_ports) == -1)
		ft_error(NULL, NULL, NULL, NULL);
	id = fork();
	if (id < 0)
		ft_error(NULL, NULL, NULL, NULL);
	if (id == 0)
	{
		pipe_forward(pipe_ports, 1,  STDOUT_FILENO);
		search_and_exec(arguments, control - 1);
	}
}

void	link_pipes(int *first_pipe, char **arguments, int control)
{
	int			middle_pipes[2];
	static int  iterations_control;
	int			id;
	
	if (iterations_control == 0)
		pipe_forward(first_pipe, 0, STDIN_FILENO);
	if (pipe(middle_pipes) == -1)
		ft_error(NULL, NULL, NULL, NULL);
	iterations_control++;
	id = fork();
	if (id < 0)
		ft_error(NULL, NULL, NULL, NULL);
	if (id == 0)
	{
		pipe_forward(middle_pipes, 1, STDOUT_FILENO);
		search_and_exec(arguments, control);
	}
	pipe_forward(middle_pipes, 0, STDIN_FILENO);
}

void	output_process(char **argv, int *first_pipe_fd, int aux_control)
{
	int		fd_trgt;
	pid_t	id;
	int		status;
	
	if (aux_control == g_argz - 2)
		pipe_forward(first_pipe_fd, 0, STDIN_FILENO);
	id = fork();
	if (id < 0)
		ft_error(NULL, NULL, NULL, NULL);
	if (id == 0)
	{
		fd_trgt = tunel_file(argv[g_argz - 1], 1);
		if (fd_trgt < 0)
			ft_error(NULL, NULL, NULL, NULL);
		search_and_exec(argv, g_argz - 2);
	}
	while ((id = waitpid(-1, &status, 0)) > 0);
}

int main(int argz, char **argv, char **env)
{
	int		pipe_ports[2];
	int		control;
	int		src_file;
	int 	aux_control;
	
	g_env = env;
	g_argz = argz;
	if (argz < 5)
	{
		printf("Arguments error\n");
		return(1);
	}
	src_file = parse_prompt(argv, &control);
	if (src_file == -1)
		ft_error(NULL, NULL, NULL, NULL);
	aux_control = control;
	imput_process(argv, pipe_ports, src_file, control);
	while (control < argz - 2)
	{
		link_pipes(pipe_ports, argv, control);
		control++;
	}
	output_process(argv, pipe_ports, aux_control);
	return (0);
}
