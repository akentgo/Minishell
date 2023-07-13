#include "includes/minishell.h"

/*
 * 	This function count the number of words for our redirection function
 */

int	redir_words(char *str, char *sep, int ct)
{
	int	qte[2];
	int	i;

	i = 0;
	qte[0] = 0;
	qte[1] = 0;
	while (str && str[i] != '\0')
	{
		ct++;
		if (!ft_strchr(sep, str[i]))
		{
			while ((!ft_strchr(sep, str[i]) || qte[1] || qte[0]) && str[i] != '\0')
			{
				qte[0] = (qte[0] + (!qte[1] && str[i] == '\'')) % 2;
				qte[1] = (qte[1] + (!qte[0] && str[i] == '\"')) % 2;
				i++;
			}
			if (qte[0] || qte[1])
				return (-1);
		}
		else
			i++;
	}
	return (ct);
}

/*
 *	This function fill a double array with the words received from a string, separated by redirections
 */

static char	**ft_fill_redir(char *str, char **ret, char *sep, int i[3])
{
	int	qte[2]; //these will be the two counters used for quote managing

	qte[0] = 0;
	qte[1] = 0;
	while (str && str[i[0]] != '\0')
	{
		i[1] = i[0];
		if (!ft_strchr(sep, str[i[0]]))
		{
			while ((!ft_strchr(sep, str[i[0]]) || qte[0] || qte[1]) && str[i[0]])
			{
				qte[0] = (qte[0] + (!qte[1] && str[i[0]] == '\'')) % 2;
				qte[1] = (qte[1] + (!qte[0] && str[i[0]] == '\"')) % 2;
				i[0]++;
			}
		}
		else
			i[0]++;
		ret[i[2]++] = ft_substr(str, i[1], i[0] - i[1]);
	}
	return (ret);
}

/*
 *	This function splits a string by redirections and pipes, creating a double array
 */

char	**redir_split(char *str, char *sep)
{
	char	**ret;
	int		wd_ct;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;

	if (!str)
		return (NULL);
	wd_ct= redir_words(str, sep, 0); //count the number of words in str, splitted by characters in sep
	if (wd_ct == -1) //if wd_ct is -1 means there is an error so return NULL
		return (NULL);
	ret = malloc(sizeof(char *) * (wd_ct + 1)); //allocate memory for the number of words needed
	if (!ret) //protect malloc
		return (NULL);
	ret = ft_fill_redir(str, ret, sep, i); //fill memory properly
	ret[wd_ct] = NULL; //set the end of double array
	return (ret); //return our double array
}
