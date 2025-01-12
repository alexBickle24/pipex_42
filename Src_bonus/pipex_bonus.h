/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 03:03:16 by alex              #+#    #+#             */
/*   Updated: 2025/01/12 02:57:03 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H_BONUS
# define PIPEX_H_BONUS

#include "../Include/libft/libft.h"
#include "../Include/ft_printf/ft_printf.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <sys/wait.h>

extern  char** g_env;
extern  int g_argz;

void	imput_process(char **arguments, int *pipe_ports, int src_file, int control);
void	link_pipes(int *first_pipe, char **arguments, int control);
void	output_process(char **argv, int *first_pipe_fd, int aux_control);
char    *check_exe(char *x_file);
char    *get_env_value(const char *key_value);
char	*get_relative_path(char **posible_paths, char *x_file);
void    ft_error(char **table1, char **table2, char *str1, char *str2);
void	ft_free_table(char **ptr);
int     tunel_file(char *file, char flag);
void	pipe_forward(int *pipe_reference, int pipe_port, int fd);
void    search_and_exec(char **arguments, int control);
int		parse_prompt(char **arg, int *control);
void    parse_and_write(char *line, int fd_inter);
unsigned int     hrdoc_exec(char *line, int fd_inter, int counters);
char    *trim_line(char *line);
unsigned int    write_env(char *line, int fd_dest, unsigned int count);

#endif