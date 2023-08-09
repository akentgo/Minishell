/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akent-go <akent-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:10:29 by akent-go          #+#    #+#             */
/*   Updated: 2023/08/09 17:04:12 by akent-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
 * This function will return the number of words 
 (splitted by spaces or tabs) we have found in our string
 */

int	n_words(const char *str, char *sep, int ct[2])
{
	int	qte[2];

	qte[0] = 0;
	qte[1] = 0;
	while (str[ct[0]])
	{
		if (!ft_strchr(sep, str[ct[0]]))
		{
			ct[1]++;
			while ((!ft_strchr(sep, str[ct[0]]) || qte[1]) && str[ct[0]])
			{
				if (!qte[0] && (str[ct[0]] == '\'' || str[ct[0]] == '\"'))
					qte[0] = str[ct[0]];
				qte[1] = (qte[1] + (qte[0] == str[ct[0]])) % 2;
				qte[0] *= qte[1] != 0;
				ct[0]++;
			}
			if (qte[1])
				return (-1);
		}
		else
			ct[0]++;
	}
	return (ct[1]);
}

/*
 * this function will fill an array 
 of strings with our words (splitted by spaces or tabs)
 */

static char	**ft_fill_array(char *str, char **ret, char *sep, int i[3])
{
	int	len;
	int	qte[2];

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

char	**ft_cmdsplit(char *rd_out, char *sep)
{
	int		wd_ct;
	char	**ret;
	int		count[2];
	int		i[3];

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
