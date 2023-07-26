#include "../../includes/minishell.h"

extern int	g_status;

int	ft_strchr_i(const char *s, int c)
{
	unsigned char	u_char;
	int				i;

	i = 0;
	if (!s)
		return (-1);
	u_char = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == u_char)
			return (i);
		i++;
	}
	if (u_char == '\0')
		return (i);
	return (-1);
}

char *search_env(t_env *env, char *var)
{
	char	*holder;

	while (env && env->name)
	{
		if (ft_strncmp(env->name, var, ft_strlen(env->name)) == 0)
		{
			holder = ft_strdup(env->value);
			return (holder);
		}
		env = env->next;
	}
	return (NULL);
}

char *search_env_len(t_env *env, char *var, int n)
{
	char	*holder;

	while (env->name)
	{
		if (ft_strncmp(env->name, var, n) == 0)
		{
			holder = ft_strdup(env->value);
			return (holder);
		}
		env = env->next;
	}
	return (NULL);
}