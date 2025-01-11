/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba_apend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 23:38:50 by alex              #+#    #+#             */
/*   Updated: 2024/12/30 23:51:19 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int fd;

	fd = open("archivoapend", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		return (0);
	}
	write(fd, "hola\n", 5);
	write(fd, "cara\n", 5);
	write(fd, "cola\n", 5);
	close(fd);
	return (0);

}
