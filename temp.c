void	output_process(char **argv, int *pipe_ports)
{
	int		fd_out;
	char	**comands;
	char	*x_file;
	pid_t	id;
	
	if (dup2(pipe_ports[0], STDIN_FILENO) == -1)
		ft_error(NULL, NULL, NULL, NULL);
	close(pipe_ports[1]);
	id = fork();
	if (id < 0)
		ft_error(NULL, NULL, NULL, NULL);
	if (id == 0)
	{
		fd_out = tunel_file(argv[4], 1);
		comands = ft_split((const char *)argv[3], ' ');
		if (!comands)
			ft_error(NULL, NULL, NULL, NULL);
		x_file = comands[0];
		x_file = check_exe(x_file);
		if (!x_file || fd_out < 0 || execve(x_file, comands, g_env) == -1)
			ft_error(NULL, NULL, NULL, NULL);
	}
	while(wait(NULL));
}

void	imput_process(char **argv, int *pipe_ports, int control, int fd_in)
{
	char	**comands;
	char	*x_f;
	pid_t	id;
	
	if(pipe(pipe_ports))
		ft_error(NULL,NULL,NULL,NULL);
	id = fork();
	if (id < 0)
		ft_error(NULL,NULL,NULL,NULL);
	if (id == 0)
	{
		fd_in = tunel_file(argv[control], fd_in, 0);
		comands = ft_split(argv[1], ' ');
		if (!comands)
			ft_error(NULL, NULL, NULL, NULL);
		x_f = comands[0];
		x_f = check_exe(g_env, x_f);
		if (dup2(pipe_ports[1], STDOUT_FILENO) == -1 || !x_f || fd_in < 0)
			ft_free(NULL, NULL, NULL, NULL);
		close(pipe_ports[0]);
		if(execve(x_f, comands, g_env) == -1)
			ft_error(NULL, NULL, NULL, NULL);
	}
}



////////////////////////////////////////BONUS SIN HEREDOC///////////////////////////


void	imput_process(char **arguments, int *pipe_ports)
{
	int fd_trgt;
	pid_t	id;
	
	if(pipe(pipe_ports) == -1)
		ft_error(NULL, NULL, NULL, NULL);
	id = fork();
	if (id < 0)
		ft_error(NULL, NULL, NULL, NULL);
	if (id == 0)
	{
		fd_inter = fd_forward(arg[1], 0);
		search_and_exec(arguments, 2);
	}
}

int main(int argz, char **argv, char **env)
{
	int		pipe_ports[2];
	int		control;
	int		src_file;
	
	if (argz < 4)
		return(1);
	g_env = env;
	imput_process(argv, pipe_ports);
	while (control < argz - 1)
	{
		link_pipes(pipe_ports, argv, control);
		control++;
	}
	output_process(argv, pipe_ports, argz);
	return (0);
	//mensajes de error
}




////////////////////////////////////////////////////


int		parse_prompt(char **arg, int argz, int *control)
{
	int		fd_inter;
	static char	*l;
	
    printf("el valor de la funcions %s\n", ft_strnstr(arg[1], "here\\_doc", 9));
	if (!(ft_strnstr(arg[1], "here\\_doc", 9) && ft_strlen(arg[1]) == 9))
	{
        printf("entra en  link pipes22\n");
        *control = 3;
        fd_inter = tunel_file(arg[1], 0);
        printf("el valor del fd es %d\n", fd_inter);
        if (fd_inter < 0)
            return(-1);
        printf("a");
        return(fd_inter);
	}
	if (argz < 6)
		return(-1);
	fd_inter = open("inter.txt", O_CREAT | O_TRUNC | O_APPEND | O_RDWR, 0664);
	if (fd_inter < 0)
		return(-1);
    l = get_next_line(0);//la  liena nunca va a ser NULL porque lee de al entrada estandar
	while (ft_strncmp(l, arg[2], ft_strlen(arg[2])) != 0 && ft_strlen(l) == 4)
	{
        write(1, ">", 1);
		parse_and_write(l, fd_inter);
        free(l);
        l = get_next_line(0);
	}
	*control = 4;
	return(free(l), fd_inter);
}




char *get_env_value(const char *key_value)
{
    int     i;
    size_t len;
    char *new_value;
    
    if (!key_value)
        return(NULL);
    len = ft_strlen(key_value);
    if (len == 0 || g_env == NULL)
        return(NULL);
    new_value = ft_strjoin(key_value, "=");
    if(new_value == NULL)
        return (NULL);
    i = 0;
    while (g_env[i] != NULL)
    {
        if ((ft_strncmp(new_value, g_env[i], len + 1)) == 0)
        {
            free(new_value);
            return ((g_env[i] + len + 1));
        }
        i++;
    }
    free(new_value);
    return(NULL);
}



if ((i == 0 && ((line[i+1] != ('(' && ' ')) && line[i+1] != '\0'))
    || (i >= 1 && (((line[i+1] != ('(' && ' '))
    && line[i+1] != '\0' && line[i - 1] == ' '))))

	line[i+1] != ('(' && ' ')



void parse_and_write(char *line, int fd_inter)
{
    unsigned int i;

    i = 0;
    while (line[i] != '\0')
    {
        if ((i == 0 && (line[i] == '$' && line[i+1] != '\n'))
            || (i >= 1 && ((line[i] == '$'
            && line[i+1] != '\n' && line[i - 1] == ' '))))
        {
			printf("el valor de line + 1 es %c\n", line[i+1]);
            if (line[i+1] != ('(' && ' ' && '\n') )
            {
                printf("GGGGGG\n");
                printf("el valor de line es %c\n", line[i]);
                i = write_env(&line[i], fd_inter, i);
            }
            else if (line[i+1] == '(')
                i = hrdoc_exec(&line[i], fd_inter, i);
            else
            {
                ft_putchar_fd(line[i], fd_inter);
                i++;
            }   
        }
        else
        {
            ft_putchar_fd(line[i], fd_inter);
            i++;
        }
    }
}


if ((i >= 1 && line[i-1] != '\0'
	&& line[i+1] != '(' && line[i+1] != ' ' && line[i+1] != '\n')
	|| (line[i+1] != '(' && line[i+1] != ' ' && line[i+1] != '\n'))



unsigned int    hrdoc_exec(char *line, int fd_inter, int counters)
{
    char    *new_line;
    pid_t   id;
    char **orders_list;
    char *x_file;
    unsigned    int len;

    new_line = trim_line(line);
    id = fork();
    if (id < 0)
       ft_error(NULL, NULL, NULL, NULL);
    if (id == 0)
    {
        orders_list = ft_split(new_line, ' ');
        if (!orders_list)
            ft_error(NULL, NULL, NULL, NULL);
        x_file = orders_list[0];
        x_file = check_exe(x_file);
        dup2(fd_inter, STDOUT_FILENO);
        if (!x_file || execve(x_file, orders_list, g_env) == -1)
            ft_error(orders_list, NULL, NULL, NULL);
    }
    wait(NULL);
    len = ft_strlen(new_line);
    return(counters + len + 2);
}




/////////////////////////////////

void	imput_process(char **arguments, int *pipe_ports, int src_file, int control)
{
	pid_t	id;
	
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
		return(1);
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
