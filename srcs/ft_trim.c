#include "../includes/minishell.h"

/*
 *	This function will return the number of  quotes that we have to trim
 */

static int	trim_len(const char *s)
{
	int	ct;
	int	i;
	int	qte[2];

	i = 0;
	ct = 0;
	qte[0] = 0;
	qte[1] = 0;
	while (s && s[i])
	{
		qte[0] = (qte[0] + (!qte[1] && s[i] == '\'')) % 2;
		qte[1] = (qte[1] + (!qte[0] && s[i] == '\"')) % 2;
		if ((s[i] == '\"' && !qte[0]) || (s[i] == '\'' && !qte[1]))
			ct++;
		i++;
	}
	if (qte[0] || qte[1])
		return (-1);
	return (ct);
}

/*
 *	This function removes any unnecessary quote an return the "clean" string
 */

char	*ft_trim(const char *s, int qte[2])
{
	int		ct;		//this will hold the number of quotes to remove
	int		i[2];	//these will be 2 counters, one for s string and the other for trim string
	char	*trim;	//this will be the new string

	i[0] = 0;	//set the counter to 0
	i[1] = -1;	//set the counter to 0
	ct = trim_len(s);	//we check the number of quotes to remove
	if (!s || ct == -1) //if there is no string or there is an open quote return NULL
		return (NULL);
	trim = malloc(sizeof(char) * (ft_strlen(s) - ct + 1)); //allocate memory for the string minus the number of quotes to remove
	if (!trim) //protect the malloc
		return (NULL);
	//El error es al guardar caracteres en el string aqui abajo, 
	while (s[i[0]]) //iterate the string
	{
		qte[0] = (qte[0] + (!qte[1] && s[i[0]] == '\'')) % 2;	//checking quotes (explained in lexer)
		qte[1] = (qte[1] + (!qte[0] && s[i[0]] == '\"')) % 2;	//checking quotes
		if ((s[i[0]] != '\"' || qte[0]) && (s[i[0]] != '\'' || qte[1]) && ++i[1] >= 0)
			trim[i[1]] = s[i[0]];
		i[0]++; //iterates
	}
	trim[++i[1]] = '\0'; //close trim string
	return (trim); //return the string
}
