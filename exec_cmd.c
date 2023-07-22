// #include "includes/minishell.h" CMD+SHIFT+7 para eliminar los comments estos de la izquierda

// /*
//     This function finds the full path for a command. Example: /bin/cat
//     It receives the PATH variable splitted in  env_path, the command in cmd and the full variable PATH in path
// */
// static char *find_command(char **env_path, char *cmd, char *path)
// {
//     char    *tmp;
//     int     i;

//     i = -1;
//     path = NULL;
//     while (env_path && env_path[++i])
//     {
//         free (path);
//         tmp = ft_strjoin(env_path[i], "/");
//         if (!tmp)
//             return (NULL);
//         path = ft_strjoin(tmp, cmd);
//         free(tmp);
//         if (!path)
//             return (NULL);
//         if (access(path, F_OK) == 0)
//             break ;
//     }
//     if (!env_path || !env_path[i])
//     {
//         free (path);
//         return (NULL);
//     }
//     return (path);
// }

// /*
//     This function check if the command is executable and open the directory in case it is necessary
// */

// static DIR  *cmd_check(t_read *p, t_list *cmd, char ***str, char *path)
// {
//     t_ms    *n;
//     DIR     *dir;

//     dir = NULL;
//     n = cmd->content; //just to make it shorter to write
//     if (n && n->cmd) //if there are commands try to open them as a directory and save it in dir
//         dir = opendir(*n->cmd);
//     if (n && n->cmd && ft_strchr(*n->cmd, '/') && !dir) //if we find a '/' in cmd and there is not a directory open
//     {
//         *str = ft_split(*n->cmd, '/'); //split it by '/'
//         n->path = ft_strdup(*n->cmd); //save it in path
//         free (n->cmd[0]); //free cmd[0] to allocate it again later
//         n->cmd[0] = ft_strdup(str[0][ft_matrixlen(*str) - 1]); //save the last line from the split
//     }
//     else if (!is_builtin(n) && n && n->cmd && !dir) //if it is not a builtin, there are not '/' in the command and it is not a directory
//     {
//         path = search_env(p->env, "PATH"); //find path and copy it to split it later
//         *str = ft_split(path, ':'); //split the path so we have each path separated
//         free (path); //free the full path
//         n->path = find_command(*str, *n->cmd, n->path); //find the right path for the command
//         if (!n->path || !n->cmd[0] || !n->cmd[0][0]) //if we do not have a path or a command send "it is not a command" error
//             ms_error(NOCMD, *n->cmd, 127);
//     }
//     return (dir);
// }

// /*
//     This function check if the command is right and call ms_error in case it is not
// */

// void    get_cmd(t_read *p, t_list *cmd, char **str, char *path)
// {
//     t_ms    *n;
//     DIR     *dir;

//     n = cmd->content;
//     dir = cmd_check(p, cmd, &str, path);
//     if (!is_builtin(n) && n && n->cmd && dir) //if the command is not a builtin and there is a directory to open call ms_error with "is a directory" error
//         ms_error(IS_DIR, n->cmd, 126);
//     else if (!is_builtin(n) && n && n->path && access(n->path, F_OK) == -1) // if the command is not a builtin, there is a path and the path is not a directory call ms_error with "is not a directory" error
//         ms_error(NODIR, n->path, 127);
//     else if (!is_builtin(n) && n && n->path && access(n->path, X_OK) == -1) // if the command is not a builtin, there is a path and the path is a directory but not accessible call ms_error with "permission" error
//         ms_error(NOPERM, n->path, 126);
//     if (dir) //if we opened a directory close it
//         closedir(dir);
//     ft_free_matrix(&str); //free the string alocated in cmd_check
// }

// /*
//     This function executes the commands if they're not a builtin (called in builtins.c).
//     It receives the t_read variable and the list of commands
// */
// void    exec_cmd(t_read *p, t_list *cmd)
// {
//     int fd[2];
//     get_cmd(p, cmd, NULL, NULL);
//     if (pipe(fd) == -1) //if the pipe fails call ms_error
//         return (ms_error(PIPERROR, NULL, 1));
//     if (!check_to_fork(p, cmd, fd)) //if we try to fork and fail return null (called in exec.c)
//         return (NULL);
//     close(fd[WRITE_END]); // close the writing file descriptor
//     if (cmd->next && !((t_ms *)cmd->next->content)->infile) //if we do not have a file descriptor set it as one from 'fd'
//         ((t_ms *)cmd->next->content)->infile = fd[READ_END];
//     else
//         close(fd[READ_END]); //if we have a file descriptor close the 'fd' reading file descriptor
//     if (((t_ms *)cmd->content)->infile > 2) // if infile is higher than 2 (meaning it is not default) close it to avoid leaks
//         close(((t_ms *)cmd->content)->infile);
//     if (((t_ms *)cmd->content)->outfile > 2) // same for outfile
//         close(((t_ms *)cmd->content)->outfile);
//     return (NULL);
// }