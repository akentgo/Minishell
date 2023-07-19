#include <unistd.h>
#include <stdio.h>
#include "../../includes/minishell.h"

int ms_cd(t_read *p)
{
	char	**str[2];
	char	*aux; //this will be an auxiliary string
	
	g_status = 0;
	str[0] = p->cmd->content; //set str[0] to the full command
	aux = search_env(p->env, "HOME"); //set aux to the variable HOME value
	if (!aux) //in case there is no aux at this point, save it as an empty string to avoid problems freeing later
		aux = ft_strdup("");
	str[1] = ft_expand_arr(NULL, aux); //set aux as a matrix in str[1]
	free (aux); //free to avoid leaks
	cd_error(str); //check if there is an error in str
	if (!g_status)
		p->env = export_env(p->env, "OLDPWD", str[1][1]); //*IMPORTANT* have to fix this function format, here or in the function itself // set the OLDPWD var
	aux = getcwd(NULL, 0); //save the current directory in aux
	if (!aux) //if get_cwd fails save an empty string
		aux = ft_strdup("");
	str[1] = ft_expand_arr(str[1], aux); //extend the matrix in str[1] with aux content
	free (aux);
	p->env = export_env(p->env, "PWD", str[1][2]); //*IMPORTANT* have to fix this function format here or in the function itself // set the new PWD var
	ft_free_matrix(&str[1]);  //free str[1] to avoid leaks
	return (g_status); //return the status
}
