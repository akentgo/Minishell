/* this function will handle some error messages in case they're needed*/
int	error_message(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY); //open a file descriptor into fd
	folder = opendir(path); //open a directory into folder
	ft_putstr_fd("minishell: ", STDERR); //print "minishell: "
	ft_putstr_fd(path, STDERR); //print the path given
	if (ft_strchr(path, '/') == NULL) //if the path doesn't contain '/' print ": command not found"
		ft_putendl_fd(": command not found", STDERR);
	else if (fd == -1 && folder == NULL) //if can't open the file descriptor nor the folder prints ": not such file or directory"
		ft_putendl_fd(": Not such file or directory", STDERR);
	else if (fd == -1 && folder != NULL) // if its a folder prints ": is a directory"
		ft_putendl_fd(": is a directory", STDERR);
	else if (fd != -1 && folder == NULL) // if its a file ": permission denied"
		ft_putendl_fd(": Permission denied", STDERR);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL)) //if it doesnt contain '/' or it isnt a folder nor a file return an error value for unknown command (127)
		ret = UNKNOWN_COMMAND;
	else //otherwise it return an error for a not executable file (126)
		ret = IS_DIRECTORY;
	if (folder) // if we opened a directory we close it
		closedir(folder);
	ft_close(fd);
	return (ret);
}

/*this function do all the process to get the right return value*/
int	ret_proc(char *path, char **args, s_env *env, t_mini *mini)
{
	char	**env_array;
	char	*ptr;
	int		ret;

	ret = SUCCESS; // assign success value to ret
	g_sig.pid = fork(); // do a fork to the global value pid
	if (g_sig.pid == 0) // if it's 0 it means we're in the child process
	{
		ptr = env_to_str(env); //transform the environment variable to a char** so we can use it in execve
		if (ft_strchr(path, '/') != NULL) // if the path given has '/' we can execute the command
			execve(path, args, env_array);
		ret = error_message(path); //assign an error value to ret
		free_tab(env_array); //free the double array
		free_token(mini->start); //free the token
		exit(ret); //finish the process
	}
	else 
		waitpid(g_sig.pid, &ret, 0); //if we're in the parent process we wait for the child process to finish
	if (g_sig.sigint == 1 || g_sig.sigquit == 1) //if any of these two global variables are 1 we return the exit status
		return (g_sig.exit_status);
	return(ret); //else we return the value assigned before to ret
}

/*this function join the path and the command string, for example 
 * being the path "/bin" and the command "bash" this function will return
 * /bin/bash, what would be executable
 */
char	*path_join(const char s1, const char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	free (tmp);
	tmp = NULL;
	return (path);
}

char	*check_dir(char *bin, char *path)
{
	DIR				*folder; //variable para guardar un directorio
	struct dirent	*item; //estructura que devuelve el readdir
	char			*path;

	path = NULL;
	folder = opendir(bin); //abrimos el directorio que nos han dado
	if (!folder) //si no se puede abrir nos salimos sin devolver nada
		return (NULL);
	while (item = readdir(folder)) // si hemos podido abrirlo guardamos la estructura del directorio en item
	{
		if (ft_strcomp(item->d_name, command) == 0) //comparamos que el nombre del directorio sea igual al comando
			path = path_join(bin, item->d_name); //unimos el nombre de la ruta y el directorio
	}
	closedir(folder); //cerramos el directorio
	return (path); //devolvemos la ruta completa
}

/*
 * this function execute commands
 */
int	exec_bin(char **args, s_env *env, t_mini *mini)
{
	int		i;
	char	**bin;
	char	*path;
	int		*ret;

	i = 0;
	ret = UNKNOWN_COMMAND; //assign unknown command return value to ret
	while (env && env->value && ft_strcomp(env->name, "PATH") != 0) // buscamos la variable path en el env
		env = env->next;
	if (env == NULL || env->next == NULL) // si el env está vacío o no hay siguiente devolvemos el valor de ret_proc
		return (ret_proc(args[0], args, env, mini));
	bin = ft_split(env->value, ':'); //en bin guardamos los distintos path que conseguimos del env
	if (!args[0] && !bin[0]) //si no hay argumentos o path devolvemos un error
		return (ERROR);
	i = 1;
	path = check_dir(bin[0], args[0]); //asignamos a path el path completo del comando
	while (args[0] && bin[i] && path == NULL) //mientras que exista argumento, exista una ruta y path no sea nulo comprobamos que la ruta sea correcta
		path = check_dir(bin[i++], args[0]);
	if (path != NULL) //si path no está vacío asignamos a ret el valor de ret_proc con el path en lugar de args[0]
		ret = ret_proc(path, args, env, mini);
	else //si está vacío lo llamamos de forma normal
		ret = ret_proc(args[0], args, env, mini);
	free_tab(bin); //liberamos el doble array
	free(path); //liberamos el path
	return (ret);
}
