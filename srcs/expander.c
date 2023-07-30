#include "../includes/minishell.h"

extern int	g_status;

/*
 * This function puts a string (s2) into another one (s1), freeing the first one
 */

void	ft_strreplace(char **s1, char *s2)
{
	char	*sdup;
	
	sdup = ft_strdup(s2);
	*s1 = sdup;
	return;
}

/*
 * This function works as strchr but in a recursive way, checking if every character from
 * a string (str) is one of the searched (check)
 */

int	ft_strchr_r(const char *str, char *check)
{
	int	i[2];

	i[0] = -1;
	if (!str)
		return (-1);
	while (str[++i[0]])
	{
		i[1] = -1;
		while (check[++i[1]])
		{
			if (str[i[0]] == check[i[1]])
				return (i[0]);
		}
	}
	return (-1);
}

/*
	This function looks for any of the characters from check in str and return its position
*/
int	ft_strchr_r_i(const char *str, char *check)
{
	int	i[2];

	i[0] = -1;
	if (!str)
		return (-1);
	while (str[++i[0]])
	{
		i[1] = -1;
		while (check[++i[1]])
		{
			if (str[i[0]] == check[i[1]])
				return (i[0]);
		}
	}
	return (-1);
}

/*
 *	This function will expand the path variable (~) if found out of quotes, giving it its actual value
 */

char	*expand_path(char *str, int i, int qte[2], char *value)
{
	char	*path;
	char	*holder;

	qte[0] = 0; //we set the quotes markers to 0
	qte[1] = 0;
	while (str && str[++i]) //while there is line
	{
		qte[0] = (qte[0] + (!qte[1] && str[i] == '\'')) % 2; // similar to lexer
		qte[1] = (qte[1] + (!qte[0] && str[i] == '\"')) % 2;
		if (!qte[0] && !qte[1] && str[i] == '~' && (i == 0 || str[i - 1] != '$'))
		{
			holder = ft_substr(str, 0, i); //holder will have the part of the string that we have iterated until now
			path = ft_strjoin(holder, value); //path will be the string plus the actual value of the path
			free (holder); //we free holder
			holder = ft_substr(str, i + 1, ft_strlen(str)); //holder will have now a new string, containing everything after '~'
			free (str); //we free our string since we do not need it anymore
			str = ft_strjoin(path, holder); //we join this new line to our path, getting our line with '~' replaced with its actual value
			free (holder); //we free holder
			free (path); //we free path
			return (expand_path(str, i + ft_strlen(value) - 1, qte, value)); //we call the function giving it the new string with the value replaced, in case there are more of them the will be replaced again, if not it will just return the string
		}
	}
	free (value);
	return (str);
}

/*
	This function will replace the environment variables values in the string 
*/

static char	*get_substr(char *str, int i, t_read *rd)
{
	char	*ret; //this is the return value
	int		pos; //this is the position to start replacing
	char	*var; //this is the variable value
	char	*holder; //this is just a holder to join strings

	pos = ft_strchr_r_i(&str[i], "|\"\'$?>< ") + (ft_strchr("$?", str[i]) != 0); // we find the character in the string and return its position ( plus 1 if it is $ or ?)
	if (pos == -1) //if the position is -1 means there is no variable or something so set the last position of the string
		pos = ft_strlen(str) - 1;
	ret = ft_substr(str, 0, i - 1); //save a substring starting from the position taken
	var = search_env_len(rd->env, &str[i], ft_strchr_r_i(&str[i], "\"\'$|>< ")); //find the variable value using our new and amazing function search_env_len (similar to search_env but we give it a length to check)
	if (!var && str[i] == '$') //if there is not variable found and we have a dollar we have to save the process id
		var = ft_itoa(rd->pid);
	else if (!var && str[i] == '?')//if there is not variable found and we have a question mark we have to save the last status
		var = ft_itoa(g_status);
	holder = ft_strjoin(ret, var); //join the substring and the variable saved
	free (ret);
	ret = ft_strjoin(holder, &(str[i + pos])); //join the rest of the string
	free (var);
	free (holder);
	free (str);
	return (ret);
}

/*
	This function goes through the string and replace environment variables with their value
*/

char	*expand_var(char *str, int qte[2], int i, t_read *rd)
{
	qte[0] = 0;
	qte[1] = 0;
	while (str && str[++i] != '\0')
	{
		qte[0] = (qte[0] + (!qte[1] && str[i] == '\'')) % 2; //similar to lexer way to check quotes
		qte[1] = (qte[1] + (!qte[0] && str[i] == '\"')) % 2;
		//if there isn't a single quote open and we find $ and there is something after that and...		
		if (!qte[0] && str[i] == '$' && str[i + 1] && \
		((ft_strchr_r_i(&str[i + 1], " :;/~%^{}") && !qte[1]) || // we find any of these characters and there is no double quote open or..
		(ft_strchr_r_i(&str[i + 1], "\":;/~%^{}") && qte[1]))) //we find the same characters plus double quote and double quote is open
			return (expand_var(get_substr(str, ++i, rd), qte, -1, rd)); //do recursivity to get the same string but with the first variable replaced (we do this until we have reached the end of the string)
	}
	return (str); //once we have checked the whole string return it with its new values
}
/*



char	*expander(char *str, int i, int q[2], t_read rd)
{
	q[0] = 0;
	q[1] = 0;
	env_hold = env;
	i = 0;
	while (str[i] && str[++i])
	{
		q[0] = (q[0] +(!q[1] && str[i] == '\'')) % 2; //same as lexer
		q[1] = (q[1] +(!q[0] && str[i] == '\"')) % 2; //same as lexer
		if (!q[0] && str[i] == '$' && str[i + 1] && \
			((ft_strchr_r_i(&str[i + 1], "/:;{}/~%^ ") && !q[1]) || \
			(ft_strchr_r_i(&str[i + 1], "/:;{}/~%^\"" && q[1])))
			return (expander(get_substr(str, ++i, rd), -1, q, rd));
	}
	return (str);
}*/
