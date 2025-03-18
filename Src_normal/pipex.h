/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 03:03:16 by alex              #+#    #+#             */
/*   Updated: 2025/03/18 00:25:02 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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

void	imput_process(char **argv, int *pipe_ports);
void	output_process(char **argv, int *pipe_ports);
int		tunel_file(char *file, char flag);
void	pipe_forward(int *pipe_reference, int pipe_port, int fd);
char	*check_exe(char *x_file);
char	*get_env_value(const char *key_value);
char	*search_relative_path(char **posible_paths, char *x_file);
void	ft_error(char **table1, char **table2, char *str1, char *str2);
void	ft_free_table(char **ptr);

#endif