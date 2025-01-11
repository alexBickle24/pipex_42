/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba_comillas.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:37:05 by alex              #+#    #+#             */
/*   Updated: 2025/01/04 22:23:23 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argz, char **argv)
{
    char *primer_argumento;

    if (argz != 2)
    {
        printf("error");
        return (1);
    }
    primer_argumento = argv[1];
    printf("%s", primer_argumento);
    return(0);
}