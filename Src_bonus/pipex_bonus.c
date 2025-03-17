/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:47:53 by alcarril          #+#    #+#             */
/*   Updated: 2025/03/17 22:43:05 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**g_env;
int		g_argz;

//lsd redirecciones de la entrada se pueden hacer desde elpadre o desde el hijo peri hayq ue tener en cuuenta varias cosas
//Primero, si se hacen desde el padre, en caso de error no puede cerrar el porceso porque las pipes originales no lo hacen
//dolo habria que devover un mensaje de erro y continuar conla ejecucion del codigo. Despues hayq ueteern en cuanta que si estanmos 
//usando un archivo como IPC vamos a tener que borrarlo. EL problema esta en que como los porcesos se eecutan a lavez tenermos que elegir entre
// borralo en antes de acabar todos los porcesos de las pipes (en ese caso tendriamos que redireccionar y abrir desde el padre para que 
//garanticfemos que ocuura antes de su borrasdo) o podria mos borrarlo cuando acaben los procesos de las pipes, es decir despues de wait. ASi nos 
//asegunramos poderaborrlo desde el hijo y desde el padre 
void	imput_process(char **args, int *pipe_p, char *src_file, int cont)
{
	pid_t		id;
	int			src_fd;
	static char	bool;

	if (pipe(pipe_p) == -1)
		ft_error(NULL, NULL, NULL, NULL);//podria no tener que abortarse el programa si falla una pipe
	src_fd = tunel_file(src_file, 0);
	if (src_fd < 0)
	{
		bool = 1;//esto es para que no ejecute le comando, no escriba en la pipe
		perror(strerror(errno));
	}
	//ESTO ES PARA WEL CASO DE UN APERO NO HAY UQ DEJARLo
	// if (cont == 4 && g_argz == 5)//ESTO ES PARA WEL CASO DE UN APERO NO HAY UQ DEJARLo
	// {
	// 	if (tunel_file(args[g_argz - 1], 1) < 0)
	// 		ft_error (NULL, NULL, NULL, NULL);//meter aqui otras cosas de cerrar las pipes
	// 	search_and_exec(args, cont - 1);
	// }
	if ((id = fork()) < 0)
		ft_error(NULL, NULL, src_file, NULL);
	if (id == 0 && !bool)
	{
		pipe_forward(pipe_p, 1, STDOUT_FILENO);
		search_and_exec(args, cont - 1);
	}
	//UNLINK PUEDE ESTAR AQUI O DESPUES DE WAit
	//ocurre porque si se crea en el proceso padre espera a que se pierda la iultima referencia
	//al archivo, el decir que se borre el ultimo fd que apuntaba a el. Si se crea eb el hijo, por lorden de ejecucion
	//en la cola de procesos listos, llega antees unlink que al proce hijo y lo borrara porque no detecta ningun 
	//fd que lo tenga abierto.
	if (cont == 4)
		if (unlink(src_file) < 0)
			ft_error(NULL, NULL, src_file, NULL);
	free(src_file);
}
//logica de que la redireccion dde la salida a la pipe se ahce en el hijo para que elpadre tenga las puertas biertas en la entrada
//depues se hace otra pipe para que le siguiente hijo vuelva a escribir. La redireccion de la entrada se hace en el padre siempre
//sabiendo que despues se va a crear otra pipe para que escriba el hijo. Esta manera de hacerlo esta justificada porque laspipes
//originales tiene que poeder vaciarse en caso de que un comando falle porque sino no podra escribir el siguiente comandom ya que no depende
//del comando any¡terior que se jecute el comando siguiente 8de aho que se tenga que creardos pipes).Se podria hcer la redireccion de la entrada desde el hijo usando una piep sestatica
//que se libere en la siguiente iteraion pero es un lio que filpas.
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
	if ((id = fork()) < 0)
		ft_error(NULL, NULL, NULL, NULL);
	if (id == 0)
	{
		pipe_forward(middle_pipes, 1, STDOUT_FILENO);
		search_and_exec(arguments, control);
	}
	pipe_forward(middle_pipes, 0, STDIN_FILENO);//redirecciono a la pipe, despues sigue el acceso porque el kernel no la ha borrado 
	close (middle_pipes[0]);
	close (middle_pipes[1]);
}

//aqui da igual redireccionar la salida del padre al archivo en el padre o en el hijo. Tambien se peude ahcer al principoi
//del pPrograma porque la redirecciones de la salida siempre se estan haciendo desde el hijo asiq ue se mantendria hasta el
//fonal de la ejeucucion 
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
	while ((id = waitpid(-1, &status, 0)) > 0);
	close(first_pipe_fd[0]);
	close(first_pipe_fd[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
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
	imput_process(argv, pipe_ports, src_file, control);//se puede meter para que solo lo envie a fuera si no hay mas que un comando
	while (control < argz - 2)//editar esto y control para que pueda funcionar sin pipes
	{
		link_pipes(pipe_ports, argv, control);
		control++;
	}
	output_process(argv, pipe_ports, aux_control);
	return (0);
}
