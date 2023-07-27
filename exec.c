#include "includes/minishell.h"

/*
	Cosas con señales que no están (entiendo que será el ctrl + c o algo así)
	si el comando no es un builtin y hay comandos los ejecutamos con execve
	si no, quiere decir que es un builtin así que comprobamos que sea pwd, echo o env y ejectuamos cada uno
*/

void	child_builtin(t_read *p, t_ms *n, int l, t_list *cmd)
{
	char **envs;

	envs = turn_into_arr(p->env);
	signal(SIGINT,SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!is_builtin(n) && n->cmd)
		execve(n->path, n->cmd, envs);
	else if (n->cmd && !ft_strncmp(*n->cmd, "pwd", l) && l == 3)
		g_status = ms_pwd();
	else if (is_builtin(n) && n->cmd && !ft_strncmp(*n->cmd, "echo", l) && \
			l == 4)
		g_status = ms_echo(cmd);
	else if (is_builtin(n) && n->cmd && !ft_strncmp(*n->cmd, "env", l) && \
			l == 3)
	{
		g_status = 0;
		print_env(p->env);
	}
	//ft_free_matrix(&envs); Aquí hay que echarle un ojo porque hay que liberar de alguna manera pero quizas no con esta función porque libera cosas sin alojar
}

/*
	Recibimos la lista de comandos y los file descriptors
	Asignamos el contenido de cmd a n (para hacerlo más corto)
	Si el infile o el ooufile no es el estandar hacemos un dup2 (duplicamos el file descriptor recibido y le damos el valor estandar)
	Si algun dup2 devuelve -1 devolvemos el error "dup error"
	si no cerramos el file descriptor de cada uno (para evitar tener 2 iguales)
	si todo ha ido bien y hay más comandos hacemos un dup2 con el file descriptor de escritura y le damos el valor estandar
	Si falla devolvemos "dup error"
	si sale bien cerramos el file descriptor original y devolvemos un string vacío
*/

static void	*child_redir(t_list *cmd, int fd[2])
{
	t_ms	*n;
	
	n = cmd->content;
	if (n->infile != INFILE)
	{
		if (dup2(n->infile, INFILE) == -1)
			return (ms_error(DUPERROR, NULL, 1));
		close(n->infile);
	}
	if (n->outfile != OUTFILE)
	{
		if(dup2(n->outfile, OUTFILE) == -1)
			return (ms_error(DUPERROR, NULL, 1));
		close(n->outfile);
	}
	else if (cmd->next && dup2(fd[WRITE_FD], OUTFILE) == -1)
		return (ms_error(DUPERROR, NULL, 1));
	close(fd[WRITE_FD]);
	return ("");
}

/*
	Asignamos a n el contenido de cmd (como siempre para hacerlo más corto)
	si en el cmd de n hay algo a l le damos la longitud del comando dentro de n
	llamamos a child_redir dandole la lista de comandos y los fd del pipe
	cerramos el fd de lectura
	llamamos a child_builtin
	limpiamos la lista y nos salimos con el estatus que tengamos en el momento
*/
void	*child_process(t_read *p, t_list *cmd, int fd[2])
{
	t_ms	*n;
	int		l;

	n = cmd->content;
	l = 0;
	if (n->cmd)
		l = ft_strlen(*n->cmd);
	child_redir(cmd, fd);
	close(fd[READ_FD]);
	child_builtin(p, n, l, cmd);
	ft_lstclear(&p->cmd, free_cmd);
	exit(g_status);
}

/*
	creamos una variable pid a la que le asignamos el valor de fork (fork crea un proceso duplicado, para el padre devolverá el pid del hijo, mientras que para el hijo será 0)
	Si el pid es menor a 0 quiere decir que ha habido un error así que cerramos los file descriptors y devolvemos el error "fallo en el fork"
	si no, ejecutamos child_process en el proceso hijo
*/
void	exec_fork(t_read *p, t_list *cmd, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[READ_FD]);
		close(fd[WRITE_FD]);
		ms_error(FORKERROR, NULL, 1);
	}
	else if (!pid)
		child_process(p, cmd, fd);
}

/*
	Esta función iguala el contenido de cmd a n (para que sea más corto de escribir) e iguala dir a NULL para evitar errores luego
	si en el comando dentro de n hay algo intentamos abrirlo como directorio
	si el infile o el outfile es -1 (es decir, ha habido un error abriendo el file descriptor) devolvemos NULL
	Si el comando tiene path y es accesible o es un builtin llamamos a exec_fork
	Si no, comprobamos que no sea un builtin y el path no sea accesible o que sea un directorio, en cualquiera de los dos casos ponemos el g_status a 126
	Si no, comprobamos que no es un builtin y hay algo dentro del comando, si ocurre esto ponemos g_status a 127
	Si hemos abierto un directorio lo cerramos
	devolvemos un string vacío
*/
void	*check_to_fork(t_read *p, t_list *cmd, int fd[2])
{
	t_ms	*n;
	DIR		*dir;
	
	n = cmd->content;
	dir = NULL;
	if (n->cmd)
		dir = opendir(*n->cmd);
	if (n->infile == -1 || n->outfile == -1)
		return (NULL);
	if ((n->path && access(n->path, X_OK) == 0) || is_builtin(n))
		exec_fork(p, cmd, fd);
	else if (!is_builtin(n) && ((n->path && !access(n->path, F_OK)) || dir))
		g_status = 126;
	else if (!is_builtin(n) && n->cmd)
		g_status = 127;
	if (dir)
		closedir(dir);
	return ("");
}