/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 03:03:16 by alex              #+#    #+#             */
/*   Updated: 2025/03/17 22:48:40 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../Include/libft/libft.h"
# include "../Include/ft_printf/ft_printf.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <limits.h>
# include <stdio.h>
# include <sys/wait.h>

# define ERROR "Arguments ERROR: Need more arguments\n"

extern char	**g_env;
extern int	g_argz;

unsigned int	write_env(char *line, int fd_dest, unsigned int count);
unsigned int	hrdoc_exec(char *line, int fd_inter, int counters);
void			imput_process(char **args, int *pipe_p, char *src_file, int cont);
void			link_pipes(int *first_pipe, char **arguments, int control);
void			output_process(char **argv, int *first_pipe_fd, int aux_cont);
char			*check_exe(char *x_file);
char			*get_env_value(const char *key_value);
char			*find_exe_file(char **posible_paths, char *x_file);
void			ft_error(char **table1, char **table2, char *str1, char *str2);
void			ft_free_table(char **ptr);
int				tunel_file(char *file, char flag);
void			pipe_forward(int *pipe_reference, int pipe_port, int fd);
void			search_and_exec(char **arguments, int control);
char			*parse_prompt(char **arg, int *control);
void			write_line_in_heredoc(char *line, int fd_inter);
char			*trim_line(char *line);
char			*new_file_name(char *path);
void			close_fds(int *pipe_ports);

#endif