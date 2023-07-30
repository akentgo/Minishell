#include "../includes/minishell.h"

extern int	g_status;

/*
 * This function will return the home directory
 */

static char	*get_home(t_read p)
{
	char	*tmp;
	char	*pwd;
	char	*home;

	pwd = getcwd(NULL, 0); //save the current directory
	if (!pwd) //if there is no pwd set it as "º "
		pwd = ft_strdup("º ");
	home = search_env(p.env, "HOME"); //save home directory in home
	if (home && home[0] && ft_strnstr(pwd, home, ft_strlen(pwd))) //if there is home, it is not empty and home is in pwd
	{
		tmp = pwd; //save pwd in tmp
		pwd = ft_strjoin("~", &pwd[ft_strlen(home)]); //join pwd to "~"
		free(tmp); //free tmp
	}
	free (pwd);
	pwd = ft_strjoin(home, " "); //add an space to the string
	free (home);
	home = ft_strjoin(" ", pwd); //add an space before the string
	free (pwd);
	return (home); //return the string
}

/*
 * This function returns the user name colored depending on its first letter
 */

static char	*get_user(t_read p)
{
	//Coger el nombre de las variables de entorno o devolver guest
	char	*tmp;
	tmp = search_env(p.env, "USER");
	if (!tmp)
		return ("guest");
	return (tmp);
}

/*
 *	This function creates a prompt using the user name eg: "asolano-@minishell$ "
 */

char	*ms_getprompt(t_read p)
{
	char	*tmp;
	char	*tmp2;
	char	*aux;

	tmp = get_user(p); //save user name in tmp
	tmp2 = ft_strjoin(tmp, "@minishell"); //join @minishell so we have user@minishell in tmp2
	//free(tmp);
	tmp = get_home(p); //save home directory in tmp
	aux = ft_strjoin(tmp2, tmp); // join directory to tmp2 so we have user@minishelldirectory in aux
	free (tmp); //free both tmp
	free (tmp2);
	tmp = ft_strjoin(aux, "$ "); //join "$ " so we have user@minishelldirectory$ 
	free (aux); //free aux
	return (tmp); //return the prompt
}
