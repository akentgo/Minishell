#include "../includes/minishell.h"

/*long	ft_strlen(const char *a)
{
	long	l;

	l = 0;
	while (a[l] != 0)
		l++;
	return (l);
}*/

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr)
	{
		if (*ptr == (char) c)
			return (ptr);
		ptr++;
	}
	if (*ptr == (char) c)
		return (ptr);
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	len_s;
	unsigned int	size;
	char			*ptr;
	unsigned int	i;

	if (!s)
		return (0);
	len_s = ft_strlen(s);
	if ((len_s - start) > len)
		size = len + 1;
	else
		size = len_s - start + 1;
	if (start >= len_s)
		size = 1;
	ptr = (char *) malloc(sizeof(char) * size);
	if (ptr == 0)
		return (ptr);
	i = 0;
	while (s[start + i] && i < len && start < len_s)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/*
 * This function will return the number of words (splitted by spaces or tabs) we have found in our string
 */

int	n_words(const char *str, char *sep, int ct[2])
{
	int	qte[2]; //these will be another double counter that we will use here

	//set the counter to 0
	qte[0] = 0; //Tipo de comilla
	qte[1] = 0; //Si están las comillas abiertas(1) o cerradas(0)
	while (str[ct[0]]) //while the string has not ended we continue the loop (ct[0] will be the one for iterating through the string)
	{
		if (!ft_strchr(sep, str[ct[0]])) //if the element in the string is not an space or tab we do...
		{
			ct[1]++; //increase our ct[1] which will count how many words we have
			while ((!ft_strchr(sep, str[ct[0]]) || qte[1]) && str[ct[0]]) // while our character is not an space or tab or our qte[1] (which check if we have an open quote) and our string has not ended we continue this loop
			{
				if (!qte[0] && (str[ct[0]] == '\'' || str[ct[0]] == '\"')) // if qte[0] (we will hold what kind of quote we have find here) is not set yet and we find a quote
					qte[0] = str[ct[0]]; //we save what kind of quote we have found
				qte[1] = (qte[1] + (qte[0] == str[ct[0]])) % 2; //qte[1] will be set as:
																// (its current value + (1 if the quote already found is the same as the current one)) module 2 so we check if we have an even or odd ammount of quotes
																// (its current value + (0 if the quote already found is different from the current one)) module 2
																// basically if we have found a second similar quote we set qte[1] to 0, if we have not we set keep it as it is
				qte[0] *= qte[1] != 0; // qte[0] will keep as it is if qte[1] is not or qte[0] will be set to 0 if qte[1] has been set to 0
				ct[0]++; //we iterate through the string
			}
			if (qte[1]) // if we have finished the loop and qte[1] is not 0 it means we have an open quote so return -1
				return (-1);
		}
		else // if we do not find a quote just iterate
			ct[0]++;
	}
	return (ct[1]); //return the number of words found
}

/*
 * this function will fill an array of strings with our words (splitted by spaces or tabs)
 */

static char	**ft_fill_array(char *str, char **ret, char *sep, int i[3])
{
	int	len; //this will hold the length of the string
	int	qte[2]; //these will be the two counters used for quote managing

	qte[0] = 0;
	qte[1] = 0;
	len = ft_strlen(str);
	while (str[i[0]])
	{
		while (ft_strchr(sep, str[i[0]]) && str[i[0]] != '\0')
			i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(sep, str[i[0]]) || qte[0] || qte[1]) && str[i[0]])
		{
			qte[0] = (qte[0] + (!qte[1] && str[i[0]] == '\'')) % 2;
			qte[1] = (qte[1] + (!qte[0] && str[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= len)
			ret[i[2]++] = "";
		else
			ret[i[2]++] = ft_substr(str, i[1], i[0] - i[1]);
	}
	return (ret);
}

/*
static char	**ft_fill_array(char *str, char **ret, char *sep, int i[3])
{
	int	len;
	int	qte[2];

	qte[0] = 0;
	qte[1] = 0;
	while (str[i[0]] == ' ' || str[i[0]] == '\t')
		i[0]++;
	while (str[i[0]] != '\0')
	{
		while (ft_strchr(sep, str[i[0]]) || qte[0])
		{
			if (!qte[0] && (str[i[0]] == '\'' || str[i[0]] == '\"'))
			{
				qte[0] = str[i[0]];
				i[0]++;
			}
			else
			{
				qte[1] = (qte[1] + (qte[0] == str[i[0]]) % 2);
				qte[0] *= qte[1] != 0;
				ret[i[1]][i[2]] = str[i[0]];
				i[0]++;
				i[2]++;
			}
		}
		i[2] = 0;
		i[1]++;
	}
	return (ret);
}
*/
char	**ft_cmdsplit(char *rd_out, char *sep)
{
	int	wd_ct; //this will hold how many words are in the read output (rd_out)
	char	**ret; //this will be the array of strings returned by the function
	int	count[2]; //this will be the 2 counters used in n_words function
	int	i[3]; // this will be the 3 counters used in fill_array function

	count[0] = 0;
	count[1] = 0;
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (!rd_out)
		return (NULL);
	wd_ct = n_words(rd_out, sep, count);
	if (wd_ct == -1)
		return (NULL);
	ret = (char **)malloc(sizeof(char *) * (wd_ct + 1));
	if (!ret)
		return (NULL);
	ret = ft_fill_array(rd_out, ret, sep, i);
	ret[wd_ct] = NULL;
	return (ret);
}

/*
static int	ft_count_words(const char *s, int i[2])
{
	int	qte[2];
	
	qte[0] = 0;
	qte[1] = 0;
	while (s[i[0]] != '\0')
	{
		if (s[i[0]] != ' ')
		{
			i[1]++;
			while ((s[i[0]] != ' ' || qte[0]) && s[i[0]] != '\0')
			{
				if (!qte[1] && (s[i[0]] == '\"' || s[i[0]] == '\''))
					qte[1] = s[i[0]];
				qte[0] = (qte[0] + (s[i[0]] == qte[1])) % 2; //this checks if we have found a qte before, in that case we set qte[0] to 0
				qte[1] *= qte[0] != 0;	//we set qte[1] to 1 if qte[0] == 1 && qte[1] == 1, or to 0 in any other case
				i[0]++;
			}
			if (qte[0]) //when we finish our loop checking for qtes, if qte[0] == 1 it means there is an open qte so we return an error
				return (-1);
		}
		else
			i[0]++;
	}
	return (i[1]);
}
*/

/*int	main (int argc, char **argv)
{
	int	n;
	char *str = "holi que tal\0";
	char **new_str;
	//n = n_words(argv[1], " \t", i);
	printf("%s\n", str);
	new_str = allocate_split(str, " ");
	printf ("%s\n", new_str[1]);
	return (0);
}*/

/*

char	**ft_strtrim(char *str)
{

}*/
