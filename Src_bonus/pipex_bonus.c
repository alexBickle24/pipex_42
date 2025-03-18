/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:47:53 by alcarril          #+#    #+#             */
/*   Updated: 2025/03/18 01:44:36 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**g_env;
int		g_argz;

void	imput_process(char **args, int *pipe_p, char *src_file, int cont)
{
	pid_t		id;
	int			src_fd;
	static char	bool;

	if (pipe(pipe_p) == -1)
		ft_error(NULL, NULL, NULL, NULL);
	src_fd = tunel_file(src_file, 0);
	if (src_fd < 0)
	{
		bool = 1;
		perror(strerror(errno));
	}
	id = fork();
	if (id < 0)
		ft_error(NULL, NULL, src_file, NULL);
	if (id == 0 && !bool)
	{
		pipe_forward(pipe_p, 1, STDOUT_FILENO);
		search_and_exec(args, cont - 1);
	}
	if (cont == 4)
		if (unlink(src_file) < 0)
			ft_error(NULL, NULL, src_file, NULL);
	free(src_file);
}

void	link_pipes(int *first_pipe, char **arguments, int control)
{
	static int	iterations_control;
	int			middle_pipes[2];
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
	close (middle_pipes[0]);
	close (middle_pipes[1]);
}

void	output_process(char **argv, int *first_pipe_fd, int aux_cont)
{
	pid_t	id;
	int		fd_out;
	int		status;

	if (aux_cont == g_argz - 2)
		pipe_forward(first_pipe_fd, 0, STDIN_FILENO);
	id = fork();
	if (id < 0)
		ft_error(NULL, NULL, NULL, NULL);
	if (id == 0)
	{
		fd_out = tunel_file(argv[g_argz - 1], 1);
		if (fd_out < 0)
			ft_error(NULL, NULL, NULL, NULL);
		search_and_exec(argv, g_argz - 2);
	}
	while ((id = waitpid(-1, &status, 0)) > 0);//cambiar esta linea para qu ehaga lo mismo pero que pase la norma
	if (aux_cont == g_argz - 2)
		close_fds(first_pipe_fd);
}

int	main(int argz, char **argv, char **env)
{
	int		pipe_ports[2];
	char	*src_file;
	int		control;
	int		aux_control;

	g_env = env;
	g_argz = argz;
	control = 3;
	if (argz < 5)
		return (ft_putstr_fd(ERROR, 2), 1);
	src_file = parse_prompt(argv, &control);
	if (!src_file)
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
