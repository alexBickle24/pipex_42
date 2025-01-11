/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1pids.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 22:32:07 by alex              #+#    #+#             */
/*   Updated: 2024/12/29 22:32:11 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int main() 
{
    pid_t pid;
    
    pid = fork();
    if (pid < 0) 
    {
        perror("fork failed");
        return 1;
    } 
    else if (pid == 0) 
    {
        printf("Soy el proceso hijo (PID: %d)\n", getpid());
    } 
    else 
    {
        printf("Soy el proceso padre (PID: %d), mi hijo tiene PID: %d\n", getpid(), pid);
    }
    return (0);
}