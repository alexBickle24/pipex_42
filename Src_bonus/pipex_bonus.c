/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:47:53 by alcarril          #+#    #+#             */
/*   Updated: 2025/03/22 04:43:01 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	imput_process(t_control *control, int *pipe_p)
{
	pid_t		id;
	static char	error_mode;

	if (pipe(pipe_p) == -1)
		ft_error(NULL, NULL, NULL, NULL);
	if (tunel_in_file(control->src_file) != -1)
	{
		id = fork();
		if (id < 0)
			ft_error(NULL, control->src_file, NULL, NULL);
		if (id == 0 && !error_mode)
		{		
			pipe_forward(pipe_p, 1, STDOUT_FILENO);
			search_and_exec(control, control->control - 1);
		}
	}
	else 
		perror(control->src_file);
	if (control->control == 4)
		if (unlink(control->src_file) < 0)
			ft_error(NULL, NULL, control->src_file, strerror(errno));
	free(control->src_file);
	control->src_file = NULL;
}

void	link_pipes(t_control *control, int *first_pipe)
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
		search_and_exec(control, control->control);
	}
	pipe_forward(middle_pipes, 0, STDIN_FILENO);
	close (middle_pipes[0]);
	close (middle_pipes[1]);
}

void	output_process(t_control *control, int *first_pipe_fd)
{
	pid_t	id;
	int		fd_out;
	int		status;

	if (control->start == control->num_args - 2)
		pipe_forward(first_pipe_fd, 0, STDIN_FILENO);
	id = fork();
	if (id < 0)
		ft_error(NULL, NULL, NULL, NULL);
	if (id == 0)
	{
		fd_out = tunel_out_file(control->args[control->num_args - 1]);
		if (fd_out < 0)
		{	
			perror(control->args[control->num_args - 1]);
			close_fds(NULL);
			exit (1);
		}
		search_and_exec(control, control->num_args - 2);
	}
	id = waitpid(-1, &status, 0);
	while (id > 0)
		id = waitpid(-1, &status, 0);
	close_fds(NULL);
}

int	main(int argz, char **argv, char **env)
{
	t_control	c;//tiene sentido que sea la memeria local ya que aqui se le pasan lso argumentos ya limpios en minishell
	int			pipe_ports[2];

	set_control(&c, argv, argz, env);
	if (argz < 5)
		return (ft_putstr_fd(ERROR, 2), 1);
	c.src_file = parse_prompt(c.args, c.num_args, &(c.control), c.env);
	if (!c.src_file)
	{
		if (c.control == 4 && c.num_args < 6)
			return (ft_putstr_fd(ERROR_HEREDOC, 2), 1);//toda la parte del aprseo y control de errores de argumentos habria que qitarla para minishjell
		return (1);
	}
	c.start = c.control;
	imput_process(&c, pipe_ports);
	while (c.control < argz - 2)
	{
		link_pipes(&c, pipe_ports);
		c.control++;
	}
	output_process(&c, pipe_ports);
	return (0);
}
